#include "../interval.h"
#include <cassert>
#include <iostream>
#include <cmath>
using namespace std;

int interval_test() {
    // Test default constructor
    _interval<double> i1;
    assert(i1.inf() == 0 && i1.sup() == 0);
    cout << "Default constructor test passed: " << i1 << endl;

    // Test single parameter constructor
    _interval<double> i2(5.0);
    assert(i2.inf() == 5.0 && i2.sup() == 5.0);
    cout << "Single parameter constructor test passed: " << i2 << endl;

    // Test two parameter constructor
    _interval<double> i3(2.0, 8.0);
    assert(i3.inf() == 2.0 && i3.sup() == 8.0);
    cout << "Two parameter constructor test passed: " << i3 << endl;

    // Test invalid two parameter constructor
    try {
        _interval<double> invalid(10, 5);
        assert(false);
    } catch (const invalid_argument& e) {
        cout << "Invalid constructor test passed: " << e.what() << endl;
    }

    // Test includes function
    assert(i3.includes(2.0));
    assert(i3.includes(8.0));
    assert(i3.includes(5.0));
    assert(!i3.includes(1.9));
    assert(!i3.includes(8.1));
    cout << "Includes function test passed" << endl;

    // Test center function
    double center = i3.center();
    assert(center == 5.0);
    cout << "Center function test passed: " << center << endl;

    // Test inverse function
    _interval<double> i4(2, 4);
    _interval<double> inv = i4.inverse();
    assert(fabs(inv.inf() - 0.25) < 1e-6 && fabs(inv.sup() - 0.5) < 1e-6);
    cout << "Inverse function test passed: " << inv << endl;

    // Test operator+ (interval + interval)
    _interval<double> i5 = i3 + i3;
    assert(i5.inf() == 4.0 && i5.sup() == 16.0);
    cout << "Operator+ (interval + interval) test passed: " << i5 << endl;

    // Test operator+ (interval + value)
    _interval<double> i6 = i3 + 2.0;
    assert(i6.inf() == 4.0 && i6.sup() == 10.0);
    cout << "Operator+ (interval + value) test passed: " << i6 << endl;

    // Test operator- (interval - interval)
    _interval<double> i7 = i3 - i2;
    assert(i7.inf() == -3.0 && i7.sup() == 3.0);
    cout << "Operator- (interval - interval) test passed: " << i7 << endl;

    // Test operator- (interval - value)
    _interval<double> i8 = i3 - 1.0;
    assert(i8.inf() == 1.0 && i8.sup() == 7.0);
    cout << "Operator- (interval - value) test passed: " << i8 << endl;

    // Test operator* (multiplication)
    _interval<double> i9 = i3 * _interval<double>(1.0, 3.0);
    assert(i9.inf() == 2.0 && i9.sup() == 24.0);
    cout << "Operator* test passed: " << i9 << endl;

    // Test operator/ (division)
    _interval<double> i10 = i3 / _interval<double>(1.0, 2.0);
    assert(i10.inf() == 1.0 && i10.sup() == 8.0);
    cout << "Operator/ test passed: " << i10 << endl;

    // Test power function for odd exponent
    _interval<double> i11 = power(i3, 3);
    assert(i11.inf() == 8.0 && i11.sup() == 512.0);
    cout << "Power function (odd exponent) test passed: " << i11 << endl;

    // Test power function for even exponent
    _interval<double> i12 = power(i3, 2);
    assert(i12.inf() == 4.0 && i12.sup() == 64.0);
    cout << "Power function (even exponent) test passed: " << i12 << endl;

    // Test sqrt_interval
    _interval<double> i13(4, 16);
    _interval<double> i14 = sqrt_interval(i13);
    assert(i14.inf() == 2.0 && i14.sup() == 4.0);
    cout << "Sqrt interval test passed: " << i14 << endl;

    // Test sqrt_interval with negative lower bound (should throw)
    try {
        _interval<double> i15(-4, 9);
        _interval<double> i16 = sqrt_interval(i15);
        assert(false);
    } catch (const invalid_argument& e) {
        cout << "Sqrt interval negative lower bound test passed: " << e.what() << endl;
    }

    cout << "All tests passed successfully." << endl;
    return 0;
}
