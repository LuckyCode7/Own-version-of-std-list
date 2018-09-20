#include <iostream>
#include "../inc/node.hpp"
#include "../inc/exceptions.hpp"

template<class T>
class List
{
public:
    List();
    void addLast(std::shared_ptr<Node<T> > node);                                   // dodaje element na koniec listy
    void addFirst(std::shared_ptr<Node<T>> node);                                   // dodaje element na początek listy
    std::shared_ptr<Node<T>> get(const T& value) const;                             // zwraca element o wskazanej wartości szukając od pierwszego elementu
    std::shared_ptr<Node<T>> getBackWard(const T& value) const;                     // zwraca element o wskazanej wartości szukając od ostatniego elementu
    std::shared_ptr<Node<T>> getHead() const;                                       // zwraca pierwszy element
    std::shared_ptr<Node<T>> getTail() const;                                       // zwraca ostatni element
    std::shared_ptr<Node<T>> getPrevious(std::shared_ptr<Node<T>> node) const;      // zwraca poprzedni element
    std::shared_ptr<Node<T>> getNext(std::shared_ptr<Node<T>> node) const;          // zwraca kolejny element
    void removeFirst();                                                             // usuwa pierwszy element
    void removeLast();                                                              // usuwa ostatni element
    int count() const;                                                              // zwraca liczbę wszystkich elementów listy
    int count(const T& value) const;                                                // zwraca liczbę konkretnych elementów listy
    void show() const;                                                              // pokazuje elementy listy
    ~List() {}
private:
    std::shared_ptr<Node<T>> first;
    std::shared_ptr<Node<T>> last;
};

template<class T>
List<T>::List() :
    first(nullptr),
    last(nullptr)
{}

template<class T>
void List<T>::removeFirst()
{
    first = first->next;
    first->prev.lock() = nullptr;
}

template<class T>
void List<T>::removeLast()
{
    last = last->prev.lock();
    last->next = nullptr;
}

template<class T>
void List<T>::show() const
{
    std::cout<<"nullptr<->";
    std::shared_ptr<Node<T>> current = first;
    do
    {
        std::cout<<current->value<<"<->";
        current = current->next;
    }
    while(current != nullptr);
    std::cout<<"nullptr"<<std::endl;
}

template<class T>
int List<T>::count() const
{
    int howMany = 0;
    std::shared_ptr<Node<T>> current = first;
    while(current != nullptr)
    {
        ++howMany;
        current = current->next;
    }
    return howMany;
}

template<class T>
int List<T>::count(const T& value) const
{
    int howMany = 0;
    std::shared_ptr<Node<T>> current = first;
    while(current != nullptr)
    {
        if(current->value == value)
        ++howMany;
        current = current->next;
    }
    return howMany;
}

template<class T>
void List<T>::addLast(std::shared_ptr<Node<T>> node)
{
    if(node->next != nullptr || node->prev.lock() != nullptr)
    {
        throw InvalidNextOrPrevValue();
    }
    if(first == nullptr) //pierwszy węzeł
    {
        first = node;
        last = node;
    }
    else
    {
        std::shared_ptr<Node<T>> current = first;
        node->prev = last;
        last = node;
        while(current->next != nullptr)
        {
            current = current->next;
        }
        current->next = node;
    }
}

template<class T>
void List<T>::addFirst(std::shared_ptr<Node<T>> node)
{
    if(node->next != nullptr)
    {
        throw InvalidNextOrPrevValue();
    }
    if(first == nullptr)
    {
        first = node;
        last = node;
    }
    else
    {
        first->prev = node;
        node->next = first;
        first = node;
    }
}

template<class T>
std::shared_ptr<Node<T>> List<T>::get(const T& value) const
{
    if(first == nullptr)
    {
        throw EmptyListError();
    }
    else
    {
        std::shared_ptr<Node<T>> current = first;
        do
        {
            if(current->value == value)
            {
                std::cout << "Found value " << current->value << std::endl;
                return current;
            }
            else
            {
                std::cout << "Going through " << current->value << std::endl;
                current = current->next;
            }
        } while(current);
        throw NotFoundError();
    }
}

template<class T>
std::shared_ptr<Node<T>> List<T>::getBackWard(const T& value) const
{
    if(first == nullptr)
    {
        throw EmptyListError();
    }
    else
    {
        std::shared_ptr<Node<T>> current = last;
        do
        {
            if(current->value == value)
            {
                std::cout << "Found value " << current->value << std::endl;
                return current;
            }
            else
            {
                std::cout << "Going through " << current->value << std::endl;
                current = current->prev.lock();
            }
        } while(current);
        throw NotFoundError();
    }
}

template<class T>
std::shared_ptr<Node<T>> List<T>::getHead() const
{
    return first;
}

template<class T>
std::shared_ptr<Node<T>> List<T>::getTail() const
{
    return last;
}

template<class T>
std::shared_ptr<Node<T>> List<T>::getPrevious(std::shared_ptr<Node<T>> node) const
{
    return node->prev.lock();
}

template<class T>
std::shared_ptr<Node<T>> List<T>::getNext(std::shared_ptr<Node<T>> node) const
{
    return node->next;
}


