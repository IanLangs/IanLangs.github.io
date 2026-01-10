#pragma once

#include <vector>
#include <map>
#include <string>
#include <ostream>
#include <functional>
#include <sstream>
#include <type_traits>
namespace type {
    using std::vector;
    using std::map;
    using str = std::string;
    using wstr = std::wstring;
    using std::function;

    using number = long double;
    using boolean = bool;
}
template<typename... Args>
type::str SepConcat(const type::str& sep, const Args&... args) {
    std::ostringstream oss;
    bool first = true;
    ((oss << (first ? "" : sep) << args, first = false), ...);
    return oss.str();
}

template<typename... Args>
type::str concat(const Args&... args) {
    return SepConcat("", args...);
}

template<typename T, typename U>
T get(const U& value) {
    if constexpr (std::is_same_v<T, type::str>) {
        if constexpr (std::is_same_v<U, str>)
            return value;
        else
            return std::to_string(value);
    } else {
        return static_cast<T>(value);
    }
}
