#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
#include "member.h"
using namespace std;

time_t get_timestamp(string str){
  struct tm tm;
  const char* tmp = str.c_str();
  time_t ret;
  if (strptime(tmp, "%Y-%m-%d %H:%M:%S", &tm) != NULL) {
    return mktime(&tm);
  }
  return NULL;
}

int main(){
  string need_time_start ;
  string need_time_end ;
  cout << "足りないシフトの開始時間を入力" << endl;
  getline(cin, need_time_start);
  cout << "足りないシフトの終了時間を入力" << endl;
  getline(cin, need_time_end);
  cout << "WORK TIME START:" << need_time_start << endl;
  cout << "WORK TIME END  :" <<  need_time_end << endl;

  time_t timestamp_start = get_timestamp(need_time_start);
  time_t timestamp_end = get_timestamp(need_time_end);

  vector<Member> member_list;
  member_list.push_back(Member("松永", 22, "2013-06-15 12:00:00", "2014-12-08 12:00:00"));
  member_list.push_back(Member("江口", 20, "2015-06-15 12:00:00", "2016-12-08 12:00:00"));
  member_list.push_back(Member("藤田", 21, "2018-06-15 12:00:00", "2019-12-08 12:00:00"));
  member_list.push_back(Member("山本", 22, "2020-06-15 12:00:00", "2021-12-08 12:00:00"));

  vector<string> workable_member_list;
  for (auto itr = member_list.begin(); itr != member_list.end(); itr++) {
      Member member = *itr;
      if (member.get_start_timestamp() <= timestamp_start && timestamp_end <= member.get_end_timestamp()) {
          workable_member_list.push_back(member.get_name());
      }
  }

  cout << "シフトに入れるのは" << endl;
  for (auto itr = workable_member_list.begin(); itr != workable_member_list.end(); itr++) {
      cout << *itr << endl;
  }


  return 0;
}
