/*! \file errors.hpp
    \brief Classes and functions for error handling.
*/

#ifndef errors_hpp
#define errors_hpp

#include <iostream>
#include <string>

#include <boost/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <exception>
#include <sstream>
#include <stdexcept>
#include <set>


//! Base error class
class Error : public std::exception {

public:
    /*! The explicit use of this constructor is not advised.
        Use the FAIL macro instead.
    */
    Error(const std::string& file,
          long line,
          const std::string& message = "");
    /*! the automatically generated destructor would
        not have the throw specifier.
    */
    virtual ~Error() throw() {}
    //! returns the error message.
    const char* what() const throw ();

private:
    boost::shared_ptr<std::string> message_;
};

/*! \def FAIL
    \brief throw an error (possibly with file and line information)
*/
#define FAIL(message) \
    std::ostringstream _msg_stream; \
    _msg_stream << message; \
    throw Error(__FILE__,__LINE__,_msg_stream.str()); \


/*! \def ASSERT
    \brief throw an error if the given condition is not verified
*/
#define ASSERT(condition,message) \
if (!(condition)) { \
    std::ostringstream _msg_stream; \
    _msg_stream << message; \
    throw Error(__FILE__,__LINE__,_msg_stream.str()); \
 } else 


/*! \def REQUIRE
    \brief throw an error if the given pre-condition is not verified
*/
#define REQUIRE(condition,message) \
if (!(condition)) { \
    std::ostringstream _msg_stream; \
    _msg_stream << message; \
    throw Error(__FILE__,__LINE__,_msg_stream.str()); \
 } else 


/*! \def ENSURE
    \brief throw an error if the given post-condition is not verified
*/
#define ENSURE(condition,message) \
if (!(condition)) { \
    std::ostringstream _msg_stream; \
    _msg_stream << message; \
    throw Error(__FILE__,__LINE__,_msg_stream.str()); \
 } else 


#endif

