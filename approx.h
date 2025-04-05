#pragma once
#include <iostream>
#include <algorithm>
#include "interval.h"
#include <functional>

// Zadanie 2
// Reason for having it in the header file:
// If I want to export template functions it is advised to define them in the header file

template <class T>
_interval<T> natural_extension(const _interval<T>& x, _interval<T>(*func)(_interval<T>)) {
    return func(x);
}

template <class T>
_interval<T> mean_value(const _interval<T>& x, _interval<T>(*func)(_interval<T>), _interval<T>(*deriv)(_interval<T>)) {
    T center = x.center();
    _interval<T> result = deriv(x) * (x - center) + func(_interval<T>(center));
    return result;
}

template <class T>
_interval<T> slope(const _interval<T>& x, _interval<T>(*func)(_interval<T>)) {
    T r = x.center();
    _interval<T> denom = x - _interval<T>(r);

    // If denom contains 0 it will fail. Happens often so let's try taking something closer to the edge.
    if (denom.inf() <= 0 && denom.sup() >= 0) {
        r = 0.99 * x.inf();
        denom = x - _interval<T>(r);
        if (denom.inf() <= 0 && denom.sup() >= 0) {
            r = 0.99 * x.sup();
            denom = x - _interval<T>(r);
        }
    }
    _interval<T> num = func(x) - func(_interval<T>(r));
    _interval<T> slope_val = num / denom;
    return func(_interval<T>(r)) + slope_val * (x - _interval<T>(r));
}
template <class T>
_interval<T> bi_center(const _interval<T>& x, _interval<T>(*func)(_interval<T>), _interval<T>(*deriv)(_interval<T>)) {
    _interval<T> derivative = deriv(x);
    T lower = x.inf();
    T upper = x.sup();
    T deriv_min = derivative.inf();
    T deriv_max = derivative.sup();

    T c1, c2;
    if (deriv_min >= 0 || deriv_max <= 0) {
        c1 = upper;
        c2 = lower;
    } else {
        T denominator = deriv_max - deriv_min;
        c1 = (deriv_max * lower - deriv_min * upper) / denominator;
        c2 = -(deriv_min * lower - deriv_max * upper) / denominator;
    }

    _interval<T> form1 = derivative * (x - c1) + func(_interval<T>(c1));
    _interval<T> form2 = derivative * (x - c2) + func(_interval<T>(c2));

    T new_lower = std::max(form1.inf(), form2.inf());
    T new_upper = std::min(form1.sup(), form2.sup());

    return _interval<T>(new_lower, new_upper);
}

template <class T>
_interval<T> taylor(const _interval<T>& x, _interval<T>(*func)(_interval<T>), _interval<T>(*deriv)(_interval<T>)) {
    T center = x.center();
    _interval<T> result = deriv(_interval<T>(center)) * (x - center) + func(_interval<T>(center));
    return result;
}
