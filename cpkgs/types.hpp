#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include <variant>
#include <complex>
#include <bitset>
#include <array>
#include <cstdint>
#include <type_traits>
#include <memory>
#include <tuple>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
namespace types {
    using str = std::string;

    template<typename T>
    using list = std::vector<T>;

    template<typename K, typename V>
    using dict = std::unordered_map<K, V>;

    template<typename T>
    using optional = std::optional<T>;

    template<typename... Ts>
    using union_t = std::variant<Ts...>;

    template<typename T>
    using complex = std::complex<T>;

    template<unsigned Bits>
    using int_s = boost::multiprecision::number<
        boost::multiprecision::cpp_int_backend<
            Bits, Bits,
            boost::multiprecision::signed_magnitude,
            boost::multiprecision::unchecked,
            void
        >
    >;

    template<unsigned Bits>
    using int_u = boost::multiprecision::number<
        boost::multiprecision::cpp_int_backend<
            Bits, Bits,
            boost::multiprecision::unsigned_magnitude,
            boost::multiprecision::unchecked,
            void
        >
    >;

    template<unsigned Bits>
    using int_t = int_s<Bits>;

    template<unsigned Bits>
    using uint_t = int_u<Bits>;

    template<unsigned MantissaBits>
    using float_bin = boost::multiprecision::cpp_bin_float<MantissaBits>;

    template<unsigned Digits>
    using float_dec = boost::multiprecision::cpp_dec_float<Digits>;

    template<unsigned N>
    using float_t = float_bin<N>;   

    template<unsigned N>
    using float_td = float_dec<N>;  

    using bit  = uint_t<1>;
    using byte = std::uint8_t;

    template<size_t N>
    using bytes = std::array(byte, N);

    template<size_t N>
    using bits = std::bitset;

    using u8char  = bytes<1>;   
    using u16char = bytes<2>;   
    using u32char = bytes<4>;   

    using i8  = int_t<8>;
    using i16 = int_t<16>;
    using i32 = int_t<32>;
    using i64 = int_t<64>;

    using u8  = uint_t<8>;
    using u16 = uint_t<16>;
    using u32 = uint_t<32>;
    using u64 = uint_t<64>;

    using f16  = float_t<16>;
    using f32  = float_t<32>;
    using f64  = float_t<64>;
    using f128 = float_t<128>;
  
    using usize = std::size_t;
    using isize = std::make_signed_t<std::size_t>;

    template<typename T>
    using shared_ptr = std::shared_ptr<T>;

    template<typename T>
    using unique_ptr = std::unique_ptr<T>;

    template<typename T>
    using weak_ptr = std::weak_ptr<T>;

    template<typename... Ts>
    using tuple = std::tuple<Ts...>;

    template<typename T1, typename T2>
    using pair = std::pair<T1, T2>;

    using KiB = bytes<1024>;
    using MiB = bytes<1048576>;
    inline constexpr byte BYTE_MAX = 0xFF;
    inline constexpr bit  BIT_TRUE = true;
    inline constexpr bit  BIT_FALSE = false;
} 