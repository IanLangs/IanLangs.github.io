export module types;

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
#include <any>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

export namespace types {

    export using str = std::string;

    export template<typename T>
    using list = std::vector<T>;

    export template<typename K, typename V>
    using dict = std::unordered_map<K, V>;

    export template<typename T>
    using optional = std::optional<T>;

    export std::nullopt_t None = std::nullopt;

    export template<typename... Ts>
    using union_t = std::variant<Ts...>;

    export template<typename T>
    using complex = std::complex<T>;

    export template<unsigned Bits>
    using int_s = boost::multiprecision::number<
        boost::multiprecision::cpp_int_backend<
            Bits, Bits,
            boost::multiprecision::signed_magnitude,
            boost::multiprecision::unchecked,
            void
        >
    >;

    export template<unsigned Bits>
    using int_u = boost::multiprecision::number<
        boost::multiprecision::cpp_int_backend<
            Bits, Bits,
            boost::multiprecision::unsigned_magnitude,
            boost::multiprecision::unchecked,
            void
        >
    >;

    export template<unsigned Bits>
    using int_t = int_s<Bits>;

    export template<unsigned Bits>
    using uint_t = int_u<Bits>;

    export template<unsigned MantissaBits>
    using float_bin = boost::multiprecision::cpp_bin_float<MantissaBits>;

    export template<unsigned Digits>
    using float_dec = boost::multiprecision::cpp_dec_float<Digits>;

    export template<unsigned N>
    using float_t = float_bin<N>;   

    export template<unsigned N>
    using float_td = float_dec<N>;  

    export using bit  = uint_t<1>;
    export using byte = std::uint8_t;

    export template<size_t N>
    using bytes = std::array<byte, N>;

    export template<size_t N>
    using bits = std::bitset<N>;

    export using u8char  = bytes<1>;   
    export using u16char = bytes<2>;   
    export using u32char = bytes<4>;   

    export using i8  = int_t<8>;
    export using i16 = int_t<16>;
    export using i32 = int_t<32>;
    export using i64 = int_t<64>;

    export using u8  = uint_t<8>;
    export using u16 = uint_t<16>;
    export using u32 = uint_t<32>;
    export using u64 = uint_t<64>;

    export using f16  = float_t<16>;
    export using f32  = float_t<32>;
    export using f64  = float_t<64>;
    export using f128 = float_t<128>;
  
    export using usize = std::size_t;
    export using isize = std::make_signed_t<std::size_t>;

    export template<typename T>
    using shared_ptr = std::shared_ptr<T>;

    export template<typename T>
    using unique_ptr = std::unique_ptr<T>;

    export template<typename T>
    using weak_ptr = std::weak_ptr<T>;

    export template<typename T>
    using type_ptr = T*; 

    export using any_t = std::any;

    export template<typename T>
    T get(any_t obj) {
        return std::any_cast<T>(obj);
    }

    export template<typename T, typename... Ts>
    T get(const union_t<Ts...>& obj) {
        return std::get<T>(obj);
    }

    export template<typename... Ts>
    using tuple = std::tuple<Ts...>;

    export template<typename T1, typename T2>
    using pair = std::pair<T1, T2>;

    export using KiB = bytes<1024>;
    export using MiB = bytes<1048576>;
    export constexpr byte BYTE_MAX = 0xFF;
    export constexpr bit  BIT_TRUE = true;
    export constexpr bit  BIT_FALSE = false;
}
