#include <iostream>
#include <memory>
#include <string>
#include "../inc/node.hpp"
#include "../inc/list.hpp"


int main()
{
    try
    {
        List<std::string> list;

        auto rafal = std::make_shared<Node<std::string>>("rafal");
        auto franek = std::make_shared<Node<std::string>>("franek");
        auto domi = std::make_shared<Node<std::string>>("kasia");
        auto ola = std::make_shared<Node<std::string>>("ola");


        list.addLast(ola);
        list.addLast(rafal);
        list.addLast(franek);
        //list.addFirst(rafal); // wksaźnik next rafala juz się zmienił wyżej !!!
        list.addFirst(domi);
        list.get("rafal");
        std::cout<<"HEAD: "<<list.getHead()->value<<std::endl;
        std::cout<<"TAIL: "<<list.getTail()->value<<std::endl;
        std::cout<<"Previous element: "<<list.getPrevious(ola)->value<<std::endl;
        std::cout<<"Next element: "<<list.getNext(domi)->value<<std::endl;
        list.getBackWard("ola");
        list.removeFirst();
        list.removeLast();
        std::cout<<"count: "<<list.count()<<std::endl;
        list.show();
    }
    catch(const EmptyListError& error)
    {
        std::cout<<error.what()<<std::endl;
    }
    catch(const NotFoundError& error)
    {
        std::cout<<error.what()<<std::endl;
    }
    catch(const InvalidNextOrPrevValue& error)
    {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}

