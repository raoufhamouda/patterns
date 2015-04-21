#ifndef test_observer_hpp
#define test_observer_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/assert.hpp>
#include <exception>
#include <stdexcept>

#include "observer.hpp"
#include "errors.hpp"

class Subject : public Observable{
  private:
    double amount_;
    int year_;
  public:
    void calculateInterest(double amount, double rate, int years) {
      amount_ = amount;
      year_ = 0;
      notifyObservers();
      for (year_=1; year_<=years; ++year_) {
        amount_ = amount_*(1.0 + rate);
        notifyObservers();
      }
    }
    double amount() {
      return amount_;
    }
    double year() {
      return year_;
    }
};

class Vtk : public Observer
{
    boost::shared_ptr<Subject> subject_;

    boost::shared_ptr<std::ofstream> vtk_stream_;
    std::string name_;

    public:

    Vtk(boost::shared_ptr<Subject> subject, const char * vtk_filename, std::string name):
        subject_(subject),
        vtk_stream_(boost::shared_ptr<std::ofstream>(new std::ofstream(vtk_filename))),
        name_(name){
            registerWith(subject_);
        }
    ~Vtk(){ vtk_stream_->close();}
    Vtk(const Vtk & observer)
        : Observer(observer),
        subject_(observer.subject_),
        name_("Copy of "+observer.name_)
    {}

    void update() {
      (*vtk_stream_) << subject_->year() << " "
          << subject_->amount() << std::endl;
    }
};

#endif
