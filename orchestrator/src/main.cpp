#include <iostream>

#include "Task.h"
#include "TaskExecutor.h"

#include "Schedule.h"
#include "RTJob.h"

int main() {
  
  Task myTask;
  TaskExecutor::getInstance().perform(myTask);

  Schedule s("1", 0);
  RTJob t("TASK", 4, "R1", 5);
  
  std::cout << "Verison: " << s.getVersion() << " Length:" << s.getLength() << "\n";
  std::cout << "Name: " << t.getNameContainer() << " Limit: " << t.getLimitTime() << " Repetition: " << t.getRepetition() << " Priority: " << t.getPriority() << "\n";
  
  return 0;
}
