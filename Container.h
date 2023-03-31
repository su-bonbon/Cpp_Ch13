/// @file Container.h
/// @author Sujin Lee
/// @date 2/24/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief Header file for Container.cpp
/// @note 25hr

#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <initializer_list>


/// A Container stores a set of values The storage of the Container is
/// handled automatically, being ecpanded as needed.

class Container {
public:
    /// Member types.
    using value_type = int;
    using size_type = std::size_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    #ifdef DEBUG
        Container& operator = (const Container&) = delete;
    #endif

    /// Default ctor.
    Container(size_type count = 0) {
        capacity = count;
        used = 0;
        data = new value_type[count];
    }
    //: capacity(count), used(0), data(new value_type[count]) {} //SAME!!!!

    /// Copy ctor
    Container(const Container& other);

    /// Initializer List ctor
    Container(const std::initializer_list<value_type>& init);

    /// Destructor.
    ~Container();

    /// Returns the number of elements in the container.
    size_type size() const { return used; }

    /// Checks if the container has no elements, e.g begin() == end()
    /// @returns true if the container is empty, false otherwise.
    bool empty() const { return begin() == end(); }

    /// Returns a pointer to the first element.
    pointer begin() { return data; }
    const_pointer begin() const { return data; }

    /// Returns a pointer to the end (the element following the last element).
    pointer end() { return begin() + size(); }
    const_pointer end() const { return begin() + size(); }

    /// Adds an element to the end.
    void push_back(const value_type& value);

    /// Removes a single item from the container.
    void erase(pointer pos);

    /// After this call, size() returns zero. The capacity remains unchanged.
    void clear() {used = 0;}

    /// Exchanges the contents of the container with those of other.
    void swap(Container& other);

    /// Finds the first element equal to the given target. Search begins at pos.
    /// @returns pointer to the element if found, or end() if not found.
    pointer find(const value_type& target, pointer pos = nullptr);
    // const pointer find(const const value_type& target, pointer pos = nullptr) const;

/// ------------------MEMBER_OPERATOR_OVERLOADING_FUNCTION---------------------///
    /// Replaces the contents of the container with a copy of the contents of rhs.
    /// @returns this
    Container& operator=(const Container& rhs);

    /// Returns other appended to this.
    /// @returns this
    Container& operator+=(const Container& rhs);

private:
    size_type capacity;  ///< Physical capacity of container.
    size_type used;      ///< Number of items in container.
    pointer   data;      ///< Array of items.
};

/// ------------------NON_MEMBER_OPERATOR_OVERLOADING_FUNCTION-----------------///
/// Equality comparison operator.
/// @returns true if lhs compares equal to rhs, otherwise false
bool operator==(const Container& lhs, const Container& rhs);

/// Inequality comparison operator.
/// @returns true if lhs does not compare equal to rhs, otherwise false
bool operator!=(const Container& lhs, const Container& rhs);

/// Returns the concatenation of lhs and rhs.
Container operator+(const Container& lhs, const Container& rhs);

/// Writes a formatted representation of rhs to output.
/// @returns output
std::ostream& operator<<(std::ostream& output, const Container& oset);




/// related non-member functions

/// Checks the contents of lhs and rhs are equal, that is, they have the same
/// number of elements and each element in lhs compares equal with the element
/// in rhs at the same position.
bool equal(const Container& lhs, const Container& rhs);

/// Performs stream output on Containers, using "{1,2,3}" format.
void write(std::ostream& output, const Container& container);

#endif /* CONTAINER_H */
