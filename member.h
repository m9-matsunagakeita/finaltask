#include<iostream>
#include<ctime>
#include<string>
#include <time.h>
#include <iomanip>
#include <sstream>

using namespace std;
char* strptime(const char* s,
    const char* f,
    struct tm* tm) {
    // Isn't the C++ standard lib nice? std::get_time is defined such that its
    // format parameters are the exact same as strptime. Of course, we have to
    // create a string stream first, and imbue it with the current C locale, and
    // we also have to make sure we return the right things if it fails, or
    // if it succeeds, but this is still far simpler an implementation than any
    // of the versions in any of the C standard libraries.
    std::istringstream input(s);
    input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
    input >> std::get_time(tm, f);
    if (input.fail()) {
        return nullptr;
    }
    return (char*)(s + input.tellg());
}


class Member {
private:
  string name;
  int age;
  time_t start;
  time_t end;
  string str_start;
  string str_end;
public:
  void set_name(string name);
  string get_name() {return this->name;};
  void set_age(int age);
  int get_age() {return this->age;};
  void set_start_time(string start);

  string get_start_time() {
    return this->str_start;
  };
  void set_end_time(string end);

  string get_end_time() {
    return this->str_end;
  };

  time_t get_start_timestamp(){
    return this->start;
  }

  time_t get_end_timestamp(){
    return this->end;
  }

  Member(string name, int age, string start, string end){
    struct tm tm;
    this->name = name;
    this->age = age;
    this->str_start = start;
    const char* char_start = start.c_str();
    if (strptime(char_start, "%Y-%m-%d %H:%M:%S", &tm) != NULL) {
      this->start = mktime(&tm);
    }
    this->str_end = end;
    const char* char_end = end.c_str();
    if (strptime(char_end, "%Y-%m-%d %H:%M:%S", &tm) != NULL) {
      this->end = mktime(&tm);
    }
  };
};

void Member::set_name(string name){
  this->name = name;
}
void Member::set_age(int age){
  this->age = age;
}
void Member::set_start_time(string start){
  struct tm tm;
  this->str_start = start;
  const char* char_start = start.c_str();
  if (strptime(char_start, "%Y-%m-%d %H:%M:%S", &tm) != NULL) {
    this->start = mktime(&tm);
  }
}

void Member::set_end_time(string end){
  struct tm tm;
  this->str_end = end;
  const char* char_end = end.c_str();
  if (strptime(char_end, "%Y-%m-%d %H:%M:%S", &tm) != NULL) {
    this->end = mktime(&tm);
  }
}
