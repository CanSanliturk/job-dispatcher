#ifndef _THREAD_SAFE_QUEUE_H_
#define _THREAD_SAFE_QUEUE_H_

#include <queue>
#include <mutex>
#include <optional>

namespace jobDispatcher {

    /// @brief Thin-wrapper around std::queue for thread safe push/pop operations
    /// @tparam T Type of the item to be stored
    template <typename T>
    class threadSafeQueue {
    public:
        /// @brief Thread-safe push operations
        /// @param item Item to be pushed to the queue
        void enqueue(const T& item) {
            std::lock_guard<std::mutex> localGuard(m_guardQueue);
            m_queue.push(item);
        }

        /// @brief Thread-safe pop operation
        /// @return Front item of the queue wrapped in std::optional.
        /// If queue is empty, returns std::nullopt
        std::optional<T> dequeue() {
            std::lock_guard<std::mutex> localGuard(m_guardQueue);
            if (m_queue.empty()) {
                return std::nullopt;
            } else {
                T front = std::move(m_queue.front());
                m_queue.pop();
                return std::optional<T>(std::move(front));
            }
        }

        /// @brief Thread-safe empty check
        /// @return True if queue is empty. Otherwise, false
        bool isEmpty() const {
            std::lock_guard<std::mutex> localGuard(m_guardQueue);
            return m_queue.empty();
        }

    private:
        /// @brief Underlying queue structure
        std::queue<T> m_queue;

        /// @brief Mutex for thread-safe operations
        mutable std::mutex m_guardQueue;
    };
};

#endif //_THREAD_SAFE_QUEUE_H_
