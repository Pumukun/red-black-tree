#pragma once

#include <iostream>
#include <vector>

#include "Node.hpp"

using namespace std;

template<class KEY, class DATA>
class RBT {
private:
    Node<KEY, DATA>* _root;

    int _size;

    vector<Node<KEY, DATA>> _nodes;

public:

    class tree_iterator;

    RBT(): _size(0) {
        _root = nullptr;
    }

    ~RBT() = default;

    Node<KEY, DATA>* get_root() const { return _root; }

    int get_size() const { return _size; }

    vector<Node<KEY, DATA>> get_nodes() { return _nodes; }

    void insert(KEY p_key, DATA p_data) {
        Node<KEY, DATA>* new_node = new Node(p_key, p_data);

        _size++;

        Node<KEY, DATA>* x = _root, *y = nullptr;

        while (x != nullptr)
        {
            y = x;
            if (p_key < x->get_key()) {
                x = x->get_left();
            } else {
                x = x->get_right();
            }
        }

        new_node->set_parent(y);

        if (y == nullptr) {
            _root = new_node;
        } else if (p_key < y->get_key()) {
            y->set_left(new_node);
        } else {
            y->set_right(new_node);
        }

        _nodes.push_back(*new_node);

        _insert_case_1(new_node);
    }
    
    void remove(KEY p_key) { 
        _delete_node(p_key);
    }

    // < ==== Find block ==== >
    Node<KEY, DATA>* find(KEY p_key) {
        return _find_r(p_key, _root);
    }

    Node<KEY, DATA>* find_min(Node<KEY, DATA>* p_node = nullptr) {
        if (_root == nullptr) { return nullptr; }
        if (p_node == nullptr) {
            p_node = _root;
        }
        while (p_node->get_left() != nullptr) {
            p_node = p_node->get_left();
        }
        return p_node;
    }    

    Node<KEY, DATA>* find_max(Node<KEY, DATA>* p_node = nullptr) {
        if (_root == nullptr) { return nullptr; }
        if (p_node == nullptr) {
            p_node = _root;
        }
        while (p_node->get_right() != nullptr) {
            p_node = p_node->get_right();
        }
        return p_node;
    }

    // < ==== Tree iterator ==== > //
    class tree_iterator {
    private:

        Node<KEY, DATA>* ptr;

    public:

        tree_iterator() { ptr = nullptr; }

        tree_iterator(Node<KEY, DATA> *p_node): ptr(p_node) {}

        tree_iterator(const tree_iterator &it) { ptr = it.ptr; }

        Node<KEY, DATA>* find_min(Node<KEY, DATA>* p_node = nullptr) {
            if (ptr == nullptr) return nullptr;
            if (p_node == nullptr)
                p_node = ptr;
            while (p_node->get_left() != nullptr)
                p_node = p_node->get_left();
            return p_node;        
        }    

        Node<KEY, DATA>* find_max(Node<KEY, DATA>* p_node = nullptr) {
            if (ptr == nullptr) return nullptr;
            if (p_node == nullptr)
                p_node = ptr;
            while (p_node->get_right() != nullptr)
                p_node = p_node->get_right();
            return p_node;
        }


        Node<KEY, DATA>& operator++ (int) {
            if (ptr == nullptr)
                throw std::out_of_range("iterator ptr is null");

            if (ptr->get_right() != nullptr)
                ptr = find_min(ptr->get_right());
            else {
                if (ptr->get_parent() == nullptr)
                    return *ptr;

                Node<KEY, DATA> *current = ptr->get_parent();

                while (current->get_parent() != nullptr && current->get_key() <= ptr->get_key())
                    current = current->get_parent();
                if (current->get_key() > ptr->get_key())
                    ptr = current;
            }
            return *ptr;
        }

        Node<KEY, DATA>& operator-- (int) {
            if (ptr == nullptr)
                throw std::out_of_range("iterator ptr is null");

            if (ptr->get_left() != nullptr)
                ptr = find_max(ptr->get_left());
            else {
                if (ptr->get_parent() == nullptr)
                    return *ptr;

                Node<KEY, DATA> *current = ptr->get_parent();

                while (current->get_parent() != nullptr && current->get_key() > ptr->get_key())
                    current = current->get_parent();
                if (current->get_key() < ptr->get_key())
                    ptr = current;
                }
                return *ptr;
            }

        Node<KEY, DATA>& operator* () {
            if (ptr == nullptr)
                throw std::out_of_range("iterator ptr is null");
            return *ptr;
        }

        bool operator!= (const tree_iterator& p_it) { return ptr != p_it.ptr; }

        bool operator== (const tree_iterator& p_it) { return ptr == p_it.ptr; }
    };

    friend class tree_iterator;

    tree_iterator begin() { 
        auto it = find_min(_root);
        return it; 
    }

    tree_iterator end() { 
        auto it = find_max(_root);
        return it; 
    }

private:

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

    Node<KEY, DATA>* _find_brother(Node<KEY, DATA>* p_node) {
        if (p_node == p_node->get_parent()->get_left()) {
            return p_node->get_parent()->get_right();
        } else {
            return p_node->get_parent()->get_left();
        }
    }

    // < ==== get_left(), get_right() rotation ==== > //
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


    // < ==== Insert Cases ==== > //
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


    // < ==== Find recursive ==== > //
    Node<KEY, DATA>* _find_r(KEY p_key, Node<KEY, DATA>* cur_node) {
        if (cur_node == nullptr) {
            return nullptr;
        }
        if (cur_node->get_key() == p_key) {
            return cur_node;
        }
        if (cur_node->get_key() > p_key) {
            return _find_r(p_key, cur_node->get_left());
        }
        if (cur_node->get_key() < p_key) {
            return _find_r(p_key, cur_node->get_right());
        }
    }


    // < ==== Deletion block ==== > //
    void _delete_node(KEY p_key) {
        Node<KEY, DATA>* tmp_node = _root;
        Node<KEY, DATA>* parent = nullptr;
        Node<KEY, DATA>* child = nullptr;
        Color original_color;

        while (tmp_node != nullptr) {
            if (p_key == tmp_node->get_key()) { break; }

            parent = tmp_node;

            if (p_key < tmp_node->get_key()) {
                tmp_node = tmp_node->get_left();
            } else {
                tmp_node = tmp_node->get_right();
            }
        }

        if (tmp_node == nullptr) { return; }

        if (tmp_node->get_left() == nullptr || tmp_node->get_right() == nullptr) {
            child = tmp_node;
        } else {
            Node<KEY, DATA>* successor = tmp_node->get_right();

            while (successor->get_left() != nullptr) {
                successor = successor->get_left();
            }

            child = successor;
        }

        if (child->get_left() != nullptr) {
            parent = child->get_left();
        } else {
            parent = child->get_right();
        }

        if (parent != nullptr) {
            parent->set_parent(child->get_parent());
        }

        if (child->get_parent() == nullptr) {
            _root = parent;
        } else if (child == child->get_parent()->get_left()) {
            child->get_parent()->set_left(parent);
        } else {
            child->get_parent()->set_right(parent);
        }

        if (child != tmp_node) {
            tmp_node->set_key(child->get_key());
            tmp_node->set_data(child->get_data());
        }

        original_color = child->get_color();
        delete child;

        if (original_color == BLACK && parent != nullptr) {
            _delete_fixup(parent);    
        }
    }

    void _delete_fixup(Node<KEY, DATA>* p_node) {
        while (p_node != _root && (p_node == nullptr && p_node->get_color() == BLACK)) {
            if (p_node == p_node->get_parent()->get_left()) {
                Node<KEY, DATA>* sibling = p_node->get_parent()->get_right();

                if (sibling->get_color() == RED) {
                    sibling->set_color(BLACK);
                    p_node->get_parent()->set_color(RED);
                    _rotate_left(p_node->get_parent());
                    sibling = p_node->get_parent()->get_right();
                }

                if ((sibling->get_left() == nullptr || sibling->get_left()->get_color() == BLACK) &&
                    (sibling->get_right() == nullptr || sibling->get_right()->get_color() == BLACK)) {
                    sibling->set_color(RED);
                    p_node = p_node->get_parent();
                } else {
                    if (sibling->get_right() == nullptr || sibling->get_right()->get_color() == BLACK) {
                        sibling->get_left()->set_color(BLACK);
                        sibling->set_color(RED);
                        _rotate_right(sibling);
                        sibling = p_node->get_parent()->get_right();
                    }

                    sibling->set_color(p_node->get_parent()->get_color());
                    p_node->get_parent()->set_color(BLACK);
                    sibling->get_right()->set_color(BLACK);
                    _rotate_left(p_node->get_parent());
                    p_node = _root;
                }
            } else {
                Node<KEY, DATA>* sibling = p_node->get_parent()->get_left();

                if (sibling->get_color() == RED) {
                    sibling->set_color(BLACK);
                    p_node->get_parent()->set_color(RED);
                    _rotate_right(p_node->get_parent());
                    sibling = p_node->get_parent()->get_left();
                }

                if ((sibling->get_right() == nullptr || sibling->get_right()->get_color() == BLACK) &&
                    (sibling->get_left() == nullptr || sibling->get_left()->get_color() == BLACK)) {
                    sibling->set_color(RED);
                    p_node = p_node->get_parent();
                } else {
                    if (sibling->get_left() == nullptr || sibling->get_left()->get_color() == BLACK) {
                        sibling->get_right()->set_color(BLACK);
                        sibling->set_color(RED);
                        _rotate_left(sibling);
                        sibling = p_node->get_parent()->get_left();
                    }

                    sibling->set_color(p_node->get_parent()->get_color());
                    p_node->get_parent()->set_color(BLACK);
                    sibling->get_left()->set_color(BLACK);
                    _rotate_right(p_node->get_parent());
                    p_node = _root;
                }
            }
        }

        if (p_node != nullptr) { p_node->set_color(BLACK); }    
    }

public:

    void print_tree(Node<KEY, DATA>* p_node, std::string prefix = "", bool is_left = true) {
        if (p_node == nullptr) {
            return;
        }

        std::cout << prefix;
        std::cout << (is_left ? "|-- " : "`-- ");
        std::cout << "{" << p_node->get_key() << ", " 
            << p_node->get_data() << "}\n";

        print_tree(p_node->get_left(), prefix + (is_left ? "|   " : "    "), true);
        print_tree(p_node->get_right(), prefix + (is_left ? "|   " : "    "), false);
    }

    // < ==== Tree walks ==== > //
    void pre_order(Node<KEY, DATA>* p_node) {
        if (p_node != nullptr) {
            std::cout << *p_node;
        }
        if (p_node != nullptr && p_node->get_left() != nullptr) {
            pre_order(p_node->get_left());
        }
        if (p_node != nullptr && p_node->get_right() != nullptr) {
            pre_order(p_node->get_right());
        }
    }

    void in_order(Node<KEY, DATA>* p_node) {
        if (p_node != nullptr && p_node->get_left() != nullptr) {
            in_order(p_node->get_left());
        }
        if (p_node != nullptr) {
            std::cout << *p_node;
        }
        if (p_node != nullptr && p_node->get_right() != nullptr) {
            in_order(p_node->get_right());
        }
    }

    void post_order(Node<KEY, DATA>* p_node) {
        if (p_node != nullptr && p_node->get_left() != nullptr) {
            post_order(p_node->get_left());
        }
        if (p_node != nullptr && p_node->get_right() != nullptr) {
            post_order(p_node->get_right());
        }
        if (p_node != nullptr) {
            std::cout << *p_node;
        }
    }
    
    void print_iterator() {
        auto iter = (*this).begin();
        while (iter != (*this).end()) {
            std::cout << *iter;
            iter++;
        } std::cout << *iter; 
    }
};

