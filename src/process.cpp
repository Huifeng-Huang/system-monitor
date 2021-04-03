#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;
// TODO: Return this process's ID
int Process::Pid() { 
    std::cout << pid<< std::endl;
    return pid;   
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    vector<string> jiffies = LinuxParser::CpuUtilization(pid);
    long utime;
 long stime;
 long cutime;
 long cstime;
 long starttime;
 long uptime;
    utime = 3;
    stime = 48;
    cutime= 91213;
    cstime = 12278;
    starttime =3570;
    long total_time = utime +stime+ cutime +cstime;
    long seconds = uptime - (starttime /sysconf(_SC_CLK_TCK));
    float cpu_usage = 100*((total_time/sysconf(_SC_CLK_TCK))/seconds);
    return cpu_usage;

 }

// TODO: Return the command that generated this process
string Process::Command() { 
    string command;
    command = LinuxParser::Command(pid);
    return command;
    
 }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    string ram;
    ram = LinuxParser::Ram(pid);
    return ram;
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    string user;
    user = LinuxParser::User(pid);
    return user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {  
    long int uptime = 0;
    uptime = LinuxParser::UpTime(pid);
    return uptime;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  

    return  this->pid < a.pid? true:false; }