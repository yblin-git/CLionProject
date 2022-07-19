#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    int32_t value  = 100;
    uint8_t value1  = 100;
    std::cout << "Hello, World!" <<(sizeof(&value) / sizeof(uint8_t)) <<std::endl;
    std::cout << "Hello, World!" <<(sizeof(value1) / sizeof(uint8_t)) <<std::endl;

    return 0;
}
