#ifndef _JOB_DISPATCHER_H_
#define _JOB_DISPATCHER_H_

#include "threadSafeQueue.h"

#include <atomic>
#include <thread>
#include <functional>
#include <condition_variable>

namespace jobDispatcher {

    class jobDispatcher {
    public:

        jobDispatcher() = delete;
        explicit jobDispatcher(unsigned int maximumThreadCount);
        ~jobDispatcher();
        void addJob(const std::function<void(int, std::atomic<unsigned int>)>& job);
        void start();
        void stop();

    private:

        threadSafeQueue<std::function<void(int, std::atomic<unsigned int>)>> m_jobQueue;
        std::atomic<unsigned> m_availableThreadCount = 0;
        std::atomic<bool> m_isDispatcherWorking = false;
        std::condition_variable m_cond;
        std::thread* m_dispatcherThread = nullptr;
    };
}

#endif //_JOB_DISPATCHER_H_
