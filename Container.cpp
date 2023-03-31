/// @file Container.cpp
/// @author Sujin Lee
/// @date 2/24/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief Header file for Container.cpp
/// @note 25hr

#include <cassert>
#include "Container.h"

/// Copies the elements in the range defined by [first, last)
/// to another range beginning at dest.
// static void copy(const int* first, const int* last, int* dest);

/// Copies the elements in the range defined by [first,last) to another
/// range beginning at d_first. The elements are copied in forward order.
static void copy(Container::const_pointer first,
                 Container::const_pointer last,
                 Container::pointer d_first);

/// Returns true if the range [first1,last1) is equal to the range
/// [first2,last2) and false otherwise.
static bool equal(Container::const_pointer first1,
                  Container::const_pointer last1,
                  Container::const_pointer first2,
                  Container::const_pointer last2);

/// Returns a pointer to the first element in the range [first,last) that
/// compares equal to value, or last if no such element found.
static Container::pointer find(Container::pointer first,
                              Container::pointer last,
                              const Container::value_type& value);

//Container::Container(const Container& other) {
//    //Container box1();  // ????
//    capacity = other.size();
//    used = other.size();
//    data = new value_type[other.size()];
//    pointer ptr = begin();
//    for (auto item : other) {
//        *ptr = item;
//        ptr++;
//    }
//}----------my copy ctor

Container::Container(const Container& other)
: Container(other.size()) {  // by calling default ctor, it saved lines of code  == line14#
    copy(other.begin(), other.end(), begin());
    used = other.size();
}

Container::Container(const std::initializer_list<value_type>& init)
: Container(init.size()) {
    copy(init.begin(), init.end(), begin());
    used = init.size();
}

Container::~Container() {
    delete [] data;
    data = nullptr;
    used = capacity = 0;
}

void Container::push_back(const value_type& value) {
    if (size() == capacity) {
        pointer copy_of_data = new value_type[capacity +=8] ;  // can use auto instead of pointer
        // auto copy_of_data { new value_type[capacity += 8] };  // this is modern way to do 1
        // auto copy_of_data { new value_type[capacity += 8] {} };  // this is modern way to do 2
        // auto copy_of_data new value_type[capacity += 8] {} ;  // this is modern way to do 3
        copy(begin(), end(), copy_of_data);
        delete [] data;
        data = copy_of_data;
    }

    *(data + used++) = value;
}

void Container::erase(pointer pos) {
    if (pos != nullptr) {
        assert(pos >= begin());
        assert(pos < end());
        copy(pos + 1, end(), pos);
        --used;
    }
}

void Container::swap(Container& other) {
    size_type temp_size = 0;  // better not use auto
    pointer temp_ptr = nullptr;  // better not use auto
    // auto temp_size = size_type{0}; this will be possible to use auto
    //{} << this initializes default value

    // swap members
    temp_size = capacity;
    capacity = other.capacity;
    other.capacity = temp_size;

    temp_size = used;
    used = other.used;
    other.used = temp_size;

    temp_ptr = data;
    data = other.data;
    other.data = temp_ptr;
}

Container::pointer
Container::find(const value_type& target, pointer pos) {
    pointer first = pos == nullptr ? begin() : pos;
    pointer location = end();

    assert(first != location);
    assert(first < end());

    while (first != location) {
        if (*first == target) {
            location = first;
        }
        else {
            ++first;
        }
    }
    return location;
}

bool equal(const Container& lhs, const Container& rhs) {
    Container::const_pointer first1 = lhs.begin();  // can use auto
    Container::const_pointer last1 = lhs.end();  // can use auto
    Container::const_pointer first2 = rhs.begin();  // can use auto

    bool result = lhs.size() == rhs.size();

    while (result && first1 != last1) {
        result = *first1++ ==*first2++;
    }

    return result;
}

void write(std::ostream& output, const Container& container) {
    char separator[2] = "";

    output << '{';

    for (const Container::value_type& item : container) {
        output << separator << item;
        *separator = ',';
    }
    output << '}';
}

/// -------------------MEMBER_OPERATOR_OVERLOADING_FUNCTION-----------------///
Container& Container::operator=(const Container& rhs) {
    // 1.  Deallocate any memory that MyClass is using internally
    // 2.  Allocate some memory to hold the contents of rhs
    // 3.  Copy the values from rhs into this instance
    // 4.  Return *this
    if (this != &rhs) {

        delete [] data;
        capacity = rhs.capacity;
        used = rhs.used;

        data = nullptr;
        data = new value_type[rhs.capacity];
        copy(rhs.begin(), rhs.end(), begin());

    }
    return *this;  // 4. return *this
}

/// Returns other appended to this.
/// @returns this
Container& Container::operator+=(const Container& rhs) {

    for ( const_pointer i = rhs.begin(); i < rhs.end(); i++ ) {
        push_back(*i);
    }

    return *this;
}
/// ---------------NON_MEMBER_OPERATOR_OVERLOADING_FUNCTION-----------------///
/// Equality comparison operator.
/// @returns true if lhs compares equal to rhs, otherwise false
bool operator==(const Container& lhs, const Container& rhs) {
    return ::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/// Inequality comparison operator.
/// @returns true if lhs does not compare equal to rhs, otherwise false
bool operator!=(const Container& lhs, const Container& rhs) {
    return !(equal(lhs, rhs));
}

/// Returns the concatenation of lhs and rhs.
Container operator+(const Container& lhs, const Container& rhs) {
    Container result(lhs.size());
    result = lhs;
    result += rhs;
    return result;
}

std::ostream& operator<<(std::ostream& output, const Container& oset) {

    char separator[2] = "";

    output << '{';

    for (const Container::value_type& item : oset) {
        output << separator << item;
        *separator = ',';
    }
    output << '}';

    return output;
}

/// ------------------STATIC_HELPER_FUNCTIONS-------------------------///
//static void copy(const int* first, const int* last, int* dest) {
//    while (first != last) {
//        *dest++ = *first++;
//    }
//}

/// Copies the elements in the range defined by [first,last) to another
/// range beginning at d_first. The elements are copied in forward order.
static void copy(Container::const_pointer first,
                 Container::const_pointer last,
                 Container::pointer d_first) {
    while (first != last) {
        *d_first++ = *first++;
    }
}



/// Returns true if the range [first1,last1) is equal to the range
/// [first2,last2) and false otherwise.
static bool equal(Container::const_pointer first1,
                  Container::const_pointer last1,
                  Container::const_pointer first2,
                  Container::const_pointer last2) {
    bool result = last1 - first1 == last2 - first2;

    while (result && first1 != last1) {
        result = *first1++ ==*first2++;
    }

    return result;
}

/// Returns a pointer to the first element in the range [first,last) that
/// compares equal to value, or last if no such element found.
static Container::pointer find(Container::pointer first,
                               Container::pointer last,
                               const Container::value_type& value) {
    Container::pointer location = last;
    assert(first != last);
    assert(first < last);

    while (first != last) {
        if (*first == value) {
            location = first;
        }
        else {
            ++first;
        }
    }
    return location;
}
