#pragma once
#include <algorithm>
#include <vector>
#include <list>
#include <functional>
#include "interval.h"
#include "approx.h"

// ---------------------------------------------------------------------
// Generic Newton method using an approximation function (approxF)
// ---------------------------------------------------------------------
template <class T, class F>
std::vector<_interval<T>> interval_newton_all_approx(
    const _interval<T> x,
    F approxF,
    _interval<T> (*deriv)(const _interval<T>),
    T tol = 1e-2,
    int max_iter = 1000,
    T stale_bound = 1e-6)
{
    std::vector<_interval<T>> result;
    std::list<_interval<T>> L;
    L.push_back(x);
    int iter = 0;

    while (!L.empty()) {
        iter++;
        _interval<T> current = L.front();
        L.pop_front();

        T x_center = current.center();
        _interval<T> c(x_center);

        _interval<T> f_current = approxF(current);
        _interval<T> f_c = approxF(c);
        _interval<T> derivative = deriv(current);
        if (derivative.inf() <= 0 && derivative.sup() >= 0) {
            // This case will error when dividing by derivative.
            // Happens often with polynomials. I just split it to try to get some answers.
            if (iter + 2 <= max_iter) {
                T mid = current.center();
                _interval<T> left(current.inf(), mid);
                _interval<T> right(mid, current.sup());
                L.push_back(left);
                L.push_back(right);
            }
            continue;
        }

        _interval<T> newton_candidate = c - f_c / derivative;

        // Contract the interval: intersection of current and newton_candidate
        T new_inf = std::max(current.inf(), newton_candidate.inf());
        T new_sup = std::min(current.sup(), newton_candidate.sup());
        if (new_inf > new_sup) {
            // Empty intersection: no zero in this interval.
            continue;
        }
        _interval<T> contracted(new_inf, new_sup);

        // Check termination conditions:
        if (iter + L.size() > max_iter || // Check on not exceding max iterations
            ((current.sup() - current.inf()) - (contracted.sup() - contracted.inf()) < stale_bound) ||
            ((contracted.sup() - contracted.inf()) < tol))
        {
            result.push_back(contracted);
        } else {
            // Otherwise, subdivide the interval and continue.
            T mid = current.center();
            _interval<T> left(current.inf(), mid);
            _interval<T> right(mid, current.sup());
            L.push_back(left);
            L.push_back(right);
        }
    }
    return result;
}

// ---------------------------------------------------------------------
// Wrappers for approximation functions
// ---------------------------------------------------------------------

template <class T>
std::vector<_interval<T>> interval_newton_all_natural_extension(
    const _interval<T> x,
    _interval<T> (*func)(const _interval<T>),
    _interval<T> (*deriv)(const _interval<T>),
    T tol = 1e-2,
    int max_iter = 1000,
    T stale_bound = 1e-6)
{
    auto approx = [=](const _interval<T> interval) -> _interval<T> {
        return natural_extension(interval, func);
    };
    return interval_newton_all_approx(x, approx, deriv, tol, max_iter, stale_bound);
}

template <class T>
std::vector<_interval<T>> interval_newton_all_mean_value(
    const _interval<T> x,
    _interval<T> (*func)(const _interval<T>),
    _interval<T> (*deriv)(const _interval<T>),
    T tol = 1e-2,
    int max_iter = 1000,
    T stale_bound = 1e-6)
{
    auto approx = [=](const _interval<T> interval) -> _interval<T> {
        return mean_value(interval, func, deriv);
    };
    return interval_newton_all_approx(x, approx, deriv, tol, max_iter, stale_bound);
}

template <class T>
std::vector<_interval<T>> interval_newton_all_slope(
    const _interval<T> x,
    _interval<T> (*func)(const _interval<T>),
    _interval<T> (*deriv)(const _interval<T>),
    T tol = 1e-2,
    int max_iter = 1000,
    T stale_bound = 1e-6)
{
    auto approx = [=](const _interval<T> interval) -> _interval<T> {
        return slope(interval, func);
    };
    return interval_newton_all_approx(x, approx, deriv, tol, max_iter, stale_bound);
}

template <class T>
std::vector<_interval<T>> interval_newton_all_bi_center(
    const _interval<T> x,
    _interval<T> (*func)(const _interval<T>),
    _interval<T> (*deriv)(const _interval<T>),
    T tol = 1e-2,
    int max_iter = 1000,
    T stale_bound = 1e-6)
{
    auto approx = [=](const _interval<T> interval) -> _interval<T> {
        return bi_center(interval, func, deriv);
    };
    return interval_newton_all_approx(x, approx, deriv, tol, max_iter, stale_bound);
}

template <class T>
std::vector<_interval<T>> interval_newton_all_taylor(
    const _interval<T> x,
    _interval<T> (*func)(const _interval<T>),
    _interval<T> (*deriv)(const _interval<T>),
    T tol = 1e-2,
    int max_iter = 1000,
    T stale_bound = 1e-6)
{
    auto approx = [=](const _interval<T> interval) -> _interval<T> {
        return taylor(interval, func, deriv);
    };
    return interval_newton_all_approx(x, approx, deriv, tol, max_iter, stale_bound);
}
