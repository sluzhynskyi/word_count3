#include "../inc/read_write.hpp"
#include "boost/locale.hpp"
#include <iostream>
#include <map>
#include <cmath>
#include <string>
#include <tbb/concurrent_queue.h>

namespace fs = boost::filesystem;

void reading_from_archive(const std::string &buffer, tbb::concurrent_queue<std::string> *tq) {
    struct archive *a;
    struct archive_entry *entry;
    la_int64_t r;
    off_t entry_size;
    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);
    archive_read_support_format_raw(a);
    // read from buffer, not from the file
    r = archive_read_open_memory(a, buffer.c_str(), buffer.size());
    for (;;) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF) {
            break;
        }
        if (r < ARCHIVE_OK) {
            break;
        }
        if (r < ARCHIVE_WARN) {
            break;
        }
        // Do nothing if not txt files
        if (boost::filesystem::path(archive_entry_pathname(entry)).extension() == ".txt") {
            entry_size = archive_entry_size(entry);
            std::string output(entry_size, char{});
            r = archive_read_data(a, &output[0], output.size());
            if (output.size() < 10 * std::pow(2, 20)) {
                // write explicitly to the other buffer
                tq->push(boost::locale::fold_case(boost::locale::normalize(output)));
            }
        }
    }
    archive_read_close(a);
    archive_read_free(a);
}

int write_file(const std::string &filename_a, const std::string &filename_n, tbb::concurrent_unordered_map<std::string, int> mp) {
    std::ofstream out_a, out_n;
    std::multimap<std::string, int> cp = copy_to_multimap(mp);
    mp.clear();
    out_a.open(filename_a, std::ios::trunc | std::ios::out | std::ios::binary);
    for (auto &it : cp) {
        out_a << boost::format("%1% %|15t| : %|25t| %2%\n") % it.first.c_str() % it.second;
    }
    out_a.close();
    std::multimap<int, std::string> dst = flip_map(cp);
    cp.clear();
    out_n.open(filename_n, std::ios::trunc | std::ios::out | std::ios::binary);
    for (auto it = dst.rbegin();
         it != dst.rend(); ++it) {
        out_n << boost::format("%1% %|15t| : %|25t| %2%\n") % it->second.c_str() % it->first;
    }
    out_n.close();
    return 0;
}