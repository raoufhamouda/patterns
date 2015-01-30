#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>

using namespace std;


template <class T>
class Composite : public T {
    protected:

        std::vector<boost::shared_ptr<T> > components_;

        typedef typename std::vector<boost::shared_ptr<T> >::iterator iterator;

        typedef typename std::vector<boost::shared_ptr<T> >::const_iterator
            const_iterator;

    public:
        void add(const boost::shared_ptr<T>& c) { components_.push_back(c); }
        void remove(boost::shared_ptr<T> c){ 
            // removes element from collection
            components_.erase(
                    std::remove(components_.begin(), components_.end(), c),
                    components_.end());
        }

        boost::shared_ptr<T> getChild(const int & index){
            return components_[index];
        }

};

class Component{
    public:
        virtual void print() = 0;
};

class CompositeComponent : public Composite<Component>{
    string name;

    public:

    CompositeComponent(const string & s);
    void print() override;
};

CompositeComponent::CompositeComponent(const string & s){
    name=s;
}


void CompositeComponent::print(){
    cout << name << endl;

    for (auto &e : components_)
        e->print();

}

class Leaf : public Component
{
    string name;
    public:

    Leaf(string s) : name(s) {}

    void print() override
    {
        cout << name << endl;
    }
};

void printComp(Component & c)
{
    c.print();
}

int main()
{
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
