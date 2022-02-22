/*

File: bar.h
Author: Danyal Warraich
Class: CS 251
Project 3 - Animated Bar Chart
Description: The purpose of this header file is to initialize
the data members that are extracted from the file. This header
file uses default and parameterized constructors to declare
variables with values. Overloading operator is used to compare
between objects or list of objects, so, it can be easier to
sort the data in descending order.

*/
#include <iostream>
#include <string>
#include "myrandom.h"  // used in autograder, do not remove
using namespace std;

//
// Bar
//
class Bar {
 private:
    // Private member variables for a Bar object
    // TO DO:  Define private member variables for this class
    // NOTE: You should not be allocating memory on the heap for this class.
    string name;
    string category;
    int value;
 public:
    // default constructor:
    Bar() {
        // Defining and initializing the variables
        this->name = "";
        this->category = "";
        this->value = 0;
    }
    //
    // a second constructor:
    //
    // Parameter passed in constructor Bar object.
    //
    Bar(string name, int value, string category) {
        // Initilaize and declare private
        // data members with passed by values
        this->name = name;
        this->value = value;
        this->category = category;
    }
    // destructor:
    virtual ~Bar() {}

    // getName:
	string getName() {
        // accessor returns the city's name assigned
        return this->name;
	}
    // getValue:
	int getValue() {
		// accessor returns the value assigned
        return this->value;
	}
    // getCategory:
	string getCategory() {
        // accessor returns the city's region
        return this->category;
	}
	// operators
    // TO DO:  Write these operators.  
    // This allows you to compare two Bar
    // objects.  Comparison should be 
    // based on the Bar's value.  For example:
	bool operator<(const Bar &other) const {
	    // return true, comparsion based on value
        return this->value < other.value;
	}
	bool operator<=(const Bar &other) const {
	    // (*this) is object not pointer to object
	    // when this stands alont it is pointer to object
        return !((*this) > other);
	}
	bool operator>(const Bar &other) const {
        //return true;
        return other < (*this);
	}
	bool operator>=(const Bar &other) const {
        return !((*this) < other);
	}
};