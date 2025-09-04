#include "calculator.h"
#include <iostream>
#include <string>

// 版本信息
#ifndef APP_VERSION
#define APP_VERSION "1.0.0"
#endif

void showMenu() {
    std::cout << "\nChoose an operation:" << std::endl;
    std::cout << "1. Addition" << std::endl;
    std::cout << "2. Subtraction" << std::endl;
    std::cout << "3. Multiplication" << std::endl;
    std::cout << "4. Division" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice (1-5): ";
}

int main() {
    Calculator calc;
    
    calc.printWelcome();
    std::cout << "Version: " << APP_VERSION << std::endl;
    
    #ifdef _WIN32
        std::cout << "Running on Windows" << std::endl;
    #elif __APPLE__
        std::cout << "Running on macOS" << std::endl;
    #elif __linux__
        std::cout << "Running on Linux" << std::endl;
    #endif
    
    int choice;
    bool running = true;
    
    while (running) {
        showMenu();
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue;
        }
        
        if (choice == 5) {
            running = false;
            std::cout << "Thank you for using Calculator!" << std::endl;
            break;
        }
        
        if (choice >= 1 && choice <= 4) {
            int a, b;
            std::cout << "Enter first number: ";
            std::cin >> a;
            std::cout << "Enter second number: ";
            std::cin >> b;
            
            try {
                switch (choice) {
                    case 1:
                        std::cout << "Result: " << a << " + " << b << " = " << calc.add(a, b) << std::endl;
                        break;
                    case 2:
                        std::cout << "Result: " << a << " - " << b << " = " << calc.subtract(a, b) << std::endl;
                        break;
                    case 3:
                        std::cout << "Result: " << a << " * " << b << " = " << calc.multiply(a, b) << std::endl;
                        break;
                    case 4:
                        std::cout << "Result: " << a << " / " << b << " = " << calc.divide(a, b) << std::endl;
                        break;
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        } else {
            std::cout << "Invalid choice! Please enter 1-5." << std::endl;
        }
    }
    
    return 0;
}