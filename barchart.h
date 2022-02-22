/*

File: barchart.h
Author: Danyal Warraich
Class: CS 251
Project 3 - Animated Bar Chart
Description: For this abstraction, space will be allocated to heap using the private data member of pointer to the C-style array. Space will allocate based on n value. Tracks of how many bars are added using the variable size.

*/
#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h"  // used in autograder, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";

// Color codes for Mimir (light mode)
// const string RED("\033[1;36m");
// const string PURPLE("\033[1;32m");
// const string BLUE("\033[1;33m");
// const string CYAN("\033[1;31m");
// const string GREEN("\033[1;35m");
// const string GOLD("\033[1;34m");
// const string BLACK("\033[1;37m");
// const string RESET("\033[0m");
// const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for Replit (dark mode terminal)
 const string CYAN("\033[1;36m");
 const string GREEN("\033[1;32m");
 const string GOLD("\033[1;33m");
 const string RED("\033[1;31m");
 const string PURPLE("\033[1;35m");
 const string BLUE("\033[1;34m");
 const string BLACK("\033[1;37m");
 const string RESET("\033[0m");
 const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, BLACK};

//
// BarChart
//
class BarChart {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    //
    Bar* bars;  // pointer to a C-style array
    int capacity;
    int size;
    string frame;
 public:
    // default constructor:
    BarChart() {
        // Does not allocate memory for bars
        // initializes private variables to default values
        bars = nullptr;
        capacity = 0;
        size = 0;
    }
    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n) {
        if (n < 0) {
            bars = nullptr;
            size = 0;
            capacity = n;
        }
        else {
        bars = new Bar[n];
        capacity = n;
        size = 0;
        }
    }
    //
    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    //
    BarChart(const BarChart& other) {
        this->bars = new Bar[other.capacity];
        this->capacity = other.capacity;
        this->size = other.size;
        this->frame = other.frame;
        for (int i = 0; i < other.size; i++) {
            this->bars[i] = other.bars[i];
        }
    }
    //
    // copy operator=
    //
    // Called when you assign one BarChart into another, i.e. this = other;
    //
    BarChart& operator=(const BarChart& other) {
        BarChart bc;
        if (this == &other) {
            return *this;
        }
        delete[] bars; // maybe do (*this);
        this->bars = new Bar[other.capacity];
        this->capacity = other.capacity;
        this->size = other.size;
        this->frame = other.frame;
        for (int i = 0; i < other.size; i++) {
            this->bars[i] = other.bars[i];
        }
        return *this;
    }
    // clear
    // frees memory and resets all private member variables to default values.
    void clear() {
        delete[] bars;
        bars = nullptr;
        capacity = 0;
        size = 0;
    }
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    //
    virtual ~BarChart() {
        // maybe use if statement like ourvector;
        if (bars != nullptr) {
            delete[] bars;
        }
    }
    // setFrame
    void setFrame(string frame) {
        this->frame = frame;
    }
    // getFrame()
    // Returns the frame of the BarChart object.
    string getFrame() {
        return this->frame;
    }
    // addBar
    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is not room
    bool addBar(string name, int value, string category) {
        if (capacity > 0 && size < capacity) {
            Bar b(name, value, category);
            this->bars[size] = b;
            size++;
            return true;
        } else if (capacity == size){
                delete[] this->bars;
                capacity = 0;
                this->bars = nullptr;
        }
        return false;
    }
    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize() {
        return size;
    }
    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar& operator[](int i) {
        // Bar b;
        if (i < 0 || i >= size) {
            throw out_of_range("C-array: i out of bounds");
        }
        return bars[i];
    }
    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.  output is any stream (cout,
    // file stream, or string stream).
    // Format:
    // "frame: 1
    // aname 5 category1
    // bname 4 category2
    // cname 3 category3" <-newline here
    void dump(ostream &output) {
        // TO DO:  Write this function.
        sort(bars, bars+size, greater<Bar>());
        output << "frame: " <<  getFrame() << endl;
        for (int i = 0; i < size; i++) {
            output << bars[i].getName() << " " << bars[i].getValue() << " " << bars[i].getCategory();
            output << endl;
        }
    }
    // graph
    // Used for printing out the bar.
    // output is any stream (cout, file stream, string stream)
    // colorMap maps category -> color
    // top is number of bars you'd like plotted on each frame (top 10? top 12?)
    // this is number of BOXs that should be printed for the top bar (max value)
    void graph(ostream &output, map<string, string> &colorMap, int top) {
    	int lenMax = 60;  // this is number of BOXs that should be printed
        sort(bars, bars+size, greater<Bar>());
        string barstr = "";
        for (int i = 0; i < lenMax; i++) { barstr += BOX; }
        if (colorMap.empty() || bars[0].getCategory() == "") {
                colorMap[bars[0].getCategory()] = "\033[1;37m";
                output << colorMap[bars[0].getCategory()] << barstr << " ";
                output << bars[0].getName() << " " << bars[0].getValue() << endl;
        } else {
        output << colorMap[bars[0].getCategory()] << barstr << " ";
        output << bars[0].getName() << " " << bars[0].getValue() << endl;
        }
        for (int i = 1; i < top; i++) {
            double boxes = (double)bars[i].getValue()/(double)bars[0].getValue();
            boxes = boxes * lenMax;
            int box = int(boxes);
            barstr = "";
            for (int j = 0; j < box; j++) { barstr += BOX; }
            if (colorMap.empty() || bars[i].getCategory() == "") {
                colorMap[bars[i].getCategory()] = "\033[1;37m";
                output << colorMap[bars[i].getCategory()] << barstr << " ";
                output << bars[i].getName() << " " << bars[i].getValue() << endl;
            } else {
                output << colorMap[bars[i].getCategory()] << barstr << " ";
                output << bars[i].getName() << " " << bars[i].getValue() << endl;
            }
        }
    }
};

