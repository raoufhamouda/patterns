#ifndef composite_hpp
#define composite_hpp
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>


template <class T>
class Composite : public T {
    protected:

        std::vector<boost::shared_ptr<T> > components_;

    public:
        void add(const boost::shared_ptr<T> & c) {components_.push_back(c);}

        void remove(const boost::shared_ptr<T> & c){ 
            components_.erase(
                    std::remove(components_.begin(), components_.end(), c),
                    components_.end());
        }

        boost::shared_ptr<T> getChild(const int & index){
            return components_[index];
        }
};

#endif

