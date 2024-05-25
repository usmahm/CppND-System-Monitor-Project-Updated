#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <fstream>
#include <string>
#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  double prev_idle_total_;
  double prev_non_idle_total_;
};

#endif