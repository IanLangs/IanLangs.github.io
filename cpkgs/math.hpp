#pragma once
#include <cmath>
#include <limits>
#include <vector>
#include <string>
#include <numeric>
#include <stdexcept>
#include <cctype>

namespace math {

    // ------------------------------
    // CONSTANTES Y UTILIDADES
    // ------------------------------
    inline constexpr long double PI      = 3.141592653589793238462643383279502884L;
    inline constexpr long double E       = 2.718281828459045235360287471352662498L;
    inline constexpr long double INF     = std::numeric_limits<long double>::infinity();
    inline constexpr long double NAN_VAL = std::numeric_limits<long double>::quiet_NaN();

    inline long double abs(long double x) { return (x < 0) ? -x : x; }

    template<typename T>
    inline T max(const T& a, const T& b) { return (a > b) ? a : b; }

    template<typename T>
    inline T min(const T& a, const T& b) { return (a < b) ? a : b; }

    // ------------------------------
    // TRIGONOMETRÍA Y LOGARITMOS
    // ------------------------------
    inline constexpr long double deg2rad(long double deg) { return deg * PI / 180.0L; }
    inline constexpr long double rad2deg(long double rad) { return rad * 180.0L / PI; }

    inline long double sin(long double x) { return std::sin(x); }
    inline long double cos(long double x) { return std::cos(x); }
    inline long double tan(long double x) { return std::tan(x); }
    inline long double asin(long double x) { return std::asin(x); }
    inline long double acos(long double x) { return std::acos(x); }
    inline long double atan(long double x) { return std::atan(x); }
    inline long double atan2(long double y, long double x) { return std::atan2(y, x); }

    inline long double exp(long double x) { return std::exp(x); }
    inline long double ln(long double x) { return std::log(x); }
    inline long double log10(long double x) { return std::log10(x); }
    inline long double log_base(long double x, long double base) { return std::log(x)/std::log(base); }

    inline long double sqrt(long double x) { return std::sqrt(x); }
    inline long double cbrt(long double x) { return std::cbrt(x); }
    inline long double pow(long double base, long double exp) { return std::pow(base, exp); }

    inline long double floor(long double x) { return std::floor(x); }
    inline long double ceil(long double x) { return std::ceil(x); }
    inline long double round(long double x) { return std::round(x); }
    inline long double trunc(long double x) { return std::trunc(x); }

    // ------------------------------
    // ESTADÍSTICA
    // ------------------------------
    template<typename T>
    inline T sum(const std::vector<T>& v) { return std::accumulate(v.begin(), v.end(), T(0)); }

    template<typename T>
    inline long double mean(const std::vector<T>& v) {
        if(v.empty()) throw std::domain_error("mean: vector vacío");
        return static_cast<long double>(sum(v)) / v.size();
    }

    template<typename T>
    inline long double variance(const std::vector<T>& v) {
        long double m = mean(v);
        long double s = 0;
        for(auto val : v) s += (val - m)*(val - m);
        return s / v.size();
    }

    template<typename T>
    inline long double stdev(const std::vector<T>& v) { return sqrt(variance(v)); }

    // ------------------------------
    // MATRICES
    // ------------------------------
    template<typename T>
    using matrix = std::vector<std::vector<T>>;

    template<typename T>
    matrix<T> zeros(size_t rows, size_t cols) { return matrix<T>(rows, std::vector<T>(cols, T(0))); }

    template<typename T>
    matrix<T> identity(size_t n) {
        matrix<T> I = zeros<T>(n,n);
        for(size_t i=0;i<n;i++) I[i][i]=1;
        return I;
    }

    template<typename T>
    matrix<T> matmul(const matrix<T>& A, const matrix<T>& B) {
        if(A[0].size() != B.size()) throw std::domain_error("matmul: dimensiones incompatibles");
        size_t n = A.size(), m = B[0].size(), p = B.size();
        matrix<T> C = zeros<T>(n,m);
        for(size_t i=0;i<n;i++)
            for(size_t j=0;j<m;j++)
                for(size_t k=0;k<p;k++)
                    C[i][j] += A[i][k]*B[k][j];
        return C;
    }

    // ------------------------------
    // COMBINATORIA
    // ------------------------------
    inline long double factorial(int n) {
        if(n<0) throw std::domain_error("factorial: n negativo");
        long double f = 1;
        for(int i=2;i<=n;i++) f*=i;
        return f;
    }

    inline long double nCr(int n, int r) {
        if(r<0 || n<0 || r>n) throw std::domain_error("nCr: valores inválidos");
        return factorial(n)/(factorial(r)*factorial(n-r));
    }

    // ------------------------------
    // CONVERSION DE BASES
    // ------------------------------
    inline std::string to_base(long double n, int base, int precision=12) {
        if(base < 2 || base > 36) throw std::domain_error("to_base: base inválida");
        std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string res;
        bool neg = n < 0;
        if(neg) n = -n;

        long long int_part = static_cast<long long>(n);
        long double frac_part = n - int_part;

        std::string int_str;
        do { int_str = chars[int_part % base] + int_str; int_part /= base; } while(int_part > 0);

        std::string frac_str;
        int count = 0;
        while(frac_part > 0 && count < precision) {
            frac_part *= base;
            int digit = static_cast<int>(frac_part);
            frac_str += chars[digit];
            frac_part -= digit;
            count++;
        }

        res = int_str;
        if(!frac_str.empty()) res += "." + frac_str;
        if(neg) res = "-" + res;
        return res;
    }

    inline long double from_base(const std::string& s, int base) {
        if(base < 2 || base > 36) throw std::domain_error("from_base: base inválida");
        std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        auto pos = s.find('.');
        std::string int_part_str = (pos == std::string::npos) ? s : s.substr(0, pos);
        std::string frac_part_str = (pos == std::string::npos) ? "" : s.substr(pos + 1);

        bool neg = false;
        size_t start = 0;
        if(!int_part_str.empty() && int_part_str[0] == '-') { neg = true; start = 1; }

        long double result = 0;
        for(size_t i = start; i < int_part_str.size(); i++) {
            char c = toupper(int_part_str[i]);
            size_t val = chars.find(c);
            if(val == std::string::npos || val >= (size_t)base) throw std::domain_error("from_base: caracter inválido");
            result = result * base + val;
        }

        long double base_inv = 1.0L / base;
        long double frac_multiplier = base_inv;
        for(char c : frac_part_str) {
            char ch = toupper(c);
            size_t val = chars.find(ch);
            if(val == std::string::npos || val >= (size_t)base) throw std::domain_error("from_base: caracter inválido");
            result += val * frac_multiplier;
            frac_multiplier *= base_inv;
        }

        if(neg) result = -result;
        return result;
    }

    // ------------------------------
    // FLECHAS DE KNUTH Y H
    // ------------------------------
    inline long double arrow(long double a, long double b, int n) {
        if(n<0) throw std::domain_error("arrow: n invalido");
        if(n==0) return a*b;
        if(n==1) return std::pow(a,b);
        if(b==0) return 1;
        long double result = a;
        for(long double i=1;i<b;i++)
            result = arrow(a,result,n-1);
        return result;
    }

    inline long double H(long double a, long double b, int n) {
        if(n==1) return a+b;
        if(n==2) return a*b;
        if(n>2) return arrow(a,b,n-2);
        throw std::domain_error("H: n invalido");
    }

    // ------------------------------
    // ACKERMANN (via flechas)
    // ------------------------------
    inline long double ackermann(long double m, long double n) {
        if(m<0 || n<0) throw std::domain_error("ackermann: m,n >=0");
        if(m==0) return n+1;
        if(m==1) return n+2;
        if(m==2) return 2*n + 3;
        if(m==3) return std::pow(2,n+3)-3;
        if(m>=4) return arrow(2,n+3,m-2)-3;
        return -1;
    }

    // ------------------------------
    // ESTRUCTURAS SIMPLES
    // ------------------------------
    struct tree_node { int value; std::vector<tree_node*> children; tree_node(int v): value(v) {} };
    struct sscg_node { int id; std::vector<int> neighbors; sscg_node(int i): id(i) {} };
    struct scg_node  { int id; std::vector<int> neighbors; scg_node(int i): id(i) {} };

}
