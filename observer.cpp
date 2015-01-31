#include <iostream>
#include <string>
#include <set>
#include <boost/shared_ptr.hpp>

using namespace std;

class Subject;

class Observer {
    public:
        virtual void update(Subject & subject) = 0;
};

// also knows as Observable in literature
class Subject
{
    string state;
    set<boost::shared_ptr<Observer> > observers;

    public:
    void attachObserver(boost::shared_ptr<Observer> o) { observers.insert(o); }
    void detachObserver(boost::shared_ptr<Observer> o) { observers.erase(o); }
    void notifyObservers()
    {
        for (auto &o : observers)
        {
            o->update(*this);
        }
    }
    string getState() { return state; }
    void changeState(const string & s)
    {
        state = s;
        notifyObservers();
    }
};

class ObserverImpl : public Observer
{
    string state;

    public:

    void update(Subject & sbj) override
    {
        state = sbj.getState();
    }

    string getState() { return state; }
};

int main()
{
    boost::shared_ptr<ObserverImpl> a(new ObserverImpl);
    boost::shared_ptr<ObserverImpl> b(new ObserverImpl);
    boost::shared_ptr<ObserverImpl> c(new ObserverImpl);

    Subject subject;

    subject.attachObserver(a);
    subject.attachObserver(b);
    subject.attachObserver(c);

    subject.changeState("Observer pattern");
    cout << a->getState() << endl;
    cout << b->getState() << endl;
    cout << c->getState() << endl;

    return 0;
}
