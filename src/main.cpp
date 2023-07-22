#include <iostream>

#include "RBT.hpp"

using namespace std;

template<class KEY, class DATA>
void print_node(Node<KEY, DATA>* p_node) { cout << *p_node; }

int main() {
	RBT<int, int> rbt;

    rbt.insert(0, 1); 
    rbt.insert(1, 1);
    rbt.insert(2, 1);
    rbt.insert(3, 1);
    
    void (*f_ptr)(Node<int, int>*);
    f_ptr = print_node;

    rbt.in_order(rbt.get_root(), f_ptr);
	return 0;
}

