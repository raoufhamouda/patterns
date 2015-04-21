#include <iostream>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "composite.hpp"


using namespace std;

class Component{
    public:
        virtual void print() = 0;
};

class CompositeComponent : public Composite<Component>{
    std::string name;

    public:
    CompositeComponent(const std::string & s);
//    void print() override; //c++0x
    virtual void print();
};

CompositeComponent::CompositeComponent(const std::string & s){
    name=s;
}


void CompositeComponent::print(){
    std::cout << name << std::endl;
 //   for (auto &e : components_) // c++0x
    for(const_iterator c = components_.begin(); c != components_.end(); ++c){
        (*c)->print();
    }
}

class Leaf : public Component
{
    std::string name;

    public:

    Leaf(const std::string & s) : name(s) {}
 //   void print() override{ c++0x
    virtual void print(){
        std::cout << name << std::endl;
    }
};

void printComp(Component & c){
    c.print();
}

int main(){
    // unix directory structure
    boost::shared_ptr<CompositeComponent> root(new CompositeComponent("/"));
    boost::shared_ptr<CompositeComponent> usr(new CompositeComponent("usr"));
    boost::shared_ptr<CompositeComponent> home(new CompositeComponent("home"));
    boost::shared_ptr<CompositeComponent> dev(new CompositeComponent("dev"));
    boost::shared_ptr<CompositeComponent> user(new CompositeComponent("user"));
    boost::shared_ptr<Leaf> file(new Leaf("file.txt"));

    user->add(file); //on passe l'adresse d'un composant
    home->add(user);

    root->add(usr);
    root->add(dev);
    root->add(home);

    // composition of objects and object are treating in the same way 
    printComp(*root);
    printComp(*file);

    return 0;
}
