#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <iostream>
#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  

  // TODO: Declare any necessary private members
 private:
  long Jiffies = LinuxParser::Jiffies();
  long ActiveJiffies = LinuxParser::ActiveJiffies();
  long IdleJiffies = LinuxParser::IdleJiffies();
};

#endif