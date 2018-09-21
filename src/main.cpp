#include <iostream>
#include <cassert>
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
        auto kasia = std::make_shared<Node<std::string>>("kasia");
        auto ola = std::make_shared<Node<std::string>>("ola");

        list.addLast(ola);
        list.addLast(rafal);
        list.addLast(franek);
        list.addFirst(kasia);

        assert(list.get("rafal") == rafal);
        assert(list.getHead()->value == "kasia");
        assert(list.getTail()->value == "franek");
        assert(list.getPrevious(ola) == kasia);
        assert(list.getNext(rafal) == franek);
        assert(list.getBackWard("ola") == ola);
        assert(list.count() == 4);
        assert(list[3] == "franek");
        list.show();

        list.removeFirst();
        list.removeLast();
        assert(list.count() == 2);
        list.replace("rafal", "anonymous");
        assert(list.count("rafal") == 0);
        list.show();

        List<std::string> list2(list);
        list2.show();
        list2.clear();
        list2.show();

        List<std::string> list3(std::move(list));
        list3.show();
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
    catch(const std::out_of_range& error)
    {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}

