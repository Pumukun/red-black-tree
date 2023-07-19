#pragma once

#include <iostream>

#include "Node.hpp"

using namespace std;

template<class KEY, class DATA>
class RBT {
private:
	Node<KEY, DATA>* _root;
	Node<KEY, DATA>* _NIL;

	int _size;

public:

	RBT(): _size(0) {
		_NIL = new Node<KEY, DATA>(NULL, NULL, nullptr, nullptr, nullptr, BLACK);
		_root = _NIL;
	}

	~RBT() = default;

	Node<KEY, DATA>* get_root() const { return _root; }
	Node<KEY, DATA>* get_NIL() const { return _NIL; }

	int get_size() const { return _size; }
};

