/*
 * @Author: yblin
 * @Date: 2021-02-08 10:51:22
 * @LastEditors: yblin
 * @LastEditTime: 2021-09-22 17:31:04
 * @Description: 
 */
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
class FunA;
class Test {
 public:
  Test(int type);
  ~Test();
  void fun1();
  void set_type(int type);
  int type();

 private:
  std::shared_ptr<FunA> fun_a_;
  int type_;
};

class Test1 : public Test {
 private:
  int times_;
 public:
  Test1(int type);
  ~Test1();
  void add() ;
  int times() ;

};

class Test2 : public Test {
 private:
  int times_;

 public:
  Test2(int type);
  ~Test2();
  void add() ;
  int times() ;
};

class FunA {
 private:
  /* data */
 public:
  FunA(/* args */);
  ~FunA();
  void test_add(Test *test) ;
};