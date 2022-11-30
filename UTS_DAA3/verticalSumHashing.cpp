#include <iostream>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

// struktur utk menyimpan node binary tree
struct Node {

  int data;
  Node *left, *right;

  Node(int data) {
    this->data = data;
    this->left = this->right = nullptr;
  }
};

// melintasi tree dengan metode post-order
void verticalSum(Node* root, int hDist, map<int,int> &Map) { // hDist = horizontal distance

  if (root == nullptr) return; // base case

  // rekursif utk subtree sisi kiri
  verticalSum(root->left, hDist - 1, Map);


  // rekursif utk subtree sisi kanan
  verticalSum(root->right, hDist + 1, Map);

  // update map
  Map[hDist] += root->data;
}

void verticalSumPrint(Node *root) {

  // buat sebuah map untuk menyimpan jumlah node utk tiap
  // jarak horizontal (horizontal distance)
  map <int,int> Map;
  map <int,int> :: iterator i; // menandai iterasi

  // mengisi map
  verticalSum(root, 0, Map);

  // mencetak vertical sum dari function verticalSum
  cout << "Position \tSum" << endl;
  for (i = Map.begin(); i != Map.end(); i++) {
    
    cout << "  " << i->first << "\t\t " << i->second << endl;
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

  Node* root = new Node(1);
  root->left = new Node(2);
  root->right = new Node(3);
  root->left->left = new Node(4);
  root->right->left = new Node(5);
  root->right->right = new Node(6);
  root->right->left->right = new Node(7);

  verticalSumPrint(root);

  auto end = high_resolution_clock::now();

  auto total = duration_cast<microseconds>(end - start);
  cout << "Total time execution: " << total.count() << " ms" << endl;

  return 0;
}