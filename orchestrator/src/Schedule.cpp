#include "Schedule.h"


// Constructur

Schedule::Schedule(std::string version, unsigned int length){
    
    versionSchedule = version;
    lengthSchedule = length;   
  
  }
  
// Getter
std::string Schedule::getVersion(void){
    
    return versionSchedule; 
  
  }


unsigned int Schedule::getLength(void){
    
    return lengthSchedule;
  
  }
