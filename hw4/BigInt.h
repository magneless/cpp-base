#pragma once

#include <iostream>
#include <string>

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

int* sum(const int* x1, const int* x2, int size1, int size2, int* size);
int* dif(const int* x1, const int* x2, int size1, int size2, int* size);
