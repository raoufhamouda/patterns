#ifndef test_composite_hpp
#define test_composite_hpp

#include <iostream>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "composite.hpp"

class Component{
    public:
        virtual void print() = 0;
};

class CompositeComponent : public Composite<Component>{
    std::string name;

    public:
    CompositeComponent(const std::string & s);
    void print() override; //c++0x
};

CompositeComponent::CompositeComponent(const std::string & s){
    name=s;
}


void CompositeComponent::print(){
    std::cout << name << std::endl;
    for (auto &c : components_){ // c++0x
        c->print();
    }
}

class Leaf : public Component
{
    std::string name;

    public:

    Leaf(const std::string & s) : name(s) {}
    void print() override{
        std::cout << name << std::endl;
    }
};

void printComp(Component & c){
    c.print();
}

#endif
