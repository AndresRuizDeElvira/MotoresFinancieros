//
//  Comparison.hpp
//  
//
//  Created by Andres on 9/10/18.
//

#ifndef Comparison_h
#define Comparison_h
inline bool close(Real x, Real y, Size n) {
    // Deals with +infinity and -infinity representations etc.
    if (x == y)
        return true;
    
    Real diff = std::fabs(x-y), tolerance = n * QL_EPSILON;
    
    if (x * y == 0.0) // x or y = 0.0
        return diff < (tolerance * tolerance);
    
    return diff <= tolerance*std::fabs(x) &&
    diff <= tolerance*std::fabs(y);
}

inline bool close_enough(Real x, Real y) {
    return close_enough(x,y,42);
}

inline bool close_enough(Real x, Real y, Size n) {
    // Deals with +infinity and -infinity representations etc.
    if (x == y)
        return true;
    
    Real diff = std::fabs(x-y), tolerance = n * QL_EPSILON;
    
    if (x * y == 0.0) // x or y = 0.0
        return diff < (tolerance * tolerance);
    
    return diff <= tolerance*std::fabs(x) ||
    diff <= tolerance*std::fabs(y);
}



//! compare two objects by date
/*! There is no generic implementation of this struct.
 Template specializations will have to be defined for
 each needed type (see CashFlow for an example.)
 */
template <class T> struct earlier_than;

/* partial specialization for shared pointers, forwarding to their
 pointees. */
template <class T>
struct earlier_than<ext::shared_ptr<T> > {
    typedef ext::shared_ptr<T> first_argument_type;
    typedef ext::shared_ptr<T> second_argument_type;
    typedef bool result_type;
    
    bool operator()(const ext::shared_ptr<T>& x,
                    const ext::shared_ptr<T>& y) const {
        return earlier_than<T>()(*x,*y);
    }
};

}


#endif





#endif /* Comparison_h */
