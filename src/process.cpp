#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid) {
  long hertz = sysconf(_SC_CLK_TCK);

  user_ = LinuxParser::User(pid);
  ram_ = LinuxParser::Ram(pid);
  command_ = LinuxParser::Command(pid);

  // Process uptime calculation to seconds
  auto start_time = LinuxParser::UpTime(pid);
  up_time_ = start_time / hertz;

  // Process CPU Utilization calculation
  auto active_jiffies = LinuxParser::ActiveJiffies(pid_);
  long system_up_time = LinuxParser::UpTime(); 

  auto seconds = system_up_time - (start_time / hertz);

  double active_time = active_jiffies / hertz;
  double offset_seconds = seconds + 0.001;
  
  cpu_utilization_ = active_time / offset_seconds;
}

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_utilization_; }

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return up_time_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return (cpu_utilization_ < a.cpu_utilization_);
}

bool Process::operator>(Process const& a) const { 
  return (cpu_utilization_ > a.cpu_utilization_);
}