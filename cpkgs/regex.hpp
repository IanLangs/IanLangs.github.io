#pragma once
#include <regex>
inline std::string sub(std::regex p, std::string repl, std::string s) {
    return std::regex_replace(s, p, repl);
}
inline std::string sub(std::string p, std::string repl, std::string s) {
    return std::regex_replace(s, std::regex(p.c_str()), repl);
}
inline std::vector<std::string> findall(const std::string& pattern, const std::string& text) {
    std::vector<std::string> matches;
    std::regex re(pattern);
    std::sregex_iterator begin(text.begin(), text.end(), re);
    std::sregex_iterator end;

    for (auto it = begin; it != end; ++it) {
        matches.push_back(it->str()); // Guarda la coincidencia completa
    }

    return matches;
}

std::vector<std::string> findall(const std::regex& re, const std::string& text) {
    std::vector<std::string> matches;
    std::sregex_iterator begin(text.begin(), text.end(), re);
    std::sregex_iterator end;

    for (auto it = begin; it != end; ++it) {
        matches.push_back(it->str()); // Guarda la coincidencia completa
    }

    return matches;
}
