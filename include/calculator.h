#pragma once

class Calculator {
public:
    Calculator();
    ~Calculator();
    
    int add(int a, int b);
    int subtract(int a, int b);
    int multiply(int a, int b);
    double divide(int a, int b);
    
    void printWelcome();
};