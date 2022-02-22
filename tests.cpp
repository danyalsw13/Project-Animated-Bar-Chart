#include <iostream>
#include "barchartanimate.h"
using namespace std;


bool testBarDefaultConstructor() {
	Bar b;
    if (b.getName() != "") {
    	cout << "testBarDefaultConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 0) {
    	cout << "testBarDefaultConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "") {
    	cout << "testBarDefaultConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarParamConstructor() {
	Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
    	cout << "testBarParamConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 9234324) {
    	cout << "testBarParamConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "US") {
    	cout << "testBarParamConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarParamConstructor: all passed!" << endl;
    return true;
}

bool testBarOperatorConstructor() {
    Bar b1("Beijing", 400, "East Asia");
    Bar b2("Egypt", 400, "Middle East");
    if (b1 < b2) {
        cout << "testBarOperatorConstructor: b1 < b2 passed!" << endl;
        cout << b1.getValue() << endl;
        cout << b2.getValue() << endl;
        return true;
    } else if (b1 > b2) {
        cout << "testBarOperatorConstructor: b1 > b2 passed!" << endl;
        cout << b1.getValue() << endl;
        cout << b2.getValue() << endl;
        return true;
    } 
    cout << "testBarOperatorConstructor: all failed!" << endl;
    return false;
}

bool testBarOperatorConstructor2() {
    Bar b1("Chicago", 560, "US");
    Bar b2("Tokyo", 720, "Japan");
    if (b1 <= b2) {
        cout << "testBarOperatorConstructor2: b1 <= b2 passed!" << endl;
        cout << b1.getValue() << endl;
        cout << b2.getValue() << endl;
        return true;
    } else if (b1 >= b2) {
        cout << "testBarOperatorConstructor2: b1 >= b2 passed!" << endl;
        cout << b1.getValue() << endl;
        cout << b2.getValue() << endl;
        return true;
    }
    cout << "testBarOperatorConstructor: all failed!" << endl;
    return false;
    
}

bool testBarOperatorConstructor3() {
    Bar b1("Germany", 560, "US");
    Bar b2("Franch", 220, "Japan");
    if (b1 <= b2) {
        cout << "testBarOperatorConstructor2: b1 <= b2 passed!" << endl;
        cout << b1.getValue() << endl;
        cout << b2.getValue() << endl;
        return true;
    } else if (b1 >= b2) {
        cout << "testBarOperatorConstructor2: b1 >= b2 passed!" << endl;
        cout << b1.getValue() << endl;
        cout << b2.getValue() << endl;
        return true;
    }
    cout << "testBarOperatorConstructor: all failed!" << endl;
    return false;
    
}

// Testing BarChart header file member functions
bool testBarChartDefaultConstructor() {
    BarChart b;
    if (b.getSize() == 0) {
        cout << "testBarChartDefaultConstructor(): size";
        cout << " passed!" << endl;
        return true;
    }
    cout << "testBarChartDefaultConstructor(): size failed!" << endl;
    return false;
   
}

bool testBarChartParamConstructor() {
    BarChart b(10);
    if (b.getSize() != 10) {
        cout << "testBarChartParamConstructor(): size failed!" << endl;
        return false;
    }
    cout << "testBarChartParamConstructor(): size passed!" << endl;
    return true;
}

bool testBarChartNegative() {
    BarChart b(-2);
    
    if (b.getSize() == 0) {
        cout << "testBarChartClear(): passed!" << endl;
        return true;
    }
    cout << "testBarChartClear(): failed!" << endl;
    return false;
}

bool testBarChartFrame() {
    BarChart b;
    b.setFrame("1982");
    if (b.getFrame() == "1982") {
        cout << "testBarChartFrame(): passed!" << endl;
        return true;
    }
    cout << "testBarChartFrame(): failed!" << endl;
    return false;
}

bool testBarChartaddBar() {
    BarChart bc(3);
    bc.addBar("Chicago", 1020, "US");
    bc.addBar("NYC", 1300, "US");
    bc.addBar("Paris", 1200, "France");
    bc.clear();
    if (bc.getSize() == 0) {
        cout << "testBarChartClear(): passed!" << endl;
        return true;
    }
    cout << "testBarChartClear(): failed!" << endl;
    return false;
    
}
bool testBarChartsize() {
    int n = 3;
    BarChart bc(n);
    bc.addBar("Chicago", 1020, "US");
    bc.addBar("NYC", 1300, "US");
    bc.addBar("Paris", 1200, "France");
    bc.setFrame("1950");
    bc.dump(cout);
    if (bc.getSize() == n) {
        cout << "testBarChartsize(): passed!" << endl;
        return true;
    } else if (bc.getSize() <= n) {
        cout << "testBarChartsize(): passed! size <= n" << endl;
        return true;
    }
    return false;
}

bool testBarChartOperator() {
    int n = 3;
    BarChart bc(n);
    bc.addBar("Chicago", 1020, "US");
    bc.addBar("NYC", 1300, "US");
    bc.addBar("Paris", 1200, "France");
    for (int i = 0; i < n; i++) {
        cout << bc[i].getName() << " ";
        cout << bc[i].getValue() << " ";
        cout << bc[i].getCategory();
        cout << endl;
    }
    if (bc[0].getName() == "Chicago") {
        cout << "testBarChartOperator(): passed!" << endl;
        return true;
    }
    cout << "testBarChartOperator(): failed!" << endl;
    return false;
}

bool testBarChartgraph() {
    int n = 3;
    BarChart bc(n);
    bc.addBar("Chicago", 1020, "US");
    bc.addBar("NYC", 1300, "US");
    bc.addBar("Paris", 1200, "France");
    bc.setFrame("1950");
    string red("\033[1;31m");
    string blue("\033[1;34m");
    string black("\033[1;37m");
    map<string, string> colorMap;
    colorMap["US"] = red;
    colorMap["France"] = blue;
    bc.graph(cout, colorMap, 3);
}

bool testBarChartEdgeCase() {
string frame = "1";
 int n = -2;
 BarChart bc(n);
 bc.setFrame(frame);
 bc.getFrame();
// cout << "Size: " << bc.getSize() << endl;
// BarChart bc(-2);
bc.addBar("a", 1, "cat");
// cout << "Size: " << bc.getSize() << endl;
bc.addBar("a", 3, "cat");
// cout << "Size: " << bc.getSize() << endl;
 bc.addBar("a", 2, "cat");
// cout << "Size: " << bc.getSize() << endl;
 bc.addBar("a", 5, "cat");
// cout << "Size: " << bc.getSize() << endl;
 bc.addBar("a", 4, "cat");
// cout << "Size: " << bc.getSize() << endl;
 bc.addBar("a", 6, "cat");
// cout << "Size: " << bc.getSize() << endl;

}

bool BarChartAnimateDefaultCons() {
    BarChartAnimate bca("X", "Y", "Z");
    if (bca.getSize() == 0) {
        cout << "BarChartAnimateSize(): passed!" << endl;
        return true;
    }
    cout << "BarChartAnimateSize(): failed!" << endl;
    return false;
}

bool BarChartAnimateTestCase() {
    string filename = "cities.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
    int count = 0;
	while (!inFile.eof()) {
		bca.addFrame(inFile);
		count++;
		if (count == 5) {
		   break; 
		}
	}
	if (bca.getSize() == 5) {
	    cout << "size in add frame passed!" << endl;
	    return true;
	}
	cout << "size in add frame failed!" << endl;
	return false;
}

/* Uncomment this part to check the test case
bool BarChartAnimateTestCase2() {
string filename = "cities.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
    int count = 0;
	while (!inFile.eof()) {
		bca.addFrame(inFile);
		count++;
		if (count == 2) {
		   break; 
		}
	}
	 bca.animate(cout, 2, -1);
    if (bca.getSize() == 2) {
	    cout << "size in add frame passed!" << endl;
	    return true;
	}
	cout << "size in add frame failed!" << endl;
	return false;
    
	// bca.animate(cout, 12, -1);
}
*/

int main() {
	testBarDefaultConstructor();
	testBarParamConstructor();
	testBarOperatorConstructor();
	testBarOperatorConstructor2();
	testBarOperatorConstructor3();

	testBarChartDefaultConstructor();
	testBarChartParamConstructor();
	testBarChartNegative();
	testBarChartFrame();
	testBarChartaddBar();
	testBarChartsize();
	testBarChartOperator();
	testBarChartgraph();
	testBarChartEdgeCase();
	
	BarChartAnimateDefaultCons();
	BarChartAnimateTestCase();
//	BarChartAnimateTestCase2(); // uncomment to check this case

    return 0;
}