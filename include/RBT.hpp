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

    void insert(KEY p_key, DATA p_data) {
        Node<KEY, DATA>* ins_node = new Node(p_key, p_data);
        cout << *ins_node;
        _insert_case_1(ins_node);
    }

private:
    
    // find grandparent and uncle of a node
    Node<KEY, DATA>* _find_grandparent(Node<KEY, DATA>* p_node) {
        if (p_node != nullptr && p_node->get_parent() != nullptr) {
            return p_node->get_parent()->get_parent();
        } else {
            return nullptr;
        }
    }

    Node<KEY, DATA>* _find_uncle(Node<KEY, DATA>* p_node) {
        Node<KEY, DATA>* tmp_grandparent = _find_grandparent(p_node);

        if (tmp_grandparent == nullptr) {
            return nullptr;
        }

        if (p_node->get_parent() == tmp_grandparent->get_left()) {
            return tmp_grandparent->get_right();
        } else {
            return tmp_grandparent->get_left();
        }
    }

    // left, right rotation
    void _rotate_left(Node<KEY, DATA>* p_node) {
        Node<KEY, DATA>* pivot = p_node->get_right();

        pivot->set_parent(p_node->get_parent());
        if (p_node->get_parent() != nullptr) {
            if (p_node->get_parent()->get_left() == p_node) {
                p_node->get_parent()->set_left(pivot);
            } else {
                p_node->get_parent()->set_right(pivot);
            }
        }

        p_node->set_right(pivot->get_left());
        if (pivot->get_left() != nullptr) {
            pivot->get_left()->set_parent(p_node);
        }

        p_node->set_parent(pivot);
        pivot->set_left(p_node);
    }

    void _rotate_right(Node<KEY, DATA>* p_node) {
        Node<KEY, DATA>* pivot = p_node->get_left();

        pivot->set_parent(p_node->get_parent());
        if (p_node->get_parent() != nullptr) {
            if (p_node->get_parent()->get_left() == p_node) {
                p_node->get_parent()->set_left(pivot);
            } else {
                p_node->get_parent()->set_right(pivot);
            }
        }

        p_node->set_left(pivot->get_right());
        if (pivot->get_right() != nullptr) {
            pivot->get_right()->set_parent(p_node);
        }

        p_node->set_parent(pivot);
        pivot->set_right(p_node);
    }


    // insert cases
    void _insert_case_1(Node<KEY, DATA>* p_node) {
        if (p_node->get_parent() == nullptr) {
            _root = p_node;
            _root->set_color(BLACK);
        } else {
            _insert_case_2(p_node);
        }
    }

    void _insert_case_2(Node<KEY, DATA>* p_node) {
        if (p_node->get_parent()->get_color() == BLACK) {
            return;
        } else {
            _insert_case_3(p_node);
        }
    }

    void _insert_case_3(Node<KEY, DATA>* p_node) {
        Node<KEY, DATA>* tmp_uncle = _find_uncle(p_node), *tmp_grandparent;

        if ((tmp_uncle == nullptr) && (tmp_uncle->get_color() == RED)) {
            p_node->get_parent()->set_color(BLACK);
            tmp_uncle->set_color(BLACK);
            tmp_grandparent = _find_grandparent(p_node);
            tmp_grandparent->set_color(RED);
            _insert_case_1(tmp_grandparent);
        } else {
            _insert_case_4(p_node);
        }
    }

    void _insert_case_4(Node<KEY, DATA>* p_node) {
        Node<KEY, DATA>* tmp_grandparent = _find_grandparent(p_node);

        if ((p_node == p_node->get_parent()->get_right()) && (p_node->get_parent() == tmp_grandparent->get_right())) {
            _rotate_left(p_node->get_parent());
            p_node = p_node->get_left();
        } else if ((p_node == p_node->get_parent()->get_left()) && (p_node->get_parent() == tmp_grandparent->get_right())) {
            _rotate_right(p_node->get_parent());
            p_node = p_node->get_right();
        }

        _insert_case_5(p_node);
    }

    void _insert_case_5(Node<KEY, DATA>* p_node) {
        Node<KEY, DATA>* tmp_grandparent = _find_grandparent(p_node);

        p_node->get_parent()->set_color(BLACK);
        tmp_grandparent->set_color(RED);
        if ((p_node == p_node->get_parent()->get_left()) && (p_node->get_parent() == tmp_grandparent->get_left())) {
            _rotate_right(tmp_grandparent);
        } else {
            _rotate_left(tmp_grandparent);
        }
    }
};

