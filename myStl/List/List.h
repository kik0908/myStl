#pragma once
#include <iostream>

template <typename Type>
class List
{
public:
    struct Node
    {
        Node* previous;
        Type data;
        Node* next;
        Node(Type const& d) : data(d), next(nullptr), previous(nullptr) {}
        Node(Type&& d) : data(std::move(d)), next(nullptr), previous(nullptr) {}
    };

    struct iterator
    {
        Node* _node;
        iterator(Node* node = nullptr) : _node(node) {}
        Type& operator*()
        {
            return _node->data;
        }

        Type& operator*() const
        {
            return _node->data;
        }

        bool operator==(iterator const& it)
        {
            return _node == it._node;
        }

        bool operator!=(iterator const& it)
        {
            return !(*this == it);
        }

        iterator& operator++()
        {
            _node = _node->next;
            return *this;
        }

        iterator operator++(int)
        {
            Node* tmp = _node;
            _node = _node->next;
            return iterator(tmp);
        }

        iterator& operator--()
        {
            _node = _node->previous;
            return *this;
        }

        iterator operator--(int)
        {
            Node* tmp = _node;
            _node = _node->previous;
            return iterator(tmp);
        }
    };

    struct const_iterator
    {
        Node* _node;
        const_iterator(Node* node = nullptr) : _node(node) {}
        Type const& operator*()
        {
            return _node->data;
        }

        Type const& operator*() const
        {
            return _node->data;
        }

        bool operator==(iterator const& it)
        {
            return _node == it._node;
        }

        bool operator!=(iterator const& it)
        {
            return !(*this == it);
        }

        const_iterator& operator++()
        {
            _node = _node->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            Node* tmp = _node;
            _node = _node->next;
            return iterator(tmp);
        }

        const_iterator& operator--()
        {
            _node = _node->previous;
            return *this;
        }

        const_iterator operator--(int)
        {
            Node* tmp = _node;
            _node = _node->previous;
            return iterator(tmp);
        }
    };
private:
    Node* _root;
    Node* _end;
    size_t _size;
public:
    List() :_root(nullptr), _end(nullptr), _size(0) {}

    List(Type* data, size_t size): List()
    {
        for (size_t i = 0; i < size; ++i) {
            push_back(data[i]);
        }
    }

    List(List const& source) : List()
    {
        Node* curr = source._root;
        while (curr != nullptr) {
            push_back(curr->data);
            curr = curr->next;
        }
    }

    List& operator=(List const& source)
    {   
        clear();
        for (auto it = source.begin(); it != source.end(); ++it) {
            push_back(*it);
        }
    }

    void clear()
    {
        while (_root != nullptr)
        {
            Node* tmp = _root;
            _root = _root->next;
            delete tmp;
        }
        _end = nullptr;
        _size = 0;
    }
    ~List()
    {
        clear();
    }

    iterator push_back(Type const& val);
    iterator push_back(Type&& val);
    

    iterator begin() { return iterator(_root); }
    iterator end() { return iterator(nullptr); }
    iterator begin() const { return const_iterator(_root); }
    iterator end() const { return const_iterator(nullptr); }

    iterator insert(Type const& val, iterator it_in);
    iterator insert(Type&& val, iterator it_in);

    void erase(iterator to_die_it);

    iterator find(Type const& to_find);

    size_t size() const { return _size; }
};

template <class Type>
typename List<Type>::iterator List<Type>::push_back(Type const& val)
{
    if (_root == nullptr)
    {
        _root = _end = new Node(val);
        _size = 1;
        return begin();
    }

    Node* new_node = new Node(val);
    new_node->previous = _end;
    _end->next = new_node;
    _end = new_node;
    ++_size;
    return iterator(_end);
}

template<typename Type>
typename List<Type>::iterator List<Type>::push_back(Type&& val)
{
    if (_root == nullptr)
    {
        _root = _end = new Node(std::move(val));
        _size = 1;
        return begin();
    }

    Node* new_node = new Node(std::move(val));
    new_node->previous = _end;
    _end->next = new_node;
    _end = new_node;
    ++_size;
    return iterator(_end);
}

template <class Type>
void List<Type>::erase(iterator to_die_it)
{
    Node* to_die = to_die_it._node;
    Node* pre = to_die->previous;
    Node* next = to_die->next;
    if (pre != nullptr) {
        pre->next = next;
    }
    if (next != nullptr) {
        next->previous = pre;
    }
    if (to_die == _root) {
        _root = next;
    }
    if (to_die == _end) {
        _end = pre;
    }
    delete to_die;
}

template<typename Type>
inline typename List<Type>::iterator List<Type>::insert(Type const& val, iterator it_in)
{
    if (it_in != end()) {
        Node* new_node = new Node(val);
        new_node->next = it_in._node;
        Node* tmp = it_in._node->previous;
        new_node->previous = tmp;
        if (tmp != nullptr) {
            tmp->next = new_node;
        }
        if (it_in == begin()) {
            _root = new_node;
        }
        it_in._node->previous = new_node;

        return iterator(new_node);
    }
    else {
        push_back(val);
    }
}

template<typename Type>
inline typename List<Type>::iterator List<Type>::insert(Type&& val, iterator it_in)
{
    if (it_in != end()) {
        Node* new_node = new Node(std::move(val));
        new_node->next = it_in._node;
        Node* tmp = it_in._node->previous;
        new_node->previous = tmp;
        if (tmp != nullptr) {
            tmp->next = new_node;
        }
        if (it_in == begin()) {
            _root = new_node;
        }
        it_in._node->previous = new_node;

        return iterator(new_node);
    }
    else {
        push_back(val);
    }
}

template <typename Type>
typename typename List<Type>::iterator List<Type>::find(Type const& to_find)
{
    Node* curr = _root;
    while (curr != nullptr)
    {
        if (curr->data != to_find)
            curr = curr->next;
        else
            return iterator(curr);
    }
    return end();
}

template <class Type>
std::ostream& operator<<(std::ostream& out, List<Type> list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        out << *it << ' ';
    }
    return out;
}