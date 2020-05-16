#include <iostream>
#include <boost/format.hpp>
#include <boost/locale.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include "../inc/t_queue.h"
#include <boost/filesystem.hpp>
#include "../inc/time.hpp"
#include "../inc/read_write.hpp"
#include <tbb/concurrent_queue.h>
#include <tbb/task_group.h>


namespace bl = boost::locale::boundary;
namespace po = boost::program_options;


void merge_dict(tbb::concurrent_queue<std::map<std::string, int>> &dict_tq, std::mutex &mtx) {
    std::map<std::string, int> first_map;
    std::map<std::string, int> second_map;
//    std::vector<std::map<std::string, int>> merge_pair;

    while (true) {

        mtx.lock();
        if (dict_tq.unsafe_size() >= 2) {
            dict_tq.try_pop(first_map);
            dict_tq.try_pop(second_map);
        } else {
            mtx.unlock();
            break;
        }
        mtx.unlock();
//        first_map = merge_pair[0];
//        second_map = merge_pair[1];

        for (const auto &x : second_map) {
            first_map[x.first] += x.second;
        }
        dict_tq.push(first_map);
    }
}

void count_words_thr(tbb::concurrent_queue<std::string> &str_tq, std::map<std::string, int> &dict) {
    while (true) {
        std::string str_txt;
        str_tq.try_pop(str_txt);
        if (str_txt == "POISON PILL") {
            str_tq.push(str_txt);
            break;
        }
        bl::ssegment_index map(bl::word, str_txt.begin(), str_txt.end());
        // Define a rule
        map.rule(bl::word_letters);

        for (bl::ssegment_index::iterator it = map.begin(), e = map.end(); it != e; ++it) {
            ++dict[*it];
        }
    }
}

void read_str_from_dir_thr(std::string &in, tbb::concurrent_queue<std::string> *str_tq) {
    std::vector<std::string> root;
    root.push_back(in);
    read_from_dir(root, str_tq);
    str_tq->push("POISON PILL");
}

int main(int argc, char *argv[]) {
//    std::cout << boost::filesystem::current_path().string() << std::endl;
    boost::locale::generator gen;
    std::locale::global(gen("en_us.UTF-8"));
    std::string conf_file;
    if (argc == 1) {
        conf_file = "config.dat";
    } else if (argc == 2) {
        conf_file = argv[1];
    } else {
        std::cerr << "Insufficient amount of arguments.\n";
        exit(1);
    }

    std::ifstream conf(conf_file, std::ios::in);

    if (!conf.is_open()) {
        std::cerr << "Could not open the configuration file. Set your working directory to ..\n";
        exit(2);
    }

    std::string in, out_a, out_n;
    int thr, merge_thr;

    po::options_description config_parser;
    config_parser.add_options()
            ("in", po::value<std::string>(&in)->default_value("data_in/"))
            ("out_a", po::value<std::string>(&out_a)->default_value("data_out/result_by_name.txt"))
            ("out_n", po::value<std::string>(&out_n)->default_value("data_out/result_by_number.txt"))
            ("thr", po::value<int>(&thr)->default_value(1))
            ("merge_thr", po::value<int>(&merge_thr)->default_value(1));

    po::variables_map vm;
    store(parse_config_file(conf, config_parser), vm);
    notify(vm);
    if (thr < 1) {
        std::cerr << "Insufficient number of threads." << std::endl;
        exit(3);
    }

    tbb::concurrent_queue<std::string> str_tq;

    std::map<std::string, int> dict;
    tbb::task_group g;
    std::chrono::high_resolution_clock::time_point start;

    if (thr == 1) {
        g.run([&]{read_str_from_dir_thr(std::ref(in), &str_tq);});
        start = get_current_time_fenced();
        g.run([&]{count_words_thr(std::ref(str_tq), std::ref(dict));});

        g.wait();
    } else {
        std::map<std::string, int> dicts[thr];
        tbb::concurrent_queue<std::map<std::string, int>> dict_tq;
        std::mutex mtx;

        start = get_current_time_fenced();

        g.run([&]{read_str_from_dir_thr(std::ref(in), &str_tq);});

        for (int i = 0; i < thr; ++i) {
            g.run([&]{count_words_thr(std::ref(str_tq), std::ref(dicts[i]));});
        }

        g.wait();

        for (const auto &d : dicts) {
            dict_tq.push(d);
        }
        tbb::task_group m;

        for (int i = 0; i < merge_thr; ++i) {
            m.run([&]{merge_dict(std::ref(dict_tq), std::ref(mtx));});
        }

        m.wait();

        dict_tq.try_pop(dict);
//        for (auto &d : dicts) {
//            for (auto &it : d) {
//                dict[it.first] += it.second;
//            }
//            d.clear();
//        }

    }

    auto finish = get_current_time_fenced();
    std::cout << "Total: " << static_cast<float>(to_ms(finish - start)) / 60 << std::endl;
    write_file(out_a,out_n, dict);

    return 0;
}
