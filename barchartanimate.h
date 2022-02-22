/*

File: barchart.h
Author: Danyal Warraich
Class: CS 251
Project 3 - Animated Bar Chart
Description: The purpose of this header file is to initialize
the data members that are extracted from the file. This header
file dynamically allocates space if size and capacity of the Bar
object is same. It also animates and shows the graph.

*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <unistd.h>
#include "myrandom.h" // used in autograder, do not remove
#include "barchart.h"
  
using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    map<string, string> colorMap;
    string title, xlabel, source;
    int colorIndex;

 public:

    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
        barcharts = new BarChart[4];
        size = 0;
        capacity = 4;
        colorIndex = 0;
        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
        if (barcharts != nullptr) {
            delete[] barcharts;
        }
    }
    // Parsing the file and extracting the fields and storing it
    // in private data members using barChart animate class
    void parseLine1(string& line, string& frame, string& name) {
         size_t pos = line.find(",");
         frame = line.substr(0, pos);
       //  cout << frame << endl;
         line = line.substr(pos+1, line.size()-frame.size()-1);
        // cout << line << endl;
         pos = line.find(",");
         name = line.substr(0, pos);
         line = line.substr(pos+1, line.size()-name.size()-1);
        // cout << name << endl;
    }
    // Parsing the file and extracting the fields and storing it
    // in private data members using barChart animate class
    void parseLine2(string& line, string& value, string& category) {
        size_t pos = line.find(",");
        string country = line.substr(0, pos);
        line = line.substr(pos+1, line.size()-country.size()-1);
     //  cout << country << endl;
        pos = line.find(",");
        value = line.substr(0, pos);
        line = line.substr(pos+1, line.size()-value.size()-1);
        // cout << value << endl;
        // cout << line << endl;
        category = line;
        // cout << category << endl;
        line = "";
    }
    
    // fills the map with category as key and colorIndex as
    // value and based on this graph bar animates the color
    void fillMap(string& category, int& colorIndex) {
        if (colorIndex <= 6) {
            if (!colorMap.count(category)) {
                colorMap[category] = COLORS[colorIndex];
                colorIndex++;
            }
        } else if (colorIndex > 6) {
            colorIndex = 0;
            if (!colorMap.count(category)) {
                colorMap[category] = COLORS[colorIndex];
                colorIndex++;
            }
        }
    }
    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity (see
    // ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream &file) {
        string line, name, frame, value, category;
        int val = 0, i = 0;
            getline(file, line);
            getline(file, line);
            if (line.empty()) { 
                file.close();
                return; }
            int n = stoi(line);
            BarChart b(n);
            while (i < n) {
                getline(file, line);
                parseLine1(line, frame, name);
                parseLine2(line, value, category);
                val = stoi(value);
                fillMap(category, colorIndex);;
                b.addBar(name, val, category);
                b.setFrame(frame);
                i++;
            }
            if (size == capacity) {
                int newCapacity = capacity * 2;
                BarChart* newbarcharts = new BarChart[newCapacity];  
                for (int i = 0; i < size; i++) { newbarcharts[i] = barcharts[i]; }
                delete[] barcharts;
                barcharts = newbarcharts;
                capacity = newCapacity;
            }
            this->barcharts[size] = b;
            size++;
    }

    // animate:
    // this function plays each frame stored in barcharts.  In order to see the
    // animation in the terminal, you must pause between each frame.  To do so,
    // type:  usleep(3 * microsecond);
    // Additionally, in order for each frame to print in the same spot in the
    // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    // in between each frame.
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;
			if (endIter == -1) {
			    endIter = size;
			}
			for (int i = 0; i < endIter; i++) {
			    usleep(3 * microsecond); // Set a delay
			    output << CLEARCONSOLE;
			    output << "\033[1;37m" << this->title << endl;
			    output << this->source << endl;
			    this->barcharts[i].graph(output, colorMap, top);
			    output << "\033[1;37m" << this->xlabel << endl;
			  	output << "Frame: " << this->barcharts[i].getFrame() << endl;
			}
	}

    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize(){
        return size;
    }

    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart& operator[](int i){
        BarChart bc;
        if (i < 0 || i >= size) {
            throw out_of_range("C-array: i out of bounds");
        }
        return barcharts[i];
    }
};
