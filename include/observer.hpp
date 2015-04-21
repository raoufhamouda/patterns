/*! \file obserer.hpp
    \brief observer/observable pattern
*/

#ifndef observer_hpp
#define observer_hpp

#include <iostream>
#include <string>
#include <boost/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <exception>
#include <sstream>
#include <stdexcept>
#include <set>

#include "errors.hpp"

class Observer;

//! Object that notifies its changes to a set of observers
/*! \ingroup patterns */
class Observable {
    friend class Observer;

    typedef std::set<Observer*>::iterator iterator;
    std::pair<iterator, bool> registerObserver(Observer*);
    size_t unregisterObserver(Observer*);
    std::set<Observer*> observers_;

  public:
    // constructors, assignment, destructor
    Observable() {}
    Observable(const Observable&);
    Observable& operator=(const Observable&);
    virtual ~Observable() {}

    /*! This method should be called at the end of non-const methods
        or when the programmer desires to notify any changes.
    */
    void notifyObservers();
};

//! Object that gets notified when a given observable changes
/*! \ingroup patterns */
class Observer {
    std::set<boost::shared_ptr<Observable> > observables_;
  public:
    // constructors, assignment, destructor
    Observer() {}
    Observer(const Observer&);
    Observer& operator=(const Observer&);
    virtual ~Observer();

    // observer interface
    std::pair<std::set<boost::shared_ptr<Observable> >::iterator, bool>
                        registerWith(const boost::shared_ptr<Observable>&);
    size_t unregisterWith(const boost::shared_ptr<Observable>&);
    void unregisterWithAll();

    /*! Must be implemented in derived classes.
     * Is called by the observable registered with, through 
     * notifyObservers method
    */
    virtual void update() = 0;
};


//inline Observer::Observer(const Observer& o)
//: observables_(o.observables_) {
//    for (iterator i=observables_.begin(); i!=observables_.end(); ++i)
//        (*i)->registerObserver(this);
//}
//
//inline Observer& Observer::operator=(const Observer& o) {
//    iterator i;
//    for (i=observables_.begin(); i!=observables_.end(); ++i)
//        (*i)->unregisterObserver(this);
//    observables_ = o.observables_;
//    for (i=observables_.begin(); i!=observables_.end(); ++i)
//        (*i)->registerObserver(this);
//    return *this;
//}
//
//inline Observer::~Observer() {
//    for (iterator i=observables_.begin(); i!=observables_.end(); ++i)
//        (*i)->unregisterObserver(this);
//}
//
//inline std::pair<std::set<boost::shared_ptr<Observable> >::iterator, bool>
//Observer::registerWith(const boost::shared_ptr<Observable>& h) {
//    if (h) {
//        h->registerObserver(this);
//        return observables_.insert(h);
//    }
//    return std::make_pair(observables_.end(), false);
//}
//
//inline size_t Observer::unregisterWith(const boost::shared_ptr<Observable>& h) {
//    if (h)
//        h->unregisterObserver(this);
//    return observables_.erase(h);
//}
//
//inline void Observer::unregisterWithAll() {
//    for (iterator i=observables_.begin(); i!=observables_.end(); ++i)
//        (*i)->unregisterObserver(this);
//    observables_.clear();
//}
//
//inline Observable::Observable(const Observable&) {
//    // the observer set is not copied; no observer asked to
//    // register with this object
//}
//
///*! \warning notification is sent before the copy constructor has
//             a chance of actually change the data
//             members. Therefore, observers whose update() method
//             tries to use their observables will not see the
//             updated values. It is suggested that the update()
//             method just raise a flag in order to trigger
//             a later recalculation.
//*/
//inline Observable& Observable::operator=(const Observable& o) {
//    // as above, the observer set is not copied. Moreover,
//    // observers of this object must be notified of the change
//    if (&o != this)
//        notifyObservers();
//    return *this;
//}
//
//
//std::pair<std::set<Observer*>::iterator, bool>
//Observable::registerObserver(Observer* o) {
//    return observers_.insert(o);
//}
//
//inline size_t Observable::unregisterObserver(Observer* o) {
//    return observers_.erase(o);
//}
//
//inline void Observable::notifyObservers() {
//    bool successful = true;
//    std::string errMsg;
//    for (iterator i=observers_.begin(); i!=observers_.end(); ++i) {
//        try {
//            (*i)->update();
//        } catch (std::exception& e) {
//            successful = false;
//            errMsg = e.what();
//        } catch (...) {
//            successful = false;
//        }
//    }
//    ENSURE(successful, "could not notify one or more observers: " << errMsg);
//}
//
#endif
