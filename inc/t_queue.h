#ifndef WORD_COUNT_T_QUEUE_H
#define WORD_COUNT_T_QUEUE_H

#include <deque>
#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <condition_variable>

template<class T>
class t_queue {
private:
    static const int UPPER_BOUND = 100;
    mutable std::mutex mut;
    std::deque<T> queue;
    std::condition_variable publish_notify;
    std::condition_variable receive_notify;


public:


    t_queue() = default;

    ~t_queue() = default;

    t_queue(const t_queue<T> &q) = delete;

    const t_queue &operator=(const t_queue<T> &q) = delete;

    void push_back(T d) {
        {
            std::unique_lock<std::mutex> lg(mut);
            receive_notify.wait(lg, [this]() { return queue.size() + 1 <= UPPER_BOUND; });
            queue.push_back(d);
        }
        publish_notify.notify_one();
    }

    T pop() {
        T d;
        {
            std::unique_lock<std::mutex> lg(mut);
            publish_notify.wait(lg, [this]() { return queue.size() != 0; });
            d = queue.front();
            queue.pop_front();
        }
        receive_notify.notify_one();
        return d;
    }

    std::vector<T> pop2() {
        std::vector<T> v_d;
        {
            std::unique_lock<std::mutex> lg(mut);
            publish_notify.wait(lg, [this]() { return queue.size() >= 2; });
            v_d.push_back(queue.front());
            queue.pop_front();
            v_d.push_back(queue.front());
            queue.pop_front();
        }
        receive_notify.notify_one();
        return v_d;
    };


    size_t get_size() const {
        std::lock_guard<std::mutex> lg(mut);
        return queue.size();
    }
};

#endif //WORD_COUNT_T_QUEUE_H
