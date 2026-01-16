#pragma once

#include <vector>
#include <map>
#include <string>
#include <ostream>
#include <functional>
#include <sstream>
#include <type_traits>
#include <optional>
#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
#include <array>

namespace backend {

    // ================= SIGN =================

    class Sign {
        bool positive = true;

    public:
        Sign() = default;
        Sign(bool v) : positive(v) {}
        Sign(long double v) : positive(v >= 0) {}

        int get() const { return positive ? 1 : -1; }
        bool is_positive() const { return positive; }
        bool is_negative() const { return !positive; }

        template <typename T>
        auto operator*(T other) const {
            return get() * other;
        }
    };

    // ================= MEB STRUCT =================

    struct MEB {
        long double mantissa; // ∈ [1, 2)
        int exponent;
        int base;
    };

    // ================= EXTRACTION =================

    inline MEB get_MEB(long double v) {
        int exp;
        long double m = std::frexp(std::fabs(v), &exp);
        // frexp da mantissa en [0.5, 1), la pasamos a [1, 2)
        m *= 2;
        exp -= 1;

        return { m, exp, 2 };
    }

    // ================= BIG INT =================

    template <unsigned Bits>
    using intN = boost::multiprecision::number<
        boost::multiprecision::cpp_int_backend<
            Bits, Bits,
            boost::multiprecision::signed_magnitude,
            boost::multiprecision::unchecked,
            void
        >
    >;

}

namespace type {
    template <unsigned long MB, unsigned long EB, bool S>
    class number {
    private:
        long double mantissa;   // por ahora real
        backend::intN<EB> exponent;
        backend::Sign sign;

    public:
        number(long double v) : sign(v) {
            auto meb = backend::get_MEB(v);
            mantissa = meb.mantissa;
            exponent = meb.exponent;
        }
    };


    using std::vector;
    using std::map;
    using str = std::string;
    using wstr = std::wstring;
    using std::function;

    using boolean = bool;
    using void_t = void;

    using std::optional;

    template <typename T>
    using ptr = T*;
}
