/*
 * @Author: yblin
 * @Date: 2021-02-08 10:51:22
 * @LastEditors: yblin
 * @LastEditTime: 2021-09-22 17:29:28
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
#include "test.h"
using namespace std;
void Test::fun1() { fun_a_->test_add(this); }
void Test::set_type(int type) { type_ = type; }
int Test::type() { return type_; }
Test::Test(int type) : type_(type) { fun_a_ = std::make_shared<FunA>(); }
Test::~Test() {}

void Test1::add() { times_ = 1; }
int Test1::times() { return times_; }
Test1::Test1(int type) : Test(type) {}
Test1::~Test1() {}

void Test2::add() { times_ = 2; }
int Test2::times() { return times_; }
Test2::Test2(int type) : Test(type) {}
Test2::~Test2() {}

void FunA::test_add(Test *test) {
  if (test->type() == 1) {
    auto test1 = static_cast<Test1 *>(test);
    test1->add();
    std::cout << "test1" << test1->times() << std::endl;
  } else if (test->type() == 2) {
    auto test2 = static_cast<Test2 *>(test);
    test2->add();
    std::cout << "test2" << test2->times() << std::endl;
  }
}

FunA::FunA(/* args */) {}

FunA::~FunA() {}