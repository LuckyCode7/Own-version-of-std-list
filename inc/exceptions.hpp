#pragma once
#include <iostream>
#include <exception>

class EmptyListError : public std::runtime_error
{
public:
    EmptyListError() : runtime_error("List is empty")
    {}
};

class NotFoundError : public std::runtime_error
{
public:
    NotFoundError() : runtime_error("searched item not found")
    {}
};

class InvalidNextOrPrevValue : public std::runtime_error
{
public:
    InvalidNextOrPrevValue() : runtime_error("Cannot add node, which next element is already set")
    {}
};


