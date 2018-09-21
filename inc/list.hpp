#include <iostream>
#include "../inc/node.hpp"
#include "../inc/exceptions.hpp"

template<class T>
class List
{
public:
    List();
    List(const List& list);
    List(List&& source);
    void addLast(std::shared_ptr<Node<T> > node);                                   // dodaje element na koniec listy
    void addFirst(std::shared_ptr<Node<T>> node);                                   // dodaje element na początek listy
    std::shared_ptr<Node<T>> get(const T& value);                                   // zwraca element o wskazanej wartości szukając od pierwszego elementu
    std::shared_ptr<Node<T>> getBackWard(const T& value);                           // zwraca element o wskazanej wartości szukając od ostatniego elementu
    std::shared_ptr<Node<T>> getHead() const;                                       // zwraca pierwszy element
    std::shared_ptr<Node<T>> getTail() const;                                       // zwraca ostatni element
    std::shared_ptr<Node<T>> getPrevious(std::shared_ptr<Node<T>> node) const;      // zwraca poprzedni element
    std::shared_ptr<Node<T>> getNext(std::shared_ptr<Node<T>> node) const;          // zwraca kolejny element
    void removeFirst();                                                             // usuwa pierwszy element
    void removeLast();                                                              // usuwa ostatni element
    int count() const;                                                              // zwraca liczbę wszystkich elementów listy
    int count(const T& value) const;                                                // zwraca liczbę konkretnych elementów listy
    void replace(const T& target, const T& value);                                  // zamienia wartość węzła
    void show();                                                                    // pokazuje elementy listy
    void clear();                                                                   // czyści listę
    T& operator[](const int& node);
    ~List() {}
private:
    std::shared_ptr<Node<T>> first;
    std::shared_ptr<Node<T>> last;
    bool checkNextAndPreviousValues(std::shared_ptr<Node<T>> node);
    bool checkIfNodeIsNotFirst(std::shared_ptr<Node<T>> node);
    bool checkIfListIsEmpty();
};

template<class T>
List<T>::List() :
    first(nullptr),
    last(nullptr)
{}

template<class T>
List<T>::List(const List& list) :
    first(list.getHead()),
    last (list.getTail())
{}

template<class T>
List<T>::List(List&& source) :
    first(source.getHead()),
    last (source.getTail())
{
    source.clear();
}

template<class T>
void List<T>::removeFirst()
{
    first = first->next;
    first->prev.lock() = nullptr;
}

template<class T>
void List<T>::clear()
{
    std::shared_ptr<Node<T>> current = last;
    while(current != nullptr)
    {
        current->next.reset();
        current = current->prev.lock();
    }
    first.reset();
}

template<class T>
void List<T>::removeLast()
{
    last = last->prev.lock();
    last->next = nullptr;
}

template<class T>
void List<T>::show()
{
    std::shared_ptr<Node<T>> current = first;
    if(!checkIfListIsEmpty())
    {
        std::cout<<"nullptr<->";
        do
        {
            std::cout<<current->value<<"<->";
            current = current->next;
        }
        while(current != nullptr);
        std::cout<<"nullptr"<<std::endl;
    }
    else throw EmptyListError();
}

template<class T>
void List<T>::replace(const T& target, const T& value)
{
    std::shared_ptr<Node<T>> current = first;
    while(current != nullptr)
    {
        if(current->value == target)
            current->value = value;
        current = current->next;
    }
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
bool List<T>::checkNextAndPreviousValues(std::shared_ptr<Node<T>> node)
{
    if(node->next != nullptr || node->prev.lock() != nullptr)
    {
        throw InvalidNextOrPrevValue();
    }
    return true;
}

template<class T>
bool List<T>::checkIfNodeIsNotFirst(std::shared_ptr<Node<T>> node)
{
    if(first == nullptr)
    {
        first = node;
        last = node;
        return true;
    }
    return false;
}

template<class T>
bool List<T>::checkIfListIsEmpty()
{
    if(first == nullptr)
    {
        throw EmptyListError();
    }
    return false;
}

template<class T>
void List<T>::addLast(std::shared_ptr<Node<T>> node)
{
    checkNextAndPreviousValues(node);
    if(!checkIfNodeIsNotFirst(node))
    {
        last->next = node;
        node->prev = last;
        last = node;
    }
}

template<class T>
void List<T>::addFirst(std::shared_ptr<Node<T>> node)
{
    checkNextAndPreviousValues(node);
    if(!checkIfNodeIsNotFirst(node))
    {
        first->prev = node;
        node->next = first;
        first = node;
    }
}

template<class T>
std::shared_ptr<Node<T>> List<T>::get(const T& value)
{
    if(!checkIfListIsEmpty())
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
std::shared_ptr<Node<T>> List<T>::getBackWard(const T& value)
{
    if(!checkIfListIsEmpty())
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

template<class T>
T& List<T>::operator[](const int& node)
{
    if(!checkIfListIsEmpty() && node < count())
    {
        int whichNode = 0;
        std::shared_ptr<Node<T>> current = first;
        while(current != nullptr)
        {
            if(whichNode == node) break;
            else
            {
                current = current->next;
                ++whichNode;
            }
        }
        return current->value;
    }
    else throw std::out_of_range("operator[] out of range");
}

