#include "Schedule.h"



// Constructor

Schedule::Schedule(void){

  versionSchedule_ = "0";
  lengthSchedule_ = 0;
  taskList_ = nullptr;

}

Schedule::Schedule(std::string version, unsigned int length, std::list<RTJob>* list){
    
    versionSchedule_ = std::move(version);
    lengthSchedule_ = length;
    taskList_ = list;   
  
  }



// Destructor
Schedule::~Schedule() {
    // Check if the pointer is not null before deleting
    if (taskList_ != nullptr) {
        delete taskList_;
        taskList_ = nullptr; // good practice to avoid dangling pointer
    }
}
  
// Getter
std::string Schedule::getVersion(void){
    
    return versionSchedule_; 
  
  }


unsigned int Schedule::getLength(void){
    
    return lengthSchedule_;
  
  }


// Equals for abstract value
bool Schedule::equals(Schedule* s){
  if (s == nullptr) return false;
  return std::stoi(this->versionSchedule_) == std::stoi(s->getVersion());
  }

// Hashcode for abstract value
int Schedule::hashCode(void){
  return std::stoi(versionSchedule_);
}
