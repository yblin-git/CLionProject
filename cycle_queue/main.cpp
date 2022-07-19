#include <iostream>
#include <mutex>
#include <deque>
#include <vector>
#include <bitset>
#include "File.h"
#include <queue>
using namespace std;
using common_data::File;

template <class T>
class CycleQueue {
 public:
  CycleQueue(size_t size)
      : m_size(size + 1), m_front(0), m_rear(0), m_data(m_size) {}
  ~CycleQueue() {}

  bool empty() { return m_front == m_rear; }

  bool isFull() { return m_front == (m_rear + 1) % m_size; }
  //获取队列中元素的个数
  int size() { return (m_rear - m_front + m_size) % m_size; }
  //获取队列元素, 不出队
  T& operator[](int offset) {
    // CHECK(offset < m_size) << offset << " " << m_size;
    return m_data[(m_front + offset) % m_size];
  }
  T front() {
    // CHECK(!empty());
    return m_data[m_front];
  }
  T back() {
    // CHECK(!empty());
    return m_data[(m_rear - 1 + m_size) % m_size];
  }
  int push_back(T ele) {
    if (isFull()) {
      m_front = (m_front + 1) % m_size;
    }
    m_data[m_rear] = ele;
    m_rear = (m_rear + 1) % m_size;
    return 0;
  }
  int push_front(T ele) {
    if (isFull()) {
      return -1;
    }
    m_front = (m_front - 1 + m_size) % m_size;
    m_data[m_front] = ele;
    return 0;
  }

  void pop_back() {
    // CHECK(!empty());
    m_rear = (m_size + m_rear - 1) % m_size;
  }
  void pop_front() {
    // CHECK(!empty());
    m_front = (m_front + 1) % m_size;
  }

 private:
  size_t m_size;
  int m_front;
  int m_rear;
  std::vector<T> m_data;
};

class A{
public:
    A():q(20){
        q.empty();
    }
private:
    CycleQueue<int> q;
};

struct Result {
    bool is_succeed;
    double theta;
};
int main() {
    Result result = {true,1.1};
    std::cout << "result: !" << result.is_succeed<<result.theta<<std::endl;

    std::deque<int> std_q;
    std_q.push_back(1);
    std_q.push_back(2);
    std_q.push_back(3);
    std_q.push_back(4);
    std_q.push_back(5);
//    std::cout << "std_q front" << std_q.front()<<std::endl;
//    std::cout << "std_q front" << std_q.front()<<std::endl;
    std::cout << "std_q  " << std_q[6]<<std::endl;


    int a=0;
    std::cout << "Hello, World!" << std::endl;
    CycleQueue<int> q(5);
    q.push_back(1);
    q.push_back(2);
    q.push_back(3);
    q.push_back(4);
    q.push_back(5);
    q.push_back(6);
    auto ret = q.push_front(5);
    cout << "ret " << ret << endl;

    cout <<"front " <<q[0] << endl;
    cout <<"back " <<q[1] << endl;

    int length = q.size();
    cout <<"length" <<length << endl;
    for (int i = 0; i < length; i++){
        a = q.front();
        q.pop_front();
        cout << a << endl;

    }
    q.push_back(5);
    q.push_back(6);
    q.push_front(7);
     length = q.size();
    cout <<"length" <<length << endl;

    for (int i = 0; i < length ; i++){
        a = q.front();
        q.pop_front();
        cout << "1 " << a << endl;
    }
    length = q.size();
    cout <<"length" <<length << endl;
    q.push_back(1);
    length = q.size();
    cout <<"length" <<length << endl;
    q.push_back(2);
    length = q.size();
    cout <<"length" <<length << endl;
    q.push_back(3);
    length = q.size();
    cout <<"length" <<length << endl;
    q.push_back(4);
     length = q.size();
    cout <<"length" <<length << endl;

    for (int i = 0; i < length ; i++) {
        cout <<"data: " <<q[i]<< endl;
    }

    for (int i = 0; i < length; i++) {
      a = q.front();
      q.pop_front();
      cout << "1 " << a << endl;
    }

    File record_file("/tmp/test.file");
    cout <<"file name: " <<record_file.GetFileName()<<" size: "<<record_file.Size()<<endl;
    std::bitset<32> used;
    used.set(2);
    cout <<"used: " <<used<<endl;
    cout <<"used: " <<used.none()<<endl;

    std::vector<int> data_test;
    data_test.reserve(2);
//    data_test.push_back(1);
//    data_test.push_back(2);
//    data_test.push_back(3);
//    data_test.push_back(4);
    for ( auto var:data_test) {
        cout <<"data_test: " <<var<<endl;
    }

    int state =0;
    cout <<"size: " <<sizeof(int)<<endl;

    CycleQueue<int> q1(5);
    q1.push_back(1);
    q1.push_back(2);
    q1.push_back(3);
    q1.push_back(4);
    q1.push_back(5);
    q1.push_back(6);

    length = q1.size();
    cout << "length" << length << endl;
    for (int i = 0; i < length; i++) {
      a = q1.front();
      q1.pop_front();
      cout << a << endl;
    }
    q1[0] = 10;
    cout << "length" << length << endl;
    for (int i = 0; i < length; i++) {
      a = q1.front();
      q1.pop_front();
      cout << a << endl;
    }

    int a1 =2;
    int b1 =2;

    auto c1 = (a1 + b1) >> 1;

    cout << "length" << c1 << endl;

    std::queue<int> q;

    return 0;
}
