#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include<iostream>
using std::string;
using std::to_string;
using std::vector;
Process::Process(int id):pid_(id){}
// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {return LinuxParser::ActiveJiffies(Pid());}

// TODO: Return the command that generated this process

string Process::Command() { 
  string cmd=LinuxParser::Command(Pid());
  
  return cmd;}


// TODO: Return this process's memory utilization

string Process::Ram() { 
  string ram=LinuxParser::Ram(Pid());
  int val=stoi(ram);
  
  
  return to_string(val/1024);  }

// TODO: Return the user (name) that generated this process

string Process::User() { 
  string user=LinuxParser::User(Pid());
  
  return user; }

// TODO: Return the age of this process (in seconds)

long int Process::UpTime() { 
  long int uptime=LinuxParser::UpTime(Pid());
  
  return uptime;  }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return (a.cpu_util > cpu_util); 

}