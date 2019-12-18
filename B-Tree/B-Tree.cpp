
#include <iostream>
#include "BTree.h"
using namespace std;


int main()
{
    BTree tree(3);
  
    tree.insert(1); 
    tree.insert(3); 
    tree.insert(7); 
    tree.insert(10); 
    tree.insert(11); 
    tree.insert(13); 
    tree.insert(14); 
    tree.insert(15); 
    tree.insert(18); 
    tree.insert(16); 
    tree.insert(19); 
    tree.insert(24); 
    tree.insert(25); 
    tree.insert(26); 
    tree.insert(21); 
    tree.insert(4); 
    tree.insert(5); 
    tree.insert(20); 
    tree.insert(22); 
    tree.insert(2); 
    tree.insert(17); 
    tree.insert(12); 
    tree.insert(6); 
  
    cout << "Traversal of tree constructed is\n"; 
    tree.traverse(); 
    cout << endl; 
  
    tree.remove(6); 
    cout << "Traversal of tree after removing 6 \n"; 
    tree.traverse(); 
    cout << endl; 
  
    tree.remove(13); 
    cout << "Traversal of tree after removing 13\n"; 
    tree.traverse(); 
    cout << endl; 
  
    tree.remove(7); 
    cout << "Traversal of tree after removing 7\n"; 
    tree.traverse(); 
    cout << endl; 
  
    tree.remove(4); 
    cout << "Traversal of tree after removing 4\n"; 
    tree.traverse(); 
    cout << endl; 
  
    tree.remove(2); 
    cout << "Traversal of tree after removing 2\n"; 
    tree.traverse(); 
    cout << endl; 
  
    tree.remove(16); 
    cout << "Traversal of tree after removing 16\n"; 
    tree.traverse(); 
    cout << endl; 
  
    return 0; 
}
