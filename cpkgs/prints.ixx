export module prints;

#include <iostream>
#include <string>
#include <vector>

export namespace prints {

    export enum class Color {
        DEFAULT, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
    };

    inline std::string colorCode(Color c) {
        switch(c) {
            case Color::RED: return "\033[31m";
            case Color::GREEN: return "\033[32m";
            case Color::YELLOW: return "\033[33m";
            case Color::BLUE: return "\033[34m";
            case Color::MAGENTA: return "\033[35m";
            case Color::CYAN: return "\033[36m";
            case Color::WHITE: return "\033[37m";
            default: return "\033[0m";
        }
    }

    export inline void print() { std::cout << "\n"; }

    export template<typename T>
    void print(const T& value, const std::string& sep = " ", const std::string& end = "\n") {
        std::cout << value << end;
    }

    export template<typename T, typename... Args>
    void print(const T& first, const Args&... args, const std::string& sep = " ", const std::string& end = "\n") {
        std::cout << first;
        ((std::cout << sep << args), ...);
        std::cout << end;
    }

    export template<Color C, typename... Args>
    void printc(const Args&... args, const std::string& sep = " ", const std::string& end = "\n") {
        std::cout << colorCode(C);
        print(args..., sep, end);
        std::cout << colorCode(Color::DEFAULT);
    }

    // Mejor no exportar operador<< directo para std::vector
    template<typename T>
    std::ostream& vec_to_stream(std::ostream& os, const std::vector<T>& vec) {
        os << "[";
        for(size_t i = 0; i < vec.size(); ++i) {
            os << vec[i];
            if(i != vec.size()-1) os << ", ";
        }
        os << "]";
        return os;
    }

}
