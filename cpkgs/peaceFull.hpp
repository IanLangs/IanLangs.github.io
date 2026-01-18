#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <regex>
#include <initializer_list>
#include <optional>

namespace peaceFull {

    // --- INPUT ---
    inline std::string input(const std::string& prompt="") {
        std::string s;
        if(!prompt.empty()) std::cout << prompt;
        std::getline(std::cin, s);
        return s;
    }

    // --- STR ---
    template<typename T>
    std::string str(const T& value) {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    // --- LEN ---
    template<typename T>
    size_t len(const T& container) { return container.size(); }

    // --- RANGE ---
    class range {
        int start_, end_, step_;
    public:
        class iterator {
            int value_;
            int step_;
        public:
            iterator(int value, int step) : value_(value), step_(step) {}
            int operator*() const { return value_; }
            iterator& operator++() { value_ += step_; return *this; }
            bool operator!=(const iterator& other) const { return step_>0 ? value_<*other : value_>*other; }
        };

        range(int end) : start_(0), end_(end), step_(1) {}
        range(int start, int end, int step=1) : start_(start), end_(end), step_(step) {}

        iterator begin() const { return iterator(start_, step_); }
        iterator end() const { return iterator(end_, step_); }
    };

    // --- LIST ---
    template<typename T>
    struct list {
        std::vector<T> data;

        list() = default;
        list(std::initializer_list<T> l) : data(l) {}
        list(const std::vector<T>& v) : data(v) {}

        T& operator[](size_t idx) { return data[idx]; }
        const T& operator[](size_t idx) const { return data[idx]; }

        size_t size() const { return data.size(); }

        void append(const T& value) { data.push_back(value); }

        list<T> slice(int start, int end, int step=1) const {
            list<T> result;
            if(step == 0) throw std::runtime_error("step cannot be 0");
            if(start < 0) start += data.size();
            if(end < 0) end += data.size();
            for(int i=start; (step>0)? i<end : i>end; i+=step)
                if(i>=0 && i<(int)data.size()) result.append(data[i]);
            return result;
        }

        list<T> operator+(const list<T>& other) const {
            list<T> result = *this;
            result.data.insert(result.data.end(), other.data.begin(), other.data.end());
            return result;
        }

        T sum() const {
            T s = T();
            for(auto& v : data) s += v;
            return s;
        }
    };

    // --- DICT ---
    template<typename K, typename V>
    struct dict {
        std::map<K,V> data;
        V& operator[](const K& key) { return data[key]; }
        bool contains(const K& key) const { return data.find(key) != data.end(); }
    };

    // --- ANY / ALL ---
    template<typename T, typename Func>
    bool any(const std::vector<T>& vec, Func f) {
        for(const auto& v : vec) if(f(v)) return true;
        return false;
    }

    template<typename T, typename Func>
    bool all(const std::vector<T>& vec, Func f) {
        for(const auto& v : vec) if(!f(v)) return false;
        return true;
    }

    // --- MIN / MAX ---
    template<typename T>
    T max(const std::vector<T>& vec) { return *std::max_element(vec.begin(), vec.end()); }

    template<typename T>
    T min(const std::vector<T>& vec) { return *std::min_element(vec.begin(), vec.end()); }

    // --- SORTED / REVERSED ---
    template<typename T>
    list<T> sorted(const std::vector<T>& vec, bool reverse=false) {
        list<T> result(vec.begin(), vec.end());
        std::sort(result.data.begin(), result.data.end());
        if(reverse) std::reverse(result.data.begin(), result.data.end());
        return result;
    }

    template<typename T>
    list<T> reversed(const std::vector<T>& vec) {
        list<T> result(vec.begin(), vec.end());
        std::reverse(result.data.begin(), result.data.end());
        return result;
    }

    // --- ZIP ---
    template<typename T1, typename T2>
    list<std::pair<T1,T2>> zip(const std::vector<T1>& a, const std::vector<T2>& b) {
        list<std::pair<T1,T2>> result;
        size_t n = std::min(a.size(), b.size());
        for(size_t i=0; i<n; ++i) result.append({a[i], b[i]});
        return result;
    }

    // --- MAP / FILTER ---
    template<typename T, typename Func>
    list<T> map(Func f, const std::vector<T>& vec) {
        list<T> result;
        for(auto& v : vec) result.append(f(v));
        return result;
    }

    template<typename T, typename Func>
    list<T> filter(Func f, const std::vector<T>& vec) {
        list<T> result;
        for(auto& v : vec) if(f(v)) result.append(v);
        return result;
    }

    // --- REGEX UTIL ---
    namespace regex {

        using Match = std::smatch;

        inline std::string sub(const std::string& pattern, const std::string& repl, const std::string& text) {
            return std::regex_replace(text, std::regex(pattern), repl);
        }

        inline std::optional<Match> M_match(const std::string& text, const std::string& pattern) {
            std::regex r(pattern);
            std::smatch m;
            if (std::regex_match(text, m, r)) return m;
            else return std::nullopt;
        }

        inline std::optional<Match> M_match(const std::string& text, const std::regex& pattern) {
            std::smatch m;
            if (std::regex_match(text, m, pattern)) return m;
            else return std::nullopt;
        }

        inline bool match(const std::string& text, const std::string& pattern) {
            return std::regex_match(text, std::regex(pattern));
        }

        inline bool match(const std::string& text, const std::regex& pattern) {
            return std::regex_match(text, pattern);
        }

        inline std::optional<Match> M_search(const std::string& pattern, const std::string& text) {
            std::regex r(pattern);
            std::smatch m;
            if (std::regex_search(text, m, r)) return m;
            else return std::nullopt;
        }

        inline std::optional<Match> M_search(const std::regex& pattern, const std::string& text) {
            std::smatch m;
            if (std::regex_search(text, m, pattern)) return m;
            else return std::nullopt;
        }

        inline bool search(const std::string& pattern, const std::string& text) {
            return std::regex_search(text, std::regex(pattern));
        }

        inline bool search(const std::regex& pattern, const std::string& text) {
            return std::regex_search(text, pattern);
        }

    } // namespace regex

} // namespace peaceFull
