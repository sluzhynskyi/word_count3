#include <iostream>
#include <boost/locale.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <thread>
#include <boost/filesystem.hpp>
#include "../inc/time.hpp"
#include "../inc/read_write.hpp"
#include <tbb/concurrent_queue.h>
#include <tbb/pipeline.h>

#define TBB_PREVIEW_CONCURRENT_ORDERED_CONTAINERS 1

#include <tbb/concurrent_unordered_map.h>

namespace fs = boost::filesystem;
namespace bl = boost::locale::boundary;
namespace po = boost::program_options;
namespace bs = boost::system;


void pipeline(int thr, std::string &in, tbb::concurrent_unordered_map<std::string, int> &dict) {
    fs::recursive_directory_iterator iter(in);
    // Create a Recursive Directory Iterator object pointing to end.
    fs::recursive_directory_iterator end;

    tbb::parallel_pipeline(
            thr,
            tbb::make_filter<void, std::string>(
                    tbb::filter::serial_out_of_order,
                    [&](tbb::flow_control &fc) -> std::string {
                        bs::error_code ec;
                        if (iter == end) {
                            fc.stop();
                            return "";
                        }
                        fs::path file = iter->path();
                        while (fs::is_directory(file)) {
                            iter.increment(ec);
                            if (iter == end) {
                                fc.stop();
                                return "";
                            }
                            file = iter->path();
                        }
                        iter.increment(ec);
                        return file.string();
                    }) &
            tbb::make_filter<std::string, tbb::concurrent_unordered_map<std::string, int>>(
                    tbb::filter::parallel,
                    [&](std::string file_name) -> tbb::concurrent_unordered_map<std::string, int> {
                        tbb::concurrent_queue<std::string> tq;
                        std::ostringstream buffer_ss;
                        std::ifstream raw_file(file_name, std::ios::binary);
                        buffer_ss << raw_file.rdbuf();
                        std::string buffer{buffer_ss.str()};
                        std::cout << file_name << std::endl;
                        if (fs::path(file_name).extension() == ".txt") {
                            if (buffer.size() < 10 * std::pow(2, 20)) {
                                tq.push(boost::locale::fold_case(boost::locale::normalize(buffer)));
                            }
                        } else {
                            reading_from_archive(buffer, &tq);
                        }
                        std::string s;
                        tbb::concurrent_unordered_map<std::string, int> d;
                        while (tq.try_pop(s)) {
                            bl::ssegment_index map(bl::word, s.begin(), s.end());
                            // Define a rule
                            map.rule(bl::word_letters);
                            for (bl::ssegment_index::iterator it = map.begin(), e = map.end(); it != e; ++it) {
                                ++d[*it];
                            }
                        }
                        return d;
                    }) &
            tbb::make_filter<tbb::concurrent_unordered_map<std::string, int>, void>(
                    tbb::filter::serial_out_of_order,
                    [&](const tbb::concurrent_unordered_map<std::string, int> &d) -> void {
                        for (auto &it : d) {
                            dict[it.first] += it.second;
                        }
                    }
            )
    );
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
            ("thr", po::value<int>(&thr)->default_value(1));
    po::variables_map vm;
    store(parse_config_file(conf, config_parser), vm);
    notify(vm);
    if (thr < 1) {
        std::cerr << "Insufficient number of threads." << std::endl;
        exit(3);
    }
    tbb::concurrent_unordered_map<std::string, int> dict;
    auto start = get_current_time_fenced();

    pipeline(thr, in, dict);

    auto finish = get_current_time_fenced();
    std::cout << "Total: " << static_cast<float>(to_ms(finish - start)) / 60 << std::endl;
    write_file(out_a, out_n, dict);
    return 0;
}
