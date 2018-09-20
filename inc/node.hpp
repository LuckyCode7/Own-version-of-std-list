#pragma once
#include <iostream>
#include <memory>

template<class T>
class Node
{
public:
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
    T value;
    Node(const T& v);
    ~Node() {}
};

template <class T>
Node<T>::Node(const T& v) :
        next(nullptr),
        value(v)
{}

