#ifndef RTJOB_H
#define RTJOB_H

#include <string>


class RTJob {
  
  private:
    
    std::string nameContainer;
    unsigned int limitTime;
    std::string repetition;
    int priority; 
  
  public:
    
    // Costructur  
    RTJob(std::string name, unsigned int limit, std::string rep, unsigned int prior);
    
    // Getter 
    std::string getNameContainer(void);
    unsigned int getLimitTime(void);
    std::string getRepetition(void);
    int getPriority(void);
    
    // Setter
    
    
    

  };


#endif