#include "TaskExecutor.h"

// Static methods should be defined outside the class

TaskExecutor* TaskExecutor::pinstance_ = nullptr;
std::mutex TaskExecutor::mutex_;

TaskExecutor::TaskExecutor(){};
TaskExecutor::~TaskExecutor(){};

TaskExecutor& TaskExecutor::getInstance(){
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new TaskExecutor();
    }
    return *pinstance_;
} 


void TaskExecutor::perform(Task& t) {
    std::lock_guard<std::mutex> lock(mutex_);
    t.execute();
}



