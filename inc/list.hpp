#include <iostream>
#include "../inc/node.hpp"
#include "../inc/exceptions.hpp"

template<class T>
class List
{
public:
    List();
    void addLast(std::shared_ptr<Node<T> > node);                        // dodaje element na koniec listy
    void addFirst(std::shared_ptr<Node<T>> node);                       // dodaje element na początek listy
    std::shared_ptr<Node<T>> get(const T& value) const;                      // zwraca element o wskazanej wartości szukając od pierwszego elementu
    std::shared_ptr<Node<T>> getBackWard(const T& value) const;             // zwraca element o wskazanej wartości szukając od ostatniego elementu
    std::shared_ptr<Node<T>> getHead() const;
    std::shared_ptr<Node<T>> getTail() const;
    std::shared_ptr<Node<T>> getPrevious(std::shared_ptr<Node<T>> node) const;
    std::shared_ptr<Node<T>> getNext(std::shared_ptr<Node<T>> node) const;
    void removeFirst();
    void removeLast();
    int count() const;
    void show() const;
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
    first->prev = nullptr;
}

template<class T>
void List<T>::removeLast()
{
    last = last->prev;
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
    while(current->next != nullptr)
    {
        howMany++;
        current = current->next;
    }
    return ++howMany;
}

template<class T>
void List<T>::addLast(std::shared_ptr<Node<T>> node)
{
    if(node->next != nullptr || node->prev != nullptr)
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
                current = current->prev;
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
    return node->prev;
}

template<class T>
std::shared_ptr<Node<T>> List<T>::getNext(std::shared_ptr<Node<T>> node) const
{
    return node->next;
}


