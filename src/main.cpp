#include <iostream>

#include "RBT.hpp"

using namespace std;

int main() {
	RBT<int, int> rbt;

    rbt.insert(0, 1); 
    rbt.insert(1, 1);
    rbt.insert(2, 1);
    rbt.insert(3, 1);
	return 0;
}

