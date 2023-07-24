#include <iostream>
#include <experimental/random>
#include <vector>

#include "RBT.hpp"

using namespace std;
using namespace experimental;

int main() {
	RBT<int, int> rbt;
    
    for (int i = 0; i < 30; i++) {
        rbt.insert(randint(-50, 50), randint(-10, 10));
    }
    
    rbt.print_tree(rbt.get_root());
    
    /*
    vector<Node<int, int>> nodes = rbt.get_nodes();
    
    for (Node<int, int> &i : nodes) {
        rbt.remove(i.get_key());
        rbt.print_tree(rbt.get_root());
        cout << "---------------------------------------------\n";
    }
    */
    
    /*
    RBT<int, int>::tree_iterator iter = rbt.begin();
    while (iter != rbt.end()) {
        cout << *iter;
        iter++;
    } cout << *iter;
    */
    return 0;
}

