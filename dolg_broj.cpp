#include <bits/stdc++.h>
using namespace std;

class LongInt {
    vector<int> lint;
    bool isNegative;

public:
    LongInt() : isNegative(false) {
        lint.push_back(0);
    }

    LongInt(const string& num) : isNegative(false) {
        size_t start = 0;
        if (num[0] == '-') {
            isNegative = true;
            start = 1;
        }
        for (size_t i = start; i < num.size(); i++) {
            if (isdigit(num[i])) {
                lint.push_back(num[i] - '0');
            }
        }
        if (lint.empty()) {
            lint.push_back(0);
        }
    }

    LongInt(long long num) : isNegative(false) {
        if (num < 0) {
            isNegative = true;
            num = -num;
        }
        if (num == 0) {
            lint.push_back(0);
        } else {
            while (num > 0) {
                lint.push_back(num % 10);
                num /= 10;
            }
            reverse(lint.begin(), lint.end());
        }
    }

    static LongInt generateRandom(int minDigits = 1, int maxDigits = 7) {
        LongInt result;
        result.lint.clear();

        int numDigits = minDigits + rand() % (maxDigits - minDigits + 1);

        result.lint.push_back(1 + rand() % 9);

        for (int i = 1; i < numDigits; i++) {
            result.lint.push_back(rand() % 10);
        }

        return result;
    }

    bool isGreaterOrEqualAbs(const LongInt& other) const {
        if (lint.size() != other.lint.size()) {
            return lint.size() > other.lint.size();
        }
        for (size_t i = 0; i < lint.size(); i++) {
            if (lint[i] != other.lint[i]) {
                return lint[i] > other.lint[i];
            }
        }
        return true;
    }

    bool isEqual(const LongInt& other) const {
        if (lint.size() != other.lint.size() || isNegative != other.isNegative) {
            return false;
        }
        for (size_t i = 0; i < lint.size(); i++) {
            if (lint[i] != other.lint[i]) {
                return false;
            }
        }
        return true;
    }

    LongInt operator+(const LongInt& v) const {
        LongInt result;
        if (isNegative && v.isNegative) {
            result = addAbsoluteValues(*this, v);
            result.isNegative = true;
        } else if (isNegative) {
            if (isGreaterOrEqualAbs(v)) {
                result = subtractAbsoluteValues(*this, v);
                result.isNegative = true;
            } else {
                result = subtractAbsoluteValues(v, *this);
            }
        } else if (v.isNegative) {
            if (isGreaterOrEqualAbs(v)) {
                result = subtractAbsoluteValues(*this, v);
            } else {
                result = subtractAbsoluteValues(v, *this);
                result.isNegative = true;
            }
        } else {
            result = addAbsoluteValues(*this, v);
        }
        return result;
    }

    LongInt operator-(const LongInt& v) const {
        LongInt result;
        if (isNegative && v.isNegative) {
            if (isGreaterOrEqualAbs(v)) {
                result = subtractAbsoluteValues(*this, v);
                result.isNegative = true;
            } else {
                result = subtractAbsoluteValues(v, *this);
            }
        } else if (isNegative) {
            result = addAbsoluteValues(*this, v);
            result.isNegative = true;
        } else if (v.isNegative) {
            result = addAbsoluteValues(*this, v);
        } else {
            if (isGreaterOrEqualAbs(v)) {
                result = subtractAbsoluteValues(*this, v);
            } else {
                result = subtractAbsoluteValues(v, *this);
                result.isNegative = true;
            }
        }
        return result;
    }

    LongInt operator*(const LongInt& v) const {
        LongInt result = multiplyAbsoluteValues(*this, v);

        result.isNegative = (isNegative != v.isNegative);
        return result;
    }

    LongInt operator/(const LongInt& v) const {

        if (v.lint.size() == 1 && v.lint[0] == 0) {
            throw runtime_error("Division by zero");
        }

        if (lint.size() == 1 && lint[0] == 0) {
            return LongInt(0);
        }

        bool resultIsNegative = (isNegative != v.isNegative);

        LongInt dividend = *this;
        dividend.isNegative = false;
        LongInt divisor = v;
        divisor.isNegative = false;

        if (!dividend.isGreaterOrEqualAbs(divisor)) {
            return LongInt(0);
        }

        LongInt result;
        result.lint.clear();

        LongInt currentDividend;
        currentDividend.lint.clear();

        for (size_t i = 0; i < dividend.lint.size(); i++) {
            currentDividend.lint.push_back(dividend.lint[i]);

            while (currentDividend.lint.size() > 1 && currentDividend.lint[0] == 0) {
                currentDividend.lint.erase(currentDividend.lint.begin());
            }

            if (!currentDividend.isGreaterOrEqualAbs(divisor)) {
                result.lint.push_back(0);
                continue;
            }

            int quotientDigit = 0;
            while (currentDividend.isGreaterOrEqualAbs(divisor)) {
                currentDividend = subtractAbsoluteValues(currentDividend, divisor);
                quotientDigit++;
            }

            result.lint.push_back(quotientDigit);
        }

        while (result.lint.size() > 1 && result.lint[0] == 0) {
            result.lint.erase(result.lint.begin());
        }

        result.isNegative = resultIsNegative;

        return result;
    }

    LongInt operator%(const LongInt& v) const {

        if (v.lint.size() == 1 && v.lint[0] == 0) {
            throw runtime_error("Modulo by zero");
        }
        if (lint.size() == 1 && lint[0] == 0) {
            return LongInt(0);
        }

        LongInt dividend = *this;
        dividend.isNegative = false;
        LongInt divisor = v;
        divisor.isNegative = false;

        if (!dividend.isGreaterOrEqualAbs(divisor)) {
            return dividend;
        }

        LongInt currentDividend = dividend;
        while (currentDividend.isGreaterOrEqualAbs(divisor)) {
            currentDividend = subtractAbsoluteValues(currentDividend, divisor);
        }

        currentDividend.isNegative = isNegative;

        return currentDividend;
    }

    void print() const {
        if (isNegative) {
            cout << "-";
        }
        for (int digit : lint) {
            cout << digit;
        }
        cout << endl;
    }

    vector<pair<LongInt, int>> factorization() const {
        vector<pair<LongInt, int>> result;
        LongInt x = *this;
        x.isNegative = false;

        for (LongInt i = LongInt("2"); x.isGreaterOrEqualAbs(i * i); i = i + LongInt("1")) {
            int k = 0;
            while ((x % i).isEqual(LongInt("0"))) {
                k++;
                x = x / i;
            }
            if (k) result.push_back(make_pair(i, k));
            if (x.isEqual(LongInt("1"))) break;
        }

        if (x.isGreaterOrEqualAbs(LongInt("1"))) result.push_back(make_pair(x, 1));
        return result;
    }

    bool isPrime(int iter = 5) const {
        if (isNegative || (lint.size() == 1 && lint[0] == 0)) {
            return false; 
        }
        if (lint.size() == 1 && (lint[0] == 2 || lint[0] == 3 || lint[0] == 5)) {
            return true; 
        }
        if (lint.size() == 1 && (lint[0] == 1 || lint[0] % 2 == 0)) {
            return false; 
        }
    
        LongInt n_minus_1 = *this - LongInt("1");
        LongInt d = n_minus_1;
        int s = 0;
        while ((d % LongInt("2")).isEqual(LongInt("0"))) {
            d = d / LongInt("2");
            s++;
        }
    
        for (int i = 0; i < iter; i++) {
            LongInt a = LongInt("2") + (generateRandom() % (*this - LongInt("3")));
    
            if (checkComposite(*this, a, d, s)) {
                return false;
            }
        }
    
        return true;
    }

private:

    static LongInt addAbsoluteValues(const LongInt& a, const LongInt& b) {
        LongInt result;
        result.lint.clear();
        int carry = 0;
        int i = a.lint.size() - 1;
        int j = b.lint.size() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += a.lint[i--];
            if (j >= 0) sum += b.lint[j--];
            result.lint.push_back(sum % 10);
            carry = sum / 10;
        }

        reverse(result.lint.begin(), result.lint.end());
        return result;
    }

    static LongInt subtractAbsoluteValues(const LongInt& a, const LongInt& b) {
        LongInt result;
        result.lint.clear();
        int borrow = 0;
        int i = a.lint.size() - 1;
        int j = b.lint.size() - 1;

        while (i >= 0 || j >= 0) {
            int diff = borrow;
            if (i >= 0) diff += a.lint[i--];
            if (j >= 0) diff -= b.lint[j--];

            if (diff < 0) {
                diff += 10;
                borrow = -1;
            } else {
                borrow = 0;
            }

            result.lint.push_back(diff);
        }

        while (result.lint.size() > 1 && result.lint.back() == 0) {
            result.lint.pop_back();
        }

        reverse(result.lint.begin(), result.lint.end());
        return result;
    }

    static LongInt multiplyAbsoluteValues(const LongInt& a, const LongInt& b) {
        LongInt result;
        result.lint.resize(a.lint.size() + b.lint.size(), 0);

        for (int i = a.lint.size() - 1; i >= 0; i--) {
            for (int j = b.lint.size() - 1; j >= 0; j--) {
                int mul = a.lint[i] * b.lint[j];
                int sum = mul + result.lint[i + j + 1];
                result.lint[i + j + 1] = sum % 10;
                result.lint[i + j] += sum / 10;
            }
        }

        while (result.lint.size() > 1 && result.lint[0] == 0) {
            result.lint.erase(result.lint.begin());
        }

        return result;
    }

    static LongInt modular_pow(const LongInt& a, const LongInt& b, const LongInt& mod) {
        LongInt result("1");
        LongInt base = a % mod;
        LongInt exponent = b;

        while (!exponent.isEqual(LongInt("0"))) {
            if ((exponent % LongInt("2")).isEqual(LongInt("1"))) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exponent = exponent / LongInt("2");
        }

        return result;
    }

    static bool checkComposite(const LongInt& n, const LongInt& a, const LongInt& d, int s) {
        LongInt x = modular_pow(a, d, n);
        if (x.isEqual(LongInt("1")) || x.isEqual(n - LongInt("1"))) {
            return false;
        }
        for (int r = 1; r < s; r++) {
            x = modular_pow(x, LongInt("2"), n);
            if (x.isEqual(n - LongInt("1"))) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    srand(time(0));

    string num;
    cout << "Enter a number to test for primality: ";
    while(cin >> num){

        LongInt x(num);
        if (x.isPrime()) {
            cout << num << " is probably prime." << endl;
        } else {
            cout << num << " is composite." << endl;
        }
    }
    return 0;
}