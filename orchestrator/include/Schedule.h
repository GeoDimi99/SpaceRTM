#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "RTJob.h"

#include <string>
#include <list>
#include <queue>


class Schedule {
  
  private:
    
    std::string versionSchedule_;
    unsigned int lengthSchedule_;
    std::list<RTJob>* taskList_;
  
  public:
    
    // Costructurs 
    Schedule(void); 
    Schedule(std::string version, unsigned int length, std::list<RTJob>* list);
    
    // Destructor
    ~Schedule();

    // Getter 
    std::string getVersion(void);
    unsigned int getLength(void);

    // Equals for Type value
    bool equals(Schedule* s);

    // Hashcode for Type value
    int hashCode(void);
    

  };


#endif