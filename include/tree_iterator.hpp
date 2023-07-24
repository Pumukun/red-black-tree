#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

friend class tree_iterator {
private:

    Node<KEY, DATA>* ptr;
    
public:

    tree_iterator() { ptr = NULL; }

        tree_iterator(Node<KEY, DATA> *p_node) { ptr = p_node; }

        tree_iterator(const tree_iterator &it) { ptr = it.ptr; }

        Node<KEY, DATA>& operator++ (RBT<KEY, DATA>& rbt) {
            if (ptr == nullptr)
                throw std::out_of_range("iterator ptr is null");

            if (ptr->get_right() != nullptr)
                ptr = rbt.find_min(ptr->get_right());
            else {
                if (ptr->get_parent() == nullptr)
                    return *ptr;

                Node<KEY, DATA> *current = ptr->get_parent();

                while (current->get_parent() != nullptr && current->get_key() < ptr->get_key())
                    current = current->get_parent();
                if (current->get_key() > ptr->get_key())
                    ptr = current;
            }
            return *ptr;
        }

        Node<KEY, DATA>& operator-- () {
            if (ptr == nullptr)
                throw std::out_of_range("iterator ptr is null");

            if (ptr->get_left() != nullptr)
                ptr = rbt.find_max(ptr->get_left());
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

    template<class KEY1, class DATA1>
    friend ostream& operator<< (ostream &out, RBT<KEY1, DATA1> p_rbt);
        auto it = p_rbt.begin();
        while (it != p_rbt.end()) {
            out << *it << " ";
            it++;
        }
        return out;
    }
};

#endif
