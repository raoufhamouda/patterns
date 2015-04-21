/*! \file visitor.hpp
    \brief degenerate base class for the Acyclic Visitor pattern
    Adds new operations to existing object structure without modifying it.
    Separates an algorithm from an object structure on which it operates.
*/

#ifndef visitor_hpp
#define visitor_hpp

//! degenerate base class for the Acyclic %Visitor pattern
/*! \ingroup patterns */
class AcyclicVisitor {
  public:
    virtual ~AcyclicVisitor() {}
};

//! %Visitor for a specific class
template <class T>
class Visitor {
  public:
    virtual ~Visitor() {}
    virtual void visit(T&) = 0;
};

#endif
