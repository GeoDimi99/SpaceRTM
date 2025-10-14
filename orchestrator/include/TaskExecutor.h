#ifndef TASKEXECUTOR_H
#define TASKEXECUTOR_H

#include <mutex>
#include "Task.h"   // Assuming Task has a method execute()

class TaskExecutor {


    private:
        static TaskExecutor* pinstance_;
        static std::mutex mutex_;           

    protected: 
        // Private constructor
        TaskExecutor();

        // Private destructor 
        ~TaskExecutor();

    public:
        // TaskExecutor should not be cloneable.
        TaskExecutor(TaskExecutor &other) = delete;

        // TaskExecutor should not be assignable.
        void operator=(const TaskExecutor&) = delete;

        // Static method to get the single instance (thread-safe)
        static TaskExecutor& getInstance();  

        // Method to execute a Task
        void perform(Task& t);    
        
};

#endif