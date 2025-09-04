#include "calculator.h"
#include <iostream>
#include <stdexcept>

Calculator::Calculator() {
    std::cout << "Calculator initialized" << std::endl;
}

Calculator::~Calculator() {
    std::cout << "Calculator destroyed" << std::endl;
}

int Calculator::add(int a, int b) {
    return a + b;
}

int Calculator::subtract(int a, int b) {
    return a - b;
}

int Calculator::multiply(int a, int b) {
    return a * b;
}

double Calculator::divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero!");
    }
    return static_cast<double>(a) / b;
}

void Calculator::printWelcome() {
    std::cout << "==================================" << std::endl;
    std::cout << "  Welcome to Cross-Platform Calc" << std::endl;
    std::cout << "==================================" << std::endl;
}