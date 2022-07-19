/*
 * @Author: yblin
 * @Date: 2021-09-22 16:57:32
 * @LastEditors: yblin
 * @LastEditTime: 2022-07-16 16:27:57
 * @Description: 
 */
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
using namespace std;

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

void fun(vector<int> res, TreeNode *root) {
  if (root == nullptr) {
    return;
  }
  fun(res, root->left);
  res.push_back(root->val);
  fun(res, root->right);
}

vector<int> inorderTraversal(TreeNode *root) {
  vector<int> res;
  fun(res, root);
  return res;
}

vector<vector<int>> levelOrder(TreeNode* root) {
  vector<vector<int>> res;
  if (root == nullptr) {
    return res;
  }
  queue<TreeNode *> q;
  TreeNode *cur;
  q.push(root);
  while (!q.empty()) {
    vector<int> row;
    int n = q.size();
    for (int i = 0; i < n; i++) {
      cur = q.front();
      q.pop();
      row.push_back(cur->val);
      if (cur->left != nullptr) {
        q.push(cur->left);
      }
      if(cur->right != nullptr){
        q.push(cur->right);
      }
    }
    res.push_back(row);
  }
  return res;
}

#pragma pack(4)
typedef struct MyDATA {
  char name;
  short age;
  char name1;
  int num;
} DATA;
#pragma pack()

int main() {
  // MyDATA data;
  // cout << " size: " << sizeof(data) << endl;
  // cout << " add: " << &data.name << endl;
  // cout << " add: " << &data.age << endl;
  // cout << " add: " << &data.name1 << endl;
  // cout << " add: " << &data.num << endl;
  int a = 2;
  int value = a > 1 ? a - 1 : 0;
  cout << " value: " << value << endl;

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
