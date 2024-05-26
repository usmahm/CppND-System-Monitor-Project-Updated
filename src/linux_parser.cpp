#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <filesystem>
#include <unistd.h>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::getline;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
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
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
// vector<int> LinuxParser::Pids() {
//   vector<int> pids;
//   DIR* directory = opendir(kProcDirectory.c_str());
//   struct dirent* file;
//   while ((file = readdir(directory)) != nullptr) {
//     // Is this a directory?
//     if (file->d_type == DT_DIR) {
//       // Is every character of the name a digit?
//       string filename(file->d_name);
//       if (std::all_of(filename.begin(), filename.end(), isdigit)) {
//         int pid = stoi(filename);
//         pids.push_back(pid);
//       }
//     }
//   }
//   closedir(directory);
//   return pids;
// }

vector<int> LinuxParser::Pids() {
  vector<int> pids;

  for (auto const& dir_entry : std::filesystem::directory_iterator{kProcDirectory}) {
    if (dir_entry.is_directory()) {
      string filename{dir_entry.path().filename()};
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }

  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float mem_total, mem_free, mem_used, value;
  // float mem_buffers, mem_cached;
  float used_percentage;
  string line, key;

  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      std::stringstream ss(line);
      ss >> key >> value;

      if (key == "MemTotal:") {
        mem_total = value;
      }

      if (key == "MemFree:") {
        mem_free = value;

        mem_used = mem_total - mem_free;
        used_percentage = mem_used / mem_total;

        return used_percentage;
      }

      // if (key == "Buffers:") {
      //   mem_buffers = value;
      // }

      // if (key == "Cached:") {
      //   mem_cached = value;


      //   mem_used = mem_total - mem_free;
      //   used_percentage = (mem_used - mem_buffers - mem_cached) / mem_total;

      //   return used_percentage;
      // }
    }
  }

  return used_percentage;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long uptime{0};
  string line;

  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    if (getline(stream, line)) {
      std::istringstream ss(line);
      ss >> uptime;
    }
  }

  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

int LinuxParser::ReadProcessesFromStatFile(std::string key_to_read) {
  string line, key;
  int value;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (getline(stream, line))
    {
      std::stringstream ss(line);

      ss >> key >> value;
      if (key == key_to_read) {
        return value;
      }
    }
  }

  return value; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  int value = ReadProcessesFromStatFile("processes");
  return value;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  int value = ReadProcessesFromStatFile("procs_running");
  return value;
}

string LinuxParser::ReadValFromPidStatusFile(int pid, string key_to_read) {
  string key, value;
  string line;

  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (getline(stream, line))
    {
      std::stringstream ss(line);

      ss >> key >> value;
      if (key == key_to_read) {
        return value;
      }
    }
    
  }

  return string();
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;

  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    if (getline(stream, line))
    {
      return line;
    }
  }

  return "Nill";
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string memory_kb = ReadValFromPidStatusFile(pid, "VmSize:");

  if (memory_kb.empty())
    return memory_kb;
  
  string memory_mb = to_string(std::stol(memory_kb) / 1000);
  return memory_mb;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string uid = ReadValFromPidStatusFile(pid, "Uid:");
  return uid;  
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string username, x, value;
  string line;

  string u_id = Uid(pid);

  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (getline(stream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');

      std::stringstream ss(line);
      ss >> username >> x >> value;

      if (value == u_id) {
        return username;
      }
    }
  }

  return "Nill";
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line;
  string others;
  long value;

  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    if (getline(stream, line)) {
      std::stringstream ss(line);

      int count = 1;
      while (ss >> others) {
        count += 1;

        if (count == 22)
          break; 
      }

      ss >> value;
      return (value / sysconf(_SC_CLK_TCK));
    }
  }

  return value;
}