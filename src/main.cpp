#include <iostream>

#include "RBT.hpp"

using namespace std;

int main() {
	RBT<int, int> rbt;

    rbt.insert(0, 1); 
    rbt.insert(1, 1);
    rbt.insert(4, 1);
    rbt.insert(3, 1);
    rbt.insert(10, 0);
    rbt.insert(-2, 2);
    
    rbt.print_tree(rbt.get_root());
	return 0;
}

