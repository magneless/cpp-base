#pragma once

#include <iostream>

class BigInt {
public:
    BigInt();
    BigInt(const std::string& num);
    BigInt(const BigInt& other);
    BigInt(BigInt&& other);
    ~BigInt();

    BigInt& operator=(const BigInt& other);
    BigInt& operator=(BigInt&& other);

    BigInt operator+(const BigInt& other) const;
    BigInt operator+(const int32_t& num) const;

    BigInt operator-(const BigInt& other) const;
    BigInt operator-(const int32_t& num) const;
    BigInt operator-() const;

    BigInt operator*(const BigInt& other) const;
    BigInt operator*(const int32_t& num) const;

    bool operator<(const BigInt& other) const;
    bool operator==(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    
    friend std::ostream& operator<<(std::ostream& out, const BigInt& num);

private:
    int size_;
    bool negative_;
    int* num_;
};

int* sum(int* x1, int* x2, int size1, int size2, int& size);
int* dif(int* x1, int* x2, int size1, int size2, int& size);
