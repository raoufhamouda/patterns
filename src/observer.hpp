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
    typedef std::set<boost::shared_ptr<Observable> >::iterator iterator;

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

#endif
