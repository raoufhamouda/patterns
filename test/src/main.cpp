#include "test_all.hpp"
#include <boost/shared_ptr.hpp>

void test_composite(){
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
}
void test_observer(){
    boost::shared_ptr<Subject> calc(new Subject);
    Vtk vtk_observer(calc,"amounts.dat" ,"observer a");
    calc->calculateInterest(100.0, 0.03, 5);
    calc->calculateInterest(100.0, 0.04, 5);
}

int main(){
    test_composite();
    test_observer();
    return 0;
}

