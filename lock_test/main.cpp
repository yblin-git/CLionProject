/*
 * @Author: yblin
 * @Date: 2021-02-08 10:51:22
 * @LastEditors: yblin
 * @LastEditTime: 2021-09-14 17:04:40
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

/**
 *  格式化给定日期
 */
inline string FormatDate(time_t time,
                         const string& format = "%Y-%m-%d_%H-%M-%S") {
  char str[255];
  std::strftime(str, 255, format.c_str(), localtime(&time));
  return string(str);
}
/**
 *  获取当前系统日期
 */
inline string CurrentSystemDate(string format = "%Y-%m-%d_%H-%M-%S") {
  static string kMs = "%MS";
  static size_t kSize = kMs.size();
  int index = format.find(kMs);
  if (index >= 0) {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    std::stringstream ss;
    ss.fill('0');
    ss << std::setw(3) << tv.tv_usec / 1000;
    format.replace(index, kSize, ss.str());
  }
  auto time =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  return FormatDate(time, format);
}
class Test1 {

 public:
  int code_;

  Test1(int code);
  ~Test1();
};

Test1::Test1(int code) : code_(code) {}

Test1::~Test1()
{
}


class LockTest{
public:
    LockTest(){
        // sync_time_thread_.reset(new std::thread([&](){
        //     sleep(2);
        //     while (1){
        //         mutex_.lock();
        //         std::cout<<"lock"<<std::endl;
        //         condition_.notify_all();
        //         mutex_.unlock();
        //         std::cout<<"unlock"<<std::endl;
        //         sleep(2);
        //     }
        // }));
        // sync_time_thread_1.reset(new std::thread([&](){
        //     while (1){
        //         {
        //             std::unique_lock<std::mutex> lock(mutex_);
        //             std::cout<<"lock1"<<std::endl;
        //             std::cv_status status = condition_.wait_for(
        //                     lock, std::chrono::seconds(10));
        //         }
        //         std::cout<<"unlock1"<<std::endl;
        //     }
        // }));
    }
    ~LockTest() { std::cout << "~LockTest" << std::endl; }
    std::shared_ptr<Test1> Test(int code) {
      std::cout << "LockTest: " << code << std::endl;
      auto test = std::make_shared<Test1>(code);
      std::unique_lock<std::mutex> lock(mutex_);
      ser_map_.insert(std::make_pair(code, nullptr));
      std::cout << "lock1" << std::endl;
      std::cv_status status =
          condition_.wait_for(lock, std::chrono::seconds(2));
      if (status == std::cv_status::timeout) {
        std::cout << "timeout" << std::endl;
        test->code_ = 100;
      } else if (status == std::cv_status::no_timeout) {
        std::cout << "no_timeout: " << code << std::endl;
        auto iter = ser_map_.find(code);
          // std::cout << "iter: " << iter->second->code_ << std::endl;
          if (iter != ser_map_.end() && iter->second != nullptr) {
            test = iter->second;
            std::cout << "notify ok: " << std::endl;
          } else {
            std::cout << "iter ser_map_.end: " << std::endl;
          }
      }
      std::cout << "unlock1: " << code << std::endl;
      std::cout << "test code: " << test->code_ << std::endl;
      ser_map_.erase(code);

      return test;
    }
    void notify(int code) {
      std::cout << "notify: " << code << std::endl;
      std::unique_lock<std::mutex> lock(mutex_);
      if (ser_map_.find(code) != ser_map_.end()) {
        std::cout << "find map: " << code << std::endl;
        ser_map_[code] = std::make_shared<Test1>(10);
        condition_.notify_all();
      } else {
        std::cout << "not find map" << code << std::endl;
      }
    }

   private:
    std::mutex mutex_;
    std::condition_variable condition_;
    std::unique_ptr<std::thread> sync_time_thread_;
    std::unique_ptr<std::thread> sync_time_thread_1;
    std::map<int, std::shared_ptr<Test1>> ser_map_;
};
typedef std::unordered_map<std::string, std::unordered_set<int>> PubSubMap;

namespace a_space
{
class A {
 private:
  /* data */
 public:
  A(/* args */);
  ~A();
  virtual void printf() { std::cout << "A printf" << std::endl; }
};

A::A(/* args */) {}

A::~A() {}
} // namespace a_space

namespace b_space
{
using a_space::A;
class B : public A {
 private:
  /* data */
 public:
  B(/* args */);
  ~B();
  void printf() override { std::cout << "B printf" << std::endl; }
};

B::B(/* args */) {}

B::~B() {}
} // namespace b_space

static void printf(a_space::A a) { a.printf(); }
static void printf(std::shared_ptr<a_space::A>& a) { a->printf(); }

int main() {
    std::cout << "Hello, World!" << std::endl;
    // LockTest test_lock;
    std::unordered_map<std::string, int> ser_map_;
    // ser_map_.insert(std::make_pair(1, 1));
    // ser_map_.insert(std::make_pair(2, 2));
    ser_map_["3"] = 3;
    // ser_map_.insert(std::make_pair(4, 4));
    // ser_map_.insert(std::make_pair(5, 5));
    // ser_map_.insert(std::make_pair(6, 6));
    for (auto iter = ser_map_.begin(); iter != ser_map_.end(); ++iter) {
      std::cout << " session_map_ size : " << ser_map_.size() << std::endl;
      if (iter->second == 3) {
        ser_map_.erase(iter);
      }
    }
    std::cout << " session_map_ size : " << ser_map_.size() << std::endl;

    // std::unique_ptr<std::thread> thread_;
    // std::unique_ptr<std::thread> thread1_;
    // std::unique_ptr<std::thread> thread2_;
    // std::shared_ptr<Test1> test1;
    // std::shared_ptr<Test1> test2;
    // thread_.reset(new std::thread([&]() {
    //   test_lock.Test(1);

    //   //   test1 = test_lock.Test(1);
    //   //   std::cout << "test1 code: " << test1->code_ << std::endl;
    // }));

    // thread1_.reset(new std::thread([&]() {
    //   test_lock.Test(1);

    //   //   test2 = test_lock.Test(1);
    //   //   std::cout << "test2 code: " << test2->code_ << std::endl;
    // }));
    // thread2_.reset(new std::thread([&]() {
    //   usleep(500 * 1000);
    //   test_lock.notify(1);
    // }));
    b_space::A a;
    auto aa = std::make_shared<b_space::A>(a);
    std::cout << "CurrentSystemDate: " << CurrentSystemDate("%Y-%m-%d_%H-%M-%S-%MS")
              << std::endl;
    while (1) {
      sleep(1); }
    return 0;
}
