#include "../approx.h"
#include "../interval.h"
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
// Zadanie 4

_interval<double> function1(_interval<double> x) {
    return (power(x, 2) + 2.0).inverse();
}

_interval<double> derivative1(_interval<double> x) {
    return _interval<double>(-2) * x / power((power(x, 2) + 2.0), 2);
}

_interval<double> function2(_interval<double> x) {
    return power(x, 2) - _interval<double>(2.0) * x + _interval<double>(1.0);
}

_interval<double> derivative2(_interval<double> x) {
    return _interval<double>(2.0) * x - _interval<double>(2.0);
}

_interval<double> function3(_interval<double> x) {
    return (_interval<double>(-5.0) * x) + (power(x, 3) / _interval<double>(3.0)) + _interval<double>(1.0);
}

_interval<double> derivative3(_interval<double> x) {
    return power(x, 2) - _interval<double>(5.0);
}

_interval<double> function4(_interval<double> x) {
    return x + _interval<double>(exp(x.inf()), exp(x.sup()));
}

_interval<double> derivative4(_interval<double> x) {
    return _interval<double>(1.0) + _interval<double>(exp(x.inf()), exp(x.sup()));
}

void run_all_methods(const string& label, _interval<double> x, _interval<double>(*f)(_interval<double>), _interval<double>(*df)(_interval<double>)) {
    cout << "Function: " << label << ", Interval: " << x << endl;
    try {
        cout << "  Natural extension: " << natural_extension(x, f) << endl;
    } catch (const std::exception& e) {
        cout << "  Natural extension: Error - " << e.what() << endl;
    }
    try {
        cout << "  Mean value:        " << mean_value(x, f, df) << endl;
    } catch (const std::exception& e) {
        cout << "  Mean value:        Error - " << e.what() << endl;
    }
    try {
        cout << "  Slope:             " << slope(x, f) << endl;
    } catch (const std::exception& e) {
        cout << "  Slope:             Error - " << e.what() << endl;
    }
    try {
        cout << "  Taylor:            " << taylor(x, f, df) << endl;
    } catch (const std::exception& e) {
        cout << "  Taylor:            Error - " << e.what() << endl;
    }
    try {
        cout << "  Bi-Center:         " << bi_center(x, f, df) << endl;
    } catch (const std::exception& e) {
        cout << "  Bi-Center:         Error - " << e.what() << endl;
    }
    cout << endl;
}


void approx_test_function1() {
    _interval<double> range(-2.0, 2.0);
    run_all_methods("1 / (x^2 + 2)", range, function1, derivative1);
}

void approx_test_function2() {
    _interval<double> range(0.0, 1.0);
    run_all_methods("x^2 - 2x + 1", range, function2, derivative2);
}

void approx_test_function3() {
    _interval<double> range(0.5, 2.5);
    run_all_methods("1 - 5x + (1/3)x^3", range, function3, derivative3);
}

void approx_test_function4() {
    _interval<double> range(1.0, 3.0);
    run_all_methods("x + e^x", range, function4, derivative4);
}
