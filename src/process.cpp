#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include  "linux_parser.h"

#include "process.h"

using std::string;
using std::to_string;
using std::vector;


// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { vector<string> jiffies = LinuxParser::CpuUtilization(pid_);
    float utime = stof(jiffies[0]);
 float stime = stof(jiffies[1]);;
 float cutime = stof(jiffies[2]);;
float cstime= stof(jiffies[3]);;
 float starttime = stof(jiffies[4]);;
 long uptime = LinuxParser::UpTime();
 float total_time = utime +stime+ cutime +cstime;
  float seconds = uptime - starttime ;
    float cpu_usage = total_time/seconds;
    return cpu_usage;
 
  }

// TODO: Return the command that generated this process
string Process::Command() const { string command;
    command = LinuxParser::Command(pid_);
    return command; }

// TODO: Return this process's memory utilization
string Process::Ram() const { string ram;
    ram = LinuxParser::Ram(pid_);
    return ram; }

// TODO: Return the user (name) that generated this process
string Process::User() const { string user;
    user = LinuxParser::User(pid_);
    return user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() const {  long int uptime = 0;
    uptime = LinuxParser::UpTime(pid_);
 
    return uptime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return  (this->CpuUtilization() < a.CpuUtilization())?true:false; }