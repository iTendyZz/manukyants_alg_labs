#pragma once  // Защита от повторного включения
#include <limits>
#include <string>
#include <iostream>

inline void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}