#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "linux_parser.h"


using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  string value;
  static double MemTotal = 0;
  static double MemFree = 0;
  static float usage = 0;

  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
         
          MemTotal = stof(value) ; 
        }
        if (key == "MemFree:") {
          MemFree = stof(value) ; 
        }
      }
    }
  }
  usage = (MemTotal-MemFree)/MemTotal; 
  return usage; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long int Suptime, Iuptime = 0; // Suptime: the uptime of the system & Iuptime: the amount of time spent in the idle process
  string Suptime_str, Iuptime_str;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream>>Suptime_str>> Iuptime_str;
     Suptime = stol(Suptime_str);
     
  }
   
  return Suptime; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  string line;
  string key;
  string user,nice,system,idle,iowait,irq,softirq;
  static long Jiffies = 0;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      
      std::istringstream linestream(line);
      while (linestream >> key >> user>>nice>>system>>idle>>iowait>>irq>>softirq) {
        if (key == "cpu") {
         
          Jiffies = stol(user)+stol(nice)+stol(system)+stol(idle)+stol(iowait)+stol(irq)+stol(softirq) ; 
          return Jiffies; 
        }
       
      }
    }
  }
  return Jiffies;
  
 }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line;
  string key;
  string str;
  vector<string> part;
  string utime,stime,cutime,cstime,starttime;
  static long ActiveJiffies = 0;

  std::ifstream filestream(kProcDirectory +"/"+ to_string(pid) + kStatFilename);
  if (filestream.is_open()) {

    for (int i = 0; i<22;i++){
      filestream >> str;
      part.push_back(str);

    }
    utime = part[13];
    stime = part[14];
    ActiveJiffies = stol(utime)+stol(stime);
  }
  return ActiveJiffies; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  string line;
  string key;
  string user,nice,system,idle,iowait,irq,softirq;
  static long ActiveJiffies = 0;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      
      std::istringstream linestream(line);
      while (linestream >> key >> user>>nice>>system>>idle>>iowait>>irq>>softirq) {
        if (key == "cpu") {
         
          ActiveJiffies = stol(user)+stol(nice)+stol(system)+stol(irq)+stol(softirq) ; 
          return ActiveJiffies; 
        }
       
      }
    }
  }
  return ActiveJiffies;}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  string line;
  string key;
  string user,nice,system,idle,iowait,irq,softirq;
  static long IdleJiffies = 0;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      
      std::istringstream linestream(line);
      while (linestream >> key >> user>>nice>>system>>idle>>iowait>>irq>>softirq) {
        if (key == "cpu") {
          IdleJiffies = stol(idle)+stol(iowait) ; 
          return IdleJiffies; 
        }
       
      }
    }
  }
  return IdleJiffies; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization(int pid) { string line;
  string key;
  string str;
  vector<string> part;
  string utime,stime,cutime,cstime,starttime;
  static long StartTime;

  std::ifstream filestream(kProcDirectory +"/"+ to_string(pid) + kStatFilename);
  if (filestream.is_open()) {

    for (int i = 0; i<22;i++){
      filestream >> str;
      part.push_back(str);

    }

  }
  return part; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value;
  static int TotalProcess= 0;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
         
          TotalProcess = stoi(value) ; 
          return TotalProcess; 
        }
       
      }
    }
  }
  return TotalProcess; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  string value;
  static int RunningProcesses = 0;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
         
          RunningProcesses = stoi(value) ; 
          return RunningProcesses; 
        }
       
      }
    }
  }
  return RunningProcesses;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string Command;
  string line;
  std::ifstream stream(kProcDirectory + "/"+to_string(pid)+kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> Command;
  }
  return Command;
   }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {  
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + "/"+to_string (pid) +kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          long ram_kb = stoi(value);
          long ram_mb = 0.001*ram_kb;
          return to_string(ram_mb); 
        }
       
      }
    }
  } 
  }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  static string uid;
  

  std::ifstream filestream(kProcDirectory + "/"+to_string (pid) +kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      
      std::istringstream linestream(line);
      while (linestream >> key >> uid) {
        if (key == "Uid:") {
         
         
          return uid; 
        }
       
      }
    }
  }
   }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line;
  string user;
  string key;
  string connection = ":x:";
  

  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      
      std::istringstream linestream(line);
      while (linestream >> user>>connection>>key) {
        if (key == "1000") {
         
         
          return user; 
        }
       
      }
    }
  }

}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { string line;
  string key;
  string str;
  vector<string> part;
  string utime,stime,cutime,cstime,starttime;
  static long StartTime;

  std::ifstream filestream(kProcDirectory +"/"+ to_string(pid) + kStatFilename);
  if (filestream.is_open()) {

    for (int i = 0; i<22;i++){
      filestream >> str;
      part.push_back(str);

    }
    starttime= part[22];
    StartTime = stol(starttime);
  }
  return StartTime/sysconf(_SC_CLK_TCK); }
