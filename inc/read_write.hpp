#ifndef READ_WRITE_HPP
#define READ_WRITE_HPP

#include <archive.h>
#include <archive_entry.h>
#include <boost/format.hpp>
#include <boost/locale.hpp>
#include <string>
#include <map>
#include <vector>
#include <boost/filesystem.hpp>
#include <numeric>
#include <exception>
#include "t_queue.h"
#include <tbb/concurrent_queue.h>

namespace fs = boost::filesystem;

std::vector<std::string> get_file_list(const std::string &path);

void reading_from_archive(const std::string &buffer, tbb::concurrent_queue<std::string> *tq);

void read_from_dir(const std::vector<std::string>& files, tbb::concurrent_queue<std::string> *tq);

int write_file(const std::string &filename_a, const std::string &filename_n, std::map<std::string, int> mp);

template <typename A, typename B>
std::multimap<B, A> flip_map(std::map<A,B> & src) {

    std::multimap<B,A> dst;

    for(typename std::map<A, B>::const_iterator it = src.begin(); it != src.end(); ++it)
        dst.insert(std::pair<B, A>(it -> second, it -> first));

    return dst;
}
#endif