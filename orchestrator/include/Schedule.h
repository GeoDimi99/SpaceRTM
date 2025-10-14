#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>


class Schedule {
  
  private:
    
    std::string versionSchedule;
    unsigned int lengthSchedule;
  
  public:
    
    // Costructur  
    Schedule(std::string version, unsigned int length);
    
    // Getter 
    std::string getVersion(void);
    unsigned int getLength(void);
    
    

  };


#endif