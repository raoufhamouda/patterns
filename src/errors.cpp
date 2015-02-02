#include <iostream>
#include <string>

#include <boost/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <exception>
#include <sstream>
#include <stdexcept>
#include <set>
#include "errors.hpp"

namespace {
    std::string format(const std::string& file, long line,
                       const std::string& message) {
        std::ostringstream msg;
        msg << "\n" << file << ":" << line << ": " << message;;
        return msg.str();
    }
}


Error::Error(const std::string& file, long line, const std::string& message){
    message_ = boost::shared_ptr<std::string>(new std::string(
                                  format(file, line, message)));
}

const char* Error::what() const throw () {
    return message_->c_str();
}
