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
#include <tbb/concurrent_queue.h>
#define TBB_PREVIEW_CONCURRENT_ORDERED_CONTAINERS 1
#include <tbb/concurrent_unordered_map.h>

namespace fs = boost::filesystem;


void reading_from_archive(const std::string &buffer, tbb::concurrent_queue<std::string> *tq);


int write_file(const std::string &filename_a, const std::string &filename_n, tbb::concurrent_unordered_map<std::string, int> mp);

template <typename A, typename B>
std::multimap<B, A> flip_map(std::multimap<A,B> & src) {
    std::multimap<B,A> dst;
    for(auto const & it: src)
        dst.insert(std::pair<B, A>(it.second, it.first));
    return dst;
}
template <typename A, typename B>
std::multimap<A, B> copy_to_multimap(tbb::concurrent_unordered_map<A,B> & src) {
    std::multimap<A,B> dst;
    for(auto const & it: src)
        dst.insert(std::pair<A, B>(it.first, it.second));
    return dst;
}
#endif