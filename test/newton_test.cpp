#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <iomanip>
#include "../interval.h"
#include "../newton.h"

using namespace std;
using namespace std::chrono;

// Zadanie 5

// ---------- Polynomial Definitions ----------
// Poly3: (x-1)(x-2)(x-3) = x^3 - 6x^2 + 11x - 6
_interval<double> poly3(const _interval<double> x) {
    return (x - _interval<double>(1)) *
           (x - _interval<double>(2)) *
           (x - _interval<double>(3));
}
_interval<double> dpoly3(const _interval<double> x) {
    // Precomputed derivative: 3x^2 - 12x + 11
    return _interval<double>(3) * power(x, 2) - _interval<double>(12) * x + _interval<double>(11);
}

// Poly4: (x-1)(x-2)(x-3)(x-4) = x^4 - 10x^3 + 35x^2 - 50x + 24
_interval<double> poly4(const _interval<double> x) {
    return (x - _interval<double>(1)) *
           (x - _interval<double>(2)) *
           (x - _interval<double>(3)) *
           (x - _interval<double>(4));
}
_interval<double> dpoly4(const _interval<double> x) {
    // Derivative: 4x^3 - 30x^2 + 70x - 50
    return _interval<double>(4) * power(x, 3) - _interval<double>(30) * power(x, 2)
           + _interval<double>(70) * x - _interval<double>(50);
}

// Poly5: (x-1)(x-2)(x-3)(x-4)(x-5)
// = x^5 -15x^4+85x^3-225x^2+274x-120
_interval<double> poly5(const _interval<double> x) {
    return (x - _interval<double>(1)) *
           (x - _interval<double>(2)) *
           (x - _interval<double>(3)) *
           (x - _interval<double>(4)) *
           (x - _interval<double>(5));
}
_interval<double> dpoly5(const _interval<double> x) {
    // Derivative: 5x^4 - 60x^3 + 255x^2 - 450x + 274
    return _interval<double>(5) * power(x, 4) - _interval<double>(60) * power(x, 3)
           + _interval<double>(255) * power(x, 2) - _interval<double>(450) * x + _interval<double>(274);
}

// Poly6: (x-1)(x-2)(x-3)(x-4)(x-5)(x-6)
// = x^6 -21x^5+175x^4-735x^3+1624x^2-1764x+720
_interval<double> poly6(const _interval<double> x) {
    return (x - _interval<double>(1)) *
           (x - _interval<double>(2)) *
           (x - _interval<double>(3)) *
           (x - _interval<double>(4)) *
           (x - _interval<double>(5)) *
           (x - _interval<double>(6));
}
_interval<double> dpoly6(const _interval<double> x) {
    // Derivative: 6x^5 -105x^4+700x^3-2205x^2+3248x-1764
    return _interval<double>(6) * power(x, 5) - _interval<double>(105) * power(x, 4)
           + _interval<double>(700) * power(x, 3) - _interval<double>(2205) * power(x, 2)
           + _interval<double>(3248) * x - _interval<double>(1764);
}

// Poly7: (x-1)(x-2)...(x-7)
// = x^7 -28x^6+322x^5 -1960x^4+6769x^3 -13132x^2+13068x-5040
_interval<double> poly7(const _interval<double> x) {
    return (x - _interval<double>(1)) *
           (x - _interval<double>(2)) *
           (x - _interval<double>(3)) *
           (x - _interval<double>(4)) *
           (x - _interval<double>(5)) *
           (x - _interval<double>(6)) *
           (x - _interval<double>(7));
}
_interval<double> dpoly7(const _interval<double> x) {
    // Derivative: 7x^6 -168x^5+1610x^4 -7840x^3+20307x^2-26264x+13068
    return _interval<double>(7) * power(x, 6) - _interval<double>(168) * power(x, 5)
           + _interval<double>(1610) * power(x, 4) - _interval<double>(7840) * power(x, 3)
           + _interval<double>(20307) * power(x, 2) - _interval<double>(26264) * x
           + _interval<double>(13068);
}

// ---------- Non-Polynomial Function ----------
// Nonpoly: sqrt(x) - 1, with a unique root at x = 1.
_interval<double> nonpoly(const _interval<double> x) {
    return sqrt_interval(x) - _interval<double>(1.0);
}
_interval<double> dnonpoly(const _interval<double> x) {
    return _interval<double>(1.0) / (_interval<double>(2.0) * sqrt_interval(x));
}

// ---------- Test Driver ----------
void run_newton_test(const string& label, const _interval<double>& range,
                     _interval<double> (*f)(_interval<double>),
                     _interval<double> (*df)(_interval<double>))
{
    cout << "Function: " << label << ", Interval: " << range << "\n";
    auto run_method = [&](const string& methodName, auto newton_method) {
        auto start = high_resolution_clock::now();
        vector<_interval<double>> roots = newton_method(range, f, df, 1e-2, 100000, 1e-6);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count();

        cout << "  " << setw(15) << left << methodName << ": ";
        if (!roots.empty()) {
            for (const auto& r : roots) {
                cout << r << " ";
            }
        } else {
            cout << "No root found";
        }
        cout << " | Time: " << duration << " µs" << endl;
    };

    try { run_method("Natural ext.", interval_newton_all_natural_extension<double>); }
    catch (const exception& e) { cout << "  Natural ext.: Error - " << e.what() << "\n"; }

    try { run_method("Mean value", interval_newton_all_mean_value<double>); }
    catch (const exception& e) { cout << "  Mean value   : Error - " << e.what() << "\n"; }

    try { run_method("Slope", interval_newton_all_slope<double>); }
    catch (const exception& e) { cout << "  Slope        : Error - " << e.what() << "\n"; }

    try { run_method("Taylor", interval_newton_all_taylor<double>); }
    catch (const exception& e) { cout << "  Taylor       : Error - " << e.what() << "\n"; }

    try { run_method("Bi-Center", interval_newton_all_bi_center<double>); }
    catch (const exception& e) { cout << "  Bi-Center    : Error - " << e.what() << "\n"; }

    cout << "\n";
}

int newton_test() {
    cout << "Interval Newton Method Test\n";
    cout << "---------------------------\n\n";

    // For poly3 with roots 1,2,3 use narrow intervals around each root.
    run_newton_test("Poly3 root at 1", _interval<double>(0, 10), poly3, dpoly3);

    // For poly4 with roots 1,2,3,4.
    run_newton_test("Poly4 root at 1", _interval<double>(0, 10), poly4, dpoly4);

    // For poly5 with roots 1,2,3,4,5.
    run_newton_test("Poly5 root at 1", _interval<double>(0, 10), poly5, dpoly5);

    // For poly6 with roots 1,2,3,4,5,6.
    run_newton_test("Poly6 root at 1", _interval<double>(0, 10), poly6, dpoly6);

    // For poly7 with roots 1,...,7.
    run_newton_test("Poly7 root at 1", _interval<double>(0, 10), poly7, dpoly7);

    // For the nonpolynomial function (sqrt(x)-1) with its unique root at 1.
    run_newton_test("NonPoly root at 1", _interval<double>(0.6, 1.7), nonpoly, dnonpoly);

    return 0;
}
