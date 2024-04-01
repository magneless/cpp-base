#include <iostream>
#include <string>
#include <algorithm>

#include "BigInt.h"

BigInt::BigInt() : size_(0), negative_(false), num_(nullptr) {}
BigInt::BigInt(const std::string& str) {
    size_ = str.size();
    negative_ = str[0] == '-';
    if (negative_) --size_;

    num_ = new int[size_];

    for (int i = 0; i < size_; ++i) {
        num_[size_ - i - 1] = str[negative_ + i] - '0';
    }
}
BigInt::BigInt(const BigInt& other) :
    size_(other.size_), negative_(other.negative_) {
    num_ = new int[size_];
    for (int i = 0;  i < size_; ++i) {
        num_[i] = other.num_[i];
    }
}
BigInt::BigInt(BigInt&& other) : size_(other.size_),
    negative_(other.negative_), num_(other.num_) {
    other.num_ = nullptr;
    other.size_ = 0;
}
BigInt::~BigInt() {
    delete [] num_;
}

BigInt& BigInt::operator=(const BigInt& other) {
    if (this != &other) {
        delete[] num_;
        size_ = other.size_;
        negative_ = other.negative_;
        num_ = new int[size_];
        for (int i = 0; i < size_; i++) {
            num_[i] = other.num_[i];
        }
    }

    return *this;
}

BigInt& BigInt::operator=(BigInt&& other) {
    if (this != &other) {
        delete[] num_;
        num_ = other.num_;
        size_ = other.size_;
        negative_ = other.negative_;
        other.num_ = nullptr;
        other.size_ = 0;
    }

    return *this;
}


BigInt BigInt::operator+(const BigInt& other) const {
    BigInt res;
    if (!negative_ && !other.negative_) {
        //x1 + x2
        res.num_ = sum(num_, other.num_, size_,
            other.size_, &res.size_);
        res.negative_ = false;
    }
    else if (negative_ && other.negative_) {
        //  -(x1 + x2)
        res.num_ = sum(num_, other.num_, size_,
            other.size_, &res.size_);
        res.negative_ = true;
    }
    else if (negative_ && !other.negative_){
        //  x2 - x1
        if (-*this <= other) {
            res.num_ = dif(other.num_, num_,
                other.size_, size_, &res.size_);
            res.negative_ = false;
        }
        else {
            res.num_ = dif(num_, other.num_,
                size_, other.size_, &res.size_);
            res.negative_ = true;
        }
    }
    else {
        //  x1 - x2
        if (*this <= -other) {
            res.num_ = dif(other.num_, num_,
                other.size_, size_, &res.size_);
            res.negative_ = true;
        }
        else {
            res.num_ = dif(num_, other.num_,
                size_, other.size_, &res.size_);
            res.negative_ = false;
        }
    }

    return res;
}

BigInt BigInt::operator+(const int32_t& num) const {
    BigInt res = *this + BigInt(std::to_string(num));

    return res;
}

BigInt BigInt::operator-(const BigInt& other) const {
    BigInt res = *this + -other;
   
    return res;
}

BigInt BigInt::operator-(const int32_t& num) const {
    BigInt res = *this - BigInt(std::to_string(num));

    return res;
}

BigInt BigInt::operator-() const {
    BigInt res(*this);
    res.negative_ = !res.negative_;

    return res;
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt res;
    res.size_ = size_ + other.size_;
    res.num_ = new int [res.size_];
    for (int i = 0; i < res.size_; ++i) res.num_[i] = 0;

    for (int i = 0; i < other.size_; ++i) {
        int re = 0;
        for (int j = 0; j < size_ || re != 0; ++j) {
            int tmpMult = res.num_[i + j] + re;
            if (j < size_) tmpMult += other.num_[i] * num_[j];
            res.num_[i + j] = tmpMult % 10;
            re = tmpMult / 10;
        }
    }

    while(res.num_[res.size_ - 1] == 0 && res.size_ != 1) --res.size_;
    if (res.num_[0] == 0 && res.size_ == 1) res.negative_ = false;
    else res.negative_ = negative_ != other.negative_;

    return res;
}

BigInt BigInt::operator*(const int32_t& num) const {
    BigInt res = *this * BigInt(std::to_string(num));

    return res;
}

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.negative_) out << "-";
    for (int i = num.size_ - 1; i >= 0; --i) {
        out << num.num_[i];
    }

    return out;
}

bool BigInt::operator<(const BigInt& other) const {
    if (negative_ != other.negative_) {
        return negative_;
    }

    if (size_ != other.size_) {
        if (negative_) return size_ > other.size_;
        else return size_ < other.size_;
    }

    for (int i = size_ - 1; i >= 0; --i) {
        if (num_[i] != other.num_[i]) {
            if (negative_) return num_[i] > other.num_[i];
            else return num_[i] < other.num_[i];
        }
    }

    return false;
}

bool BigInt::operator==(const BigInt& other) const {
    if (negative_ != other.negative_) return false;
    if (size_ != other.size_) return false;
    for (int i = 0; i < size_; ++i) {
        if (num_[i] != other.num_[i]) return false;
    }

    return true;
}

bool BigInt::operator<=(const BigInt& other) const {
    return (*this < other) || (*this == other);
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator>(const BigInt& other) const {
    return !(*this <= other);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}


int* sum(const int* x1, const int* x2, int size1, int size2, int *size) {
    //  x1 + x2
    int maxSize = std::max(size1, size2);
    int* res = new int[maxSize + 1];
    *size = maxSize + 1;
    int re = 0;
    for (int i = 0; i < maxSize; ++i) {
        int tmpSum = re;
        if (i < size1) tmpSum += x1[i];
        if (i < size2) tmpSum += x2[i];
        res[i] = tmpSum % 10;
        re = tmpSum / 10;
    }

    if (re != 0) res[*size - 1] = re;
    else --(*size);

    return res;
}

int* dif(const int* x1, const int* x2, int size1, int size2, int *size) {
    //  x1 - x2
    int maxSize = std::max(size1, size2);
    int* res = new int[maxSize];
    *size = maxSize;
    int re = 0;
    for (int i = 0; i < maxSize; ++i) {
        int tmpDif = 10 + re;
        if (i < size1) tmpDif += x1[i];
        if (i < size2) tmpDif -= x2[i];
        res[i] = tmpDif % 10;
        re = tmpDif / 10 - 1;
    }

    while (res[*size - 1] == 0 && *size != 1) --(*size);

    return res;
}
