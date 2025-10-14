#include "RTJob.h"

// Contstructur
RTJob::RTJob(std::string name, unsigned int limit, std::string rep, unsigned int prior) {
    
    nameContainer = name;
    limitTime = limit;
    repetition = rep;
    priority = prior;
    
  }
  

// Getter 
std::string RTJob::getNameContainer(void){
  
    return nameContainer;

  }

unsigned int RTJob::getLimitTime(void){

    return limitTime;
  
  }


std::string RTJob::getRepetition(void){

    return repetition;

}


int RTJob::getPriority(void){

  return priority;

}