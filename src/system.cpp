#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

bool compare(Process& p1, Process& p2) {
  return p1 > p2;
}
// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  processes_ = {};
  auto pids = LinuxParser::Pids();

  for (auto id : pids) {
    Process process(id);
    processes_.push_back(id);
  }

  std::sort(processes_.begin(), processes_.end(), compare);

  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
  auto kernel_id  = LinuxParser::Kernel();
  return kernel_id; 
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
  float mem_usage = LinuxParser::MemoryUtilization();
  return mem_usage;  
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
  string os_name = LinuxParser::OperatingSystem();
  return os_name; 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
  int running_procs = LinuxParser::RunningProcesses();
  return running_procs;
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
  auto total_procs = LinuxParser::TotalProcesses();
  return total_procs;  
}

// TODO: Return the number of seconds since the system started running
long System::UpTime() { 
  long up_time = LinuxParser::UpTime();  
  return up_time;
}

// System::System() {
//   std::cout << "INITT " << "\n";
//   auto pids = LinuxParser::Pids();

//   for (auto id : pids) {
//     Process process(id);
//     processes_.push_back(id);
//   }
// }