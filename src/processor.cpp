#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float utilization = 0;
    utilization = float(ActiveJiffies)/float(Jiffies);
    return utilization;
 }