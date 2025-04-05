
#include "test/interval_test.h"
#include "test/approx_test.h"
#include "test/newton_test.h"
#include <iostream>
using namespace std;


int main() {
    cout << "--------------- Running tests for interval.h ---------------" << endl;
    interval_test();
    cout << "------------------------------------------------------------" << endl << endl;

    cout << "------------ Testing the approximation techniqies -----------" << endl;
    approx_test_function1();
    approx_test_function2();
    approx_test_function3();
    approx_test_function4();
    cout << "--------------------------------------------------------------" << endl << endl;

    cout << "----------- Testing Newton approximation ---------------------" << endl;
    newton_test();
    cout << "--------------------------------------------------------------" << endl << endl;
    return 0;
}

