#include <iostream>
#include <experimental/random>
#include <vector>

#include "RBT.hpp"

using namespace std;
using namespace experimental;

int main() {
	RBT<string, string> rbt;
    
    rbt.insert("Ivanov", "Ivan");
    rbt.insert("Pirogov", "Alexander");
    rbt.insert("Sidorov", "Kiril");
    rbt.insert("Pavlov", "Pavel");
    rbt.insert("Mikhaylov", "Mikhail");

    rbt.in_order(rbt.get_root());

    cout << "\n\ntree find: " << *rbt.find("Pavlov");

    return 0;
}

