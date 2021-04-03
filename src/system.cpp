#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"


using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    cpu_ = Processor();
    return cpu_;
    }
    

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<int> pids = LinuxParser::Pids(); 
    for (int i = 0; i< pids.size(); i++ ){
        int pid_ = pids[i];
        
        processes_.push_back(Process(pid_));
      
    }
    return processes_;
 }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    string kernel;
    kernel = LinuxParser::Kernel() ;
    return kernel; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    float usage;
    usage = LinuxParser:: MemoryUtilization() ;
    return usage;}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    string os;
    os = LinuxParser::OperatingSystem();
    return os;
    
 }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    int RunningProcesses = 0;
    RunningProcesses = LinuxParser::RunningProcesses();
    return RunningProcesses; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    int TotalProcesses = 0;
    TotalProcesses = LinuxParser::TotalProcesses();
    return TotalProcesses;
 }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    
   long up_time = LinuxParser::UpTime();
 
    return up_time; }