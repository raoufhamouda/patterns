#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>


using namespace std;

class Component
{
    public:
        virtual void operation() = 0;
};

class ConcreteComponent : public Component
{
    void operation() override { cout << "pattern"; }
};

class Decorator : public Component
{
    boost::shared_ptr<Component>  component;
    void beforeOperation() { cout << "decorator "; }
    void afterOperation() { cout << "."; }

    public:
    Decorator(boost::shared_ptr<Component> c) : component(c) { }
    Decorator(boost::shared_ptr<Decorator> c) : component(c) { }
    void operation() override
    {
        beforeOperation();
        component->operation();
        afterOperation();
    }
};

int main()
{
    boost::shared_ptr<ConcreteComponent> comp1;
    boost::shared_ptr<Decorator> dec1(boost::dynamic_pointer_cast<Component> (comp1));
    // decorator is also a component so can be also decorated
    //Decorator dec2(static_cast<Component &> (dec1));
   // boost::shared_ptr<Decorator> dec1(comp1);
    boost::shared_ptr<Decorator> dec3(dec1);
    //Decorator dec4(static_cast<Component &> (dec3));

    dec1.operation();
    cout << endl;
    dec2.operation();
    cout << endl;
    dec3.operation();
    cout << endl;
    dec4.operation();
    cout << endl;

    return 0;
}
