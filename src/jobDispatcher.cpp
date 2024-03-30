#include "jobDispatcher.h"

namespace jobDispatcher {

    jobDispatcher::jobDispatcher(unsigned int maximumThreadCount) 
        : m_availableThreadCount(maximumThreadCount)
    {
    }

    jobDispatcher::~jobDispatcher() {
        m_isDispatcherWorking = false;
        if (nullptr != m_dispatcherThread)
        {
            m_dispatcherThread->join();
            delete m_dispatcherThread;
        }
        
    }

    void jobDispatcher::addJob(const std::function<void(int, std::atomic<unsigned int>)>& job) {
        m_jobQueue.enqueue(job);
    }

    void jobDispatcher::start() {
        m_isDispatcherWorking = true;
        m_dispatcherThread = new std::thread([this]() {
                while (true == m_isDispatcherWorking)
                {
                    if ((false == m_jobQueue.isEmpty()) && (0 < m_availableThreadCount))
                    {
                        std::function<void(int, std::atomic<unsigned int>)> nextJob = m_jobQueue.dequeue().value();
                        --m_availableThreadCount;
                        std::thread jobThread(nextJob);
                        jobThread.detach();
                    }
                }
            }
        );
    }

    void jobDispatcher::stop() {
        m_isDispatcherWorking = false;
    }
};

