/*
 * @Author: yblin
 * @Date: 2021-09-22 16:57:32
 * @LastEditors: yblin
 * @LastEditTime: 2022-07-12 16:38:59
 * @Description: 
 */
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
using namespace std;

/*map内部有排序机制，它是有序的，当map存结构体或者存类的时候，要重载operator <
 * 运算符函数
*/

class A {
  int id;
  string name;

 public:
  virtual void test() { cout << "A::test()" << endl; }
  bool operator<(const A &a) const { return id < a.id; }
};

struct B {
  int id;
  string name;
  B() {}
  B(int x, string y) : id(x), name(y) {}
  bool operator<(const B &a) const { return id < a.id; }
};

//严蔚敏《数据结构》标准分割函数
int Paritition1(int A[], int low, int high) {
  int pivot = A[low];
  int start = low;
  while (low < high) {
    while (low < high && A[high] >= pivot) {
      --high;
    }
    // std::cout << " A[low] " << A[low] << " A[high] " << A[high] << std::endl;
    // A[low] = A[high];

    while (low < high && A[low] <= pivot) {
      ++low;
    }
    // std::cout << " A[high] " << A[high] << " A[low] " << A[low] << std::endl;
    // A[high] = A[low];
    if (low < high) {
      std::swap(A[low], A[high]);
    }
  }
  std::swap(A[start], A[low]);

  for (size_t i = 0; i < 10; i++) {
    std::cout << A[i] << " ";
  }
  std::cout << std::endl;
  std::cout << " A[low] " << A[low] << " pivot " << pivot << std::endl;
  A[low] = pivot;

  return low;
}

void QuickSort(int A[], int low, int high)  //快排母函数
{
  if (low < high) {
    int pivot = Paritition1(A, low, high);
    QuickSort(A, low, pivot - 1);
    QuickSort(A, pivot + 1, high);
  }
}
int main() {
  // int a[10] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
  // QuickSort(a, 0, 9);
  // for (size_t i = 0; i < 10; i++)
  // {
  //   std::cout << a[i] << " ";
  // }
  // std::cout << std::endl;
  int n;
  std::cout << "***************" << n << std::endl;
  while (std::cin >> n) {
    std::cout << "***************" << n << std::endl;
  }
  return 0;
}

// ListNode* ReverseList(ListNode* pHead) {
//   ListNode* newHead = nullptr;
//   while (pHead != nullptr) {
//     ListNode* temp = pHead->next;
//     pHead->next = newHead;
//     newHead = pHead;
//     pHead = temp;
//   }
//   return newHead;
// }
