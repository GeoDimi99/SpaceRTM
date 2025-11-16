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
    
    // Getters
    std::string getNameContainer() const;
    unsigned int getLimitTime() const;
    std::string getRepetition() const;
    int getPriority() const;
    
    // Setter
    
    
    

  };


#endif