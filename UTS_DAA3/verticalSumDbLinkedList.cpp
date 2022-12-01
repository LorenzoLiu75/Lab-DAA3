#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// struct utk menyimpan node binary tree
struct treeNode {
  
  int data;
  treeNode *left, *right;

  treeNode(int data) {

    this->data = data;
    this->left = this->right = nullptr;
  }
};

// struct untuk membuat doubly linked list node
struct linkedListNode {

  int data;
  linkedListNode *next, *prev;

  linkedListNode(int data, linkedListNode* prev, linkedListNode* next) {

    this->data = data;
    this->prev = prev;
    this->next = next;
  }
};

// fungsi untuk menghitung nilai masing-masing vertical sum dari binary tree
void verticalSumDoublyLL(treeNode* root, linkedListNode* sum) {

  // update nilai sum pada line yang sedang dikerjakan
  // dengan menambahkan nilai node yang sedang dituju
  sum->data += root->data;

  // rekursif untuk subtree sisi kiri
  if (root->left) {
    if (sum->prev == nullptr) {
      sum->prev = new linkedListNode(0, nullptr, sum);
    }
    verticalSumDoublyLL(root->left, sum->prev);
  }

  // rekursif untuk subtree sisi kanan
  if (root->right) {
    if (sum->next == nullptr) {
      sum->next = new linkedListNode(0, sum, nullptr);
    }
    verticalSumDoublyLL(root->right, sum->next);
  }
}

// fungsi untuk mencetak nilai vertical sum dari binary tree
void verticalSumDoublyLLPrint(treeNode *root) {

  // buat linked list node baru 
  linkedListNode* sum = new linkedListNode(0, nullptr, nullptr);

  // memanggil fungsi untuk menghitung nilai masing-masing vertical sum
  verticalSumDoublyLL(root, sum);

  // membuat pointer doubly linked list akan menunjuk ke node pertama yang ada pada list
  while (sum->prev != nullptr) {
    sum = sum->prev;
  }

  // mencetak vertical sum dari function verticalSum
  cout << "Nilai masing-masing vertical sum:\n";
  while (sum != nullptr) {
    cout << sum->data << " ";
    sum = sum->next;
  }
  
}

int main() {
  
  /* bentuk binary tree
            1
          /   \
         /     \
        2       3
      /       /   \
     /       /     \
   4        5       6
              \
               \
                7
   */

  auto start = high_resolution_clock::now();

  treeNode* root = new treeNode(1);
  root->left = new treeNode(2);
  root->right = new treeNode(3);
  root->left->left = new treeNode(4);
  root->right->left = new treeNode(5);
  root->right->right = new treeNode(6);
  root->right->left->right = new treeNode(7);

  verticalSumDoublyLLPrint(root);

  auto end = high_resolution_clock::now();

  auto total = duration_cast<microseconds>(end - start);
  cout << "\nTotal time execution: " << total.count() << " ms" << endl;

  return 0;
}