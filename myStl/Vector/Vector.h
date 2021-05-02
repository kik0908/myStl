#pragma once
#include <stdexcept>
#include <iostream>
template <class Type>
class Vector
{
private:
    Type* _data;
    size_t _size;
    size_t _capacity;
    static const size_t kDefCapacity = 10;
    static const double kDefMultiplier() { return 1.5; }

public:
    Vector(size_t size = 0);
    Vector(size_t size, Type const& val);
    Vector(Vector<Type> const& vec) : Vector(vec._data, vec._size) {}
    ~Vector() { clear(); }

    Vector& operator=(Vector<Type> const& vec)
    {
        clear();
        reserve(vec.size());
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            push_back(*it);
        }
        return *this;
    }

    Vector(Type* data, size_t size) : Vector(size)
    {
        for (size_t i = 0; i < size; ++i) {
            _data[i] = data[i];
        }
    }

    void reserve(size_t new_capacity);
    void clear();

    struct iterator
    {
        Type* _data;

        iterator(Type* elem = nullptr) : _data(elem) {}
        Type& operator*() { return *_data; }
        Type& operator*() const { return *_data; }
        bool operator==(const iterator& it) const
        {
            return _data == it._data;
        }
        bool operator!=(const iterator& it) const
        {
            return !(*this == it);
        }
        iterator& operator++()
        {
            ++_data;
            return *this;
        }
        iterator operator++(int)
        {
            Type* tmp = _data;
            ++_data;
            return iterator(tmp);
        }
        iterator& operator--()
        {
            --_data;
            return *this;
        }
        iterator operator--(int)
        {
            Type* tmp = _data;
            --_data;
            return iterator(tmp);
        }
    };


    Type& operator[](int idx);
    Type const& operator[](int idx) const;

    iterator push_back(Type const& val);
    iterator push_back(Type&& val);

    iterator insert(iterator it_in, Type const& val);
    iterator insert(iterator it_in, Type&& val);

    iterator find(Type const& to_find);
    void erase(iterator to_die);

    iterator begin() { return iterator(_data); }
    iterator end() { return iterator(_data+_size); }

    size_t size() const { return _size; }
};

template<class Type>
Type& Vector<Type>::operator[](int idx)
{
    idx = idx >= 0 ? idx : _size + idx;
    if (idx < 0 or idx >= _size) {
        throw std::out_of_range ("Index out of range!");
    }

    return _data[idx];
}

template<class Type>
Type const& Vector<Type>::operator[](int idx) const
{
    idx = idx >= 0 ? idx : _size + idx;
    if (idx < 0 or idx >= _size) {
        throw std::out_of_range("Index out of range!");
    }

    return _data[idx];
}

template <class Type>
Vector<Type>::Vector(size_t size) : _size(size), _capacity(size), _data(nullptr)
{
    _data = (Type*)(::operator new(_capacity * sizeof(Type)));
    for (size_t idx = 0; idx < _size; ++idx)
        new(_data + idx) Type;
}

template <class Type>
Vector<Type>::Vector(size_t size, Type const& val) : _size(size), _capacity(size), _data(nullptr)
{
    if (_capacity != 0)
    {
        _data = (Type*)(::operator new(_capacity * sizeof(Type)));
        for (size_t idx = 0; idx < _size; ++idx)
            new(_data + idx) Type(val);
    }
}

template <class Type>
void Vector<Type>::reserve(size_t new_capacity)
{
    if (new_capacity > _capacity)
    {
        Type* tmp_data = (Type*)(::operator new(new_capacity * sizeof(Type)));
        for (size_t idx = 0; idx < _size; ++idx)
            new(tmp_data + idx) Type(std::move(_data[idx]));
        size_t prev_size = _size;
        clear();
        _data = tmp_data;
        _size = prev_size;
        _capacity = new_capacity;
    }
}

template <class Type>
typename Vector<Type>::iterator Vector<Type>::push_back(Type const& val)
{
    if (_size == _capacity)
    {
        size_t safe_capacity = _capacity <= 1 ? kDefCapacity : _capacity;
        reserve(safe_capacity * kDefMultiplier());
    }

    new(_data + (_size++)) Type(val);
    return iterator(_data + (_size - 1));
}

template <class Type>
typename Vector<Type>::iterator Vector<Type>::push_back(Type&& val)
{
    if (_size == _capacity)
    {
        size_t safe_capacity = _capacity <= 1 ? kDefCapacity : _capacity;
        reserve(safe_capacity * kDefMultiplier());
    }

    new(_data + (_size++)) Type(std::move(val));
    return iterator(_data + (_size - 1));
}

template<class Type>
typename Vector<Type>::iterator Vector<Type>::insert(Vector<Type>::iterator it_in, Type const& val)
{   
    push_back(*(--end()));
    for (auto it = --end(); it != it_in;) {
        Type& tmp2 = *it;
        tmp2 = std::move(*(--it));
    }
    *it_in = val;
    return it_in;
}

template<class Type>
typename Vector<Type>::iterator Vector<Type>::insert(Vector<Type>::iterator it_in, Type&& val)
{
    push_back(*(--end()));
    for (auto it = --end(); it != it_in;) {
        Type& tmp2 = *it;
        tmp2 = std::move(*(--it));
    }
    *it_in = val;
    return it_in;
}

template<class Type>
void Vector<Type>::erase(iterator to_die)
{
    (*to_die).~Type();
    for (auto it = to_die; it != end();) {
        Type& tmp = *it;
        tmp = std::move(*(++it));
    }
    (*(--end())).~Type();
    --_size;
}

template <class Type>
void Vector<Type>::clear()
{
    if (_capacity != 0)
    {
        for (size_t idx = 0; idx < _size; ++idx)
            _data[idx].~Type();
        ::operator delete[](_data);
        _size = _capacity = 0;
    }
}

template <class Type>
typename Vector<Type>::iterator Vector<Type>::find(Type const& to_find)
{
    for (size_t idx = 0; idx < _size; ++idx)
        if (_data[idx] == to_find)
            return iterator(_data + idx);
    return end();
}

template <class Type>
std::ostream& operator<<(std::ostream& out, Vector<Type> vec) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        out << *it << ' ';
    }
    return out;
}