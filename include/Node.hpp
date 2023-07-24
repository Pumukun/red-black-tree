#pragma once

#include <iostream>
#include <string>

enum Color {
	BLACK,
	RED
};

std::string color_arr[2] = { "BLACK", "RED" };

template<class KEY, class DATA>
class Node {
protected:
	KEY _key;
	DATA _data;

	Color _color;

	Node<KEY, DATA>* _parent;
	Node<KEY, DATA>* _right;
	Node<KEY, DATA>* _left;

public:
	Node() = default;

	Node(KEY p_key, DATA p_data): _key(p_key), _data(p_data) {
        _left = nullptr;
        _right = nullptr;
        _parent = nullptr;
    }

	Node(
		KEY p_key, 
		DATA p_data, 
		Node<KEY, DATA>* p_parent, 
		Node<KEY, DATA>* p_right, 
		Node<KEY, DATA>* p_left, 
		Color p_color
	): 
		_key(p_key), 
		_data(p_data), 
		_parent(p_parent), 
		_right(p_right), 
		_left(p_left), 
		_color(p_color)
	{}
	
    void swapColor() {
        _color == BLACK ? _color = RED : _color = BLACK;
    }

	// getters
	KEY get_key() const { return _key; }
	DATA get_data() const { return _data; }

	Color get_color() { return _color; }

	Node<KEY, DATA>* get_parent() const { return _parent; }
	Node<KEY, DATA>* get_right() const { return _right; }
	Node<KEY, DATA>* get_left() const { return _left; }

	// setters
	void set_key(KEY p_key) { _key = p_key; }
	void set_data(DATA p_data) { _data = p_data; }

	void set_color(Color p_color) { _color = p_color; }

	void set_parent(Node<KEY, DATA>* p_parent) { _parent = p_parent; }
	void set_right(Node<KEY, DATA>* p_right) { _right = p_right; }
	void set_left(Node<KEY, DATA>* p_left) { _left = p_left; }

    friend std::ostream& operator<< (std::ostream& out, Node<KEY, DATA>& p_node) {
        out << "k: " << p_node._key << ", d: " << p_node._data << ", c: " << color_arr[p_node._color] << "\n";
        return out;
    }
};

