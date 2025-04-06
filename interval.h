#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

using namespace std;

// Zadanie 1
// Klasa przedziału
template <class T>
class _interval {
    T _inf, _sup;
public:
    _interval() : _inf(0), _sup(0) {}

    explicit _interval(T a) : _inf(a), _sup(a) {}

    _interval(T a, T b) {
        if (b < a) {
            throw invalid_argument("Blad: b < a");
        }
        _inf = a;
        _sup = b;
    }
    _interval(const _interval<T>& other) : _inf(other._inf), _sup(other._sup) {}
    ~_interval() = default;

    T inf() const { return _inf; }
    T sup() const { return _sup; }
    T center() const { return (_inf + _sup) / 2; }

    bool includes(T value) const {
        return value >= _inf && value <= _sup;
    }
    _interval<T> inverse() const {
        if (includes(0)) {
            throw invalid_argument("Nie mozna obliczyc odwrotnosci z przedzialu zawierajacego 0");
        }
        return _interval<T>(1 / _sup, 1 / _inf);
    }
};

// Dodawanie i odejmowanie
template <class T>
_interval<T> operator+(const _interval<T>& x, const _interval<T>& y) {
    return _interval<T>(x.inf() + y.inf(), x.sup() + y.sup());
}
template<class T>
_interval<T> operator + (const _interval<T>& x, const T& y) {
    return _interval<T>(x.inf() + y, x.sup() + y);
}
template <class T>
_interval<T> operator-(const _interval<T>& x, const _interval<T>& y) {
    return _interval<T>(x.inf() - y.sup(), x.sup() - y.inf());
}
template<class T>
_interval<T> operator - (const _interval<T>& x, const T& y) {
    return _interval<T>(x.inf() - y, x.sup() - y);
}

// Mnożenie, potęgowanie i pierwiastki kwadratowe
template <class T>
_interval<T> operator*(const _interval<T>& x, const _interval<T>& y) {
    T t1 = x.inf() * y.inf();
    T t2 = x.inf() * y.sup();
    T t3 = x.sup() * y.inf();
    T t4 = x.sup() * y.sup();
    T new_inf = min({ t1, t2, t3, t4 });
    T new_sup = max({ t1, t2, t3, t4 });
    return _interval<T>(new_inf, new_sup);
}
template <class T>
_interval<T> operator/(const _interval<T>& x, const _interval<T>& y) {
    _interval<T> invY = y.inverse();
    return x * invY;
}
template <class T>
_interval<T> power(const _interval<T>& x, int n) {
    if (n < 0) {
        throw std::invalid_argument("Negative exponent not supported");
    }
    if (n == 0) {
        return _interval<T>(1, 1);
    }

    T a_pow = std::pow(x.inf(), n);
    T b_pow = std::pow(x.sup(), n);

    if (n % 2 == 1) {
        return _interval<T>(a_pow, b_pow);
    }

    if (x.inf() <= 0 && x.sup() >= 0) {
        return _interval<T>(0, std::max(a_pow, b_pow));
    }
    return _interval<T>(std::min(a_pow, b_pow), std::max(a_pow, b_pow));
}

template <class T>
_interval<T> sqrt_interval(const _interval<T>& x) {
    T a = x.inf();
    T b = x.sup();
    if (a < 0) {
        throw invalid_argument("Cannot compute square root of interval with negative lower bound");
    }

    return _interval<T>(std::sqrt(a), std::sqrt(b));
}

// COUT
template <class T>
std::ostream& operator<<(std::ostream& os, const _interval<T>& x) {
    os << "[" << x.inf() << ", " << x.sup() << "]";
    return os;
}
