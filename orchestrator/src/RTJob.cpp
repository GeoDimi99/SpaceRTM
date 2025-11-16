#include "RTJob.h"

// Contstructur
RTJob::RTJob(std::string name, unsigned int limit, std::string rep, unsigned int prior) {
    
    nameContainer = name;
    limitTime = limit;
    repetition = rep;
    priority = prior;
    
  }
  

// Getters 
std::string RTJob::getNameContainer() const { return nameContainer; }
unsigned int RTJob::getLimitTime() const { return limitTime; }
std::string RTJob::getRepetition() const { return repetition; }
int RTJob::getPriority() const { return priority; }