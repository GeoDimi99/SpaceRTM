#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>


class Schedule {
  
  private:
    
    string versionSchedule;
    unsigned int lengthSchedule;
  
  public:
    
    // Costructur  
    Schedule(unsigned int version, unsigned int length);
    
    // Getter 
    unsigned int getVersion();
    unsigned int getLength();
    
    

  };


#endif