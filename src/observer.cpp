#include "observer.hpp"
#include "errors.hpp"

Observer::Observer(const Observer& o)
: observables_(o.observables_) {

    for (auto &e : observables_) // c++0x
        e->registerObserver(this);
}

Observer& Observer::operator=(const Observer& o) {
    for (auto &e : observables_) // c++0x
        e->unregisterObserver(this);
    observables_ = o.observables_;
    for (auto &e : observables_) // c++0x
        e->registerObserver(this);
    return *this;
}

Observer::~Observer() {
    for (auto &e : observables_) // c++0x
        e->unregisterObserver(this);
}

std::pair<std::set<boost::shared_ptr<Observable> >::iterator, bool>
Observer::registerWith(const boost::shared_ptr<Observable>& h) {
    if (h) {
        h->registerObserver(this);
        return observables_.insert(h);
    }
    return std::make_pair(observables_.end(), false);
}

size_t Observer::unregisterWith(const boost::shared_ptr<Observable>& h) {
    if (h)
        h->unregisterObserver(this);
    return observables_.erase(h);
}

void Observer::unregisterWithAll() {
    for (auto &e : observables_) // c++0x
        e->unregisterObserver(this);
    observables_.clear();
}

Observable::Observable(const Observable&) {
    // the observer set is not copied; no observer asked to
    // register with this object
}

/*! \warning notification is sent before the copy constructor has
             a chance of actually change the data
             members. Therefore, observers whose update() method
             tries to use their observables will not see the
             updated values. It is suggested that the update()
             method just raise a flag in order to trigger
             a later recalculation.
*/
Observable& Observable::operator=(const Observable& o) {
    // as above, the observer set is not copied. Moreover,
    // observers of this object must be notified of the change
    if (&o != this)
        notifyObservers();
    return *this;
}


std::pair<std::set<Observer*>::iterator, bool>
Observable::registerObserver(Observer* o) {
    return observers_.insert(o);
}

size_t Observable::unregisterObserver(Observer* o) {
    return observers_.erase(o);
}

void Observable::notifyObservers() {
    bool successful = true;
    std::string errMsg;
    for (iterator i=observers_.begin(); i!=observers_.end(); ++i) {
        try {
            (*i)->update();
        } catch (std::exception& e) {
            successful = false;
            errMsg = e.what();
        } catch (...) {
            successful = false;
        }
    }
    ENSURE(successful, "could not notify one or more observers: " << errMsg);
}
