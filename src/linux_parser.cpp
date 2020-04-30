#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::stoi;
using std::stol;
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
  string os, kernel,version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >>version>> kernel;
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
  std::string line;
  std::string key;
  std::string value;
  std::string unit;
  float memtotal;
  float memfree;
  //float memavail;
  //float buff;
std::ifstream fs(kProcDirectory+kMeminfoFilename);  
  if(fs.is_open()){
    while (std::getline(fs, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value >> unit){
        if (key == "MemTotal"){
          memtotal=stof(value);
        }
        else if(key =="MemFree"){
        memfree=stof(value);
        }
        /*else if(key =="MemAvailable"){
        memavail=stof(value);
        }
        else if(key =="Buffers"){
          buff=stof(value);
        }*/
      }
    }
    
    
  }
  
  
  return (memtotal-memfree)/memtotal; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  std::string line;
  std::string uptime;
  std::string idletime;
  long up_time;
  std::ifstream f_s(kProcDirectory+kUptimeFilename);
  if (f_s.is_open()){
    std::getline(f_s, line);
    std::istringstream l_s(line);
    l_s>>uptime>>idletime;
    up_time=stol(uptime);   
  }
  return up_time; }

// TODO: Read and return the number of jiffies for the system
//long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::ActiveJiffies(int pid) { 
  string utime;
  string line;
  string Stime;
  string cutime;
  string cstime;
  long total;
  string value;
  long uptime=LinuxParser::UpTime();
  long starttime=UpTime(pid);
  
 std::string PID=to_string(pid);
  std::ifstream file(kProcDirectory+PID+kStatFilename);
   if(file.is_open()){
   while (std::getline(file, line)){
  std::istringstream linestream(line);
     for(int i=0;i<17;i++){
       linestream>>value;
       if(i==13){
         utime=value;
       }
       if(i==14){
         Stime=value;
       }
       if(i==15){
         cutime=value;
       }
       if(i==16){
         cstime=value;
       }
     }
   }
   
   }
  
  total=stol(utime)+stol(Stime)+stol(cutime)+stol(cstime);
  float sec=uptime-(starttime/sysconf(_SC_CLK_TCK));
  float cpu_usage;
  cpu_usage=((total/sysconf(_SC_CLK_TCK))/sec)*100;
  
  return cpu_usage; }

// TODO: Read and return the number of active jiffies for the system
//long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
//long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string>cpu_data;
  std::string line;
  string cpu, user, nice, system, idle, iowait, irq, softirq, steal, guest,guest_nice;
  std::ifstream file(kProcDirectory+kStatFilename);
  if (file.is_open()){
    std::getline(file, line);
    std::istringstream linestream(line);
  linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >>softirq >> steal >> guest >> guest_nice;
    //vector<string>cpu_data;
    cpu_data.push_back(user);
    cpu_data.push_back(nice);
    cpu_data.push_back(system);
    cpu_data.push_back(idle);
    cpu_data.push_back(iowait);
    cpu_data.push_back(irq);
    cpu_data.push_back(softirq);
    cpu_data.push_back(steal);
    cpu_data.push_back(guest);
    cpu_data.push_back(guest_nice);
  
  }
  return cpu_data; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::string line;
  std::string pcs;
  std::string value;
  int processes;
  std::ifstream file(kProcDirectory+kStatFilename);
  if (file.is_open()){
    while (std::getline(file, line)){
      std::istringstream linestream(line);
      while (linestream >> pcs >> value){
        if(pcs=="processes"){
        processes=stoi(value);
        }
      }
    }
  }
  return processes; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::string line;
  std::string rpcs;
  std::string value;
  int running_processes;
  std::ifstream file(kProcDirectory+kStatFilename);
  if (file.is_open()){
    while (std::getline(file, line)){
      std::istringstream linestream(line);
      while (linestream >> rpcs >> value){
        if(rpcs=="procs_running"){
        running_processes=stoi(value);
          return running_processes;
        }
      }
    }
  }
  return -1;
  }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::string PID=to_string(pid);
  std::ifstream file(kProcDirectory+PID+kCmdlineFilename);
  if (file.is_open()) {
    std::getline(file, line);
  }
  return line; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
   string line;
  string value;
  string key;
  //int v;
  
  std::string PID=to_string(pid);
  std::ifstream file(kProcDirectory+PID+kStatusFilename);
  if(file.is_open()){
    while (std::getline(file, line)){
  std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize") {
         return value;
        }
      }
    }
  }
 return value;
   }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string key;
  string value;
  string line;
 std::string PID=to_string(pid);
  std::ifstream file(kProcDirectory+PID+kStatusFilename);
   if(file.is_open()){
    while (std::getline(file, line)){
  std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid") {
  return value;
        }
      }
      
    }
  }
  return "-1";
}
// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string key;
  string unit;
  string value;
  string line;
  string uid;
 std::string PID=to_string(pid);
  uid=LinuxParser::Uid(pid);
  std::ifstream file(kPasswordPath);
   if(file.is_open()){
    while (std::getline(file, line)){
  std::replace(line.begin(), line.end(), ':', ' ');
      std::replace(line.begin(), line.end(), ',', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> unit>>value) {
        if (value == uid) {
  return key;
        }
      }
    }
   }
return "-1";
 }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  //string key;
  string value;
  string line;
  
 std::string PID=to_string(pid);
  std::ifstream file(kProcDirectory+PID+kStatFilename);
   if(file.is_open()){
   while (std::getline(file, line)){
  std::istringstream linestream(line);
     for(int i=0;i<22;i++){
       linestream>>value;
     }
   }
   }
  
  return (stol(value)/sysconf(_SC_CLK_TCK)); }
