#include <iostream>
#include <unistd.h>

#include <libmemcached/memcached.h>
#include <string>
#include <map>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include "Task.h"
#include "TaskExecutor.h"

#include "Schedule.h"
#include "RTJob.h"

int main(int argc, char **argv){
  
  memcached_st *memc;
  memcached_return rc;

  // Create a Memcached structure
  memc = memcached_create(NULL);  
  memcached_server_st *servers = memcached_server_list_append(NULL, "memcached", 11211, &rc);
  
  // Add server to client
  rc = memcached_server_push(memc, servers); 
  
  // Free server list
  memcached_server_list_free(servers); 
  
  /*********  Memcached initizialization  *********/
  /************************************************/
  
  std::cout << "Start Initialization!" << std::endl;

  // Key-value data to initialize
  std::map<std::string, std::string> init_data = {
        {"schedule:version", "1"},
        {"schedule:length", "3"},
        {"scheduletask:1",  "{\"nametask\":\"init_core\", \"starttime\":\"0\", \"endtime\":\"14\", \"repetition\":\"R1\", \"priority\":\"135\"}"},
        {"scheduletask:2",  "{\"nametask\":\"comm_proto\", \"starttime\":\"0\", \"endtime\":\"16\", \"repetition\":\"R1\", \"priority\":\"136\"}"},
        {"scheduletask:3",  "{\"nametask\":\"ctrl_exec\", \"starttime\":\"2\", \"endtime\":\"5\", \"repetition\":\"R1\", \"priority\":\"133\"}"}
  };

  // Populate Memcached
  
  for (const auto& pair : init_data) {
      rc = memcached_set(memc, pair.first.c_str(), pair.first.size(),
                          pair.second.c_str(), pair.second.size(),
                          (time_t)0, (uint32_t)0);
      if (rc != MEMCACHED_SUCCESS) {
          std::cerr << "Failed to set key '" << pair.first
                    << "': " << memcached_strerror(memc, rc) << std::endl;
      }
  }
  std::cout << "Initialization complete!" << std::endl;
  
  /************************************************/
  /******** End Memcached initizialization  *******/
  
  
  
  


  
  // Init var
  Schedule* schedule = new Schedule();
  std::cout << "Verison: " << schedule->getVersion() << " Length:" << schedule->getLength() << std::endl;



  std::string lookupKey = "schedule:version";
  
  
  rc = MEMCACHED_NOTFOUND;

  while(rc !=  MEMCACHED_SUCCESS){

    // Check if some schedule is stored inside memcached
    rc = memcached_exist(memc, lookupKey.c_str(), lookupKey.length());


    if (rc == MEMCACHED_SUCCESS){

      std::cout << "Key exists!" << std::endl;
    
    } else {
      
      if (rc == MEMCACHED_NOTFOUND)
        std::cout << "Key not found." << std::endl;
      else
        std::cout << "Error: " << memcached_strerror(memc, rc) << std::endl;
      
      // If it's not found some schedule then wait an retry
      sleep(1);
    }

  }
     
    while(true){


      // Check new schedule version and update 
      std::string newVersionSchedule;
      size_t valueLength;
      uint32_t flags;
      char* ret_val = memcached_get(memc, lookupKey.c_str(), lookupKey.size(), &valueLength, &flags, &rc);

      if (rc == MEMCACHED_SUCCESS) {
          newVersionSchedule = ret_val;
          std::cout << lookupKey << " -> " << newVersionSchedule << std::endl;
      } else {
          std::cerr << "Failed to get key '" << lookupKey << "': " << memcached_strerror(memc, rc) << std::endl;
      }

      if( std::stoi(schedule->getVersion()) < std::stoi(newVersionSchedule) ){
        
        // There is a new version schedule, so we must update it 

        std::string scheduleLengthKey = "schedule:length";
        std::string newLengthSchedule;
        ret_val = memcached_get(memc, scheduleLengthKey.c_str(), scheduleLengthKey.size(), &valueLength, &flags, &rc);
        int lengthSchedule;

        if (rc == MEMCACHED_SUCCESS) {
          newLengthSchedule = ret_val;
          std::cout << scheduleLengthKey << " -> " << newLengthSchedule << std::endl;
          lengthSchedule = std::stoi(newLengthSchedule);
        } else {
          std::cerr << "Failed to get key '" << scheduleLengthKey << "': " << memcached_strerror(memc, rc) << std::endl;
        }

        for(int i = 1; i <= lengthSchedule; i++ ){
          std::string jsonRTJob;
          std::string rtjobKey = "scheduletask:" + std::to_string(i);
          ret_val = memcached_get(memc, rtjobKey.c_str(), rtjobKey.size(), &valueLength, &flags, &rc);

          if (rc == MEMCACHED_SUCCESS) {
            jsonRTJob = ret_val;
            std::cout << rtjobKey << " -> " << jsonRTJob << std::endl;
          } else {
            std::cerr << "Failed to get key '" << jsonRTJob << "': " << memcached_strerror(memc, rc) << std::endl;
          }

          rapidjson::Document docRTJob; 
          docRTJob.Parse(jsonRTJob.c_str());
          if (docRTJob.HasParseError())  
            std::cerr << "Error parsing JSON!" << std::endl;
          
          std::cout << "Run nametask: " << docRTJob["nametask"].GetString() << std::endl;
           
          
          std::string imageName = docRTJob["nametask"].GetString();
          std::string command =
                    "docker run --rm "
                    "--cpuset-cpus=2 "
                    "--cap-add=SYS_NICE "
                    "--ulimit rtprio=99 "
                    "--ulimit rttime=-1 "
                    "--ulimit memlock=2048000000 "
                    "--network=host "
                    + imageName +
                    " /app/api/rtjob "
                    "--name " + imageName +
                    " --policy fifo --priority 2 --time 3000";
      
          std::cout << "Running: " << command << std::endl;
          int result = system(command.c_str());

          if (result == 0)
            std::cout << "Container for " << imageName << " started successfully!" << std::endl;
          else
            std::cerr << "Failed to start container for " << imageName << std::endl;

        
        }

        // Keep program running
        while (1) sleep(10);

      }
      
      


      free(ret_val);
      sleep(1);

    }



  



  // Keep program running
  while (1) sleep(10);

  memcached_free(memc);
  return 0;

}



/*

int main() {
  
  Task myTask;
  TaskExecutor::getInstance().perform(myTask);

  Schedule s("1", 0);
  RTJob t("TASK", 4, "R1", 5);
  
  std::cout << "Verison: " << s.getVersion() << " Length:" << s.getLength() << "\n";
  std::cout << "Name: " << t.getNameContainer() << " Limit: " << t.getLimitTime() << " Repetition: " << t.getRepetition() << " Priority: " << t.getPriority() << "\n";
  
  while(1) sleep(10);

  return 0;
}

*/