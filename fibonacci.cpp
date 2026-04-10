#include <bits/stdc++.h>
#include <cstdint>
#include <iostream>
using namespace std;
typedef __int128_t int128;

class uint512 {
private:
    array<uint64_t, 8> data;

    static string addStrings(string s1, const string& s2) {
        string res = "";
        int i = s1.size() - 1, j = s2.size() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry + (i >= 0 ? s1[i--] - '0' : 0) + (j >= 0 ? s2[j--] - '0' : 0);
            res.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        reverse(res.begin(), res.end());
        return res;
    }

    string toDecimalString() const {
        string decimalStr = "0";
        string powerOfTwo = "1";

        for (int i = 0; i < 8; ++i) {
            uint64_t limb = data[i];
            for (int bit = 0; bit < 64; ++bit) {
                if ((limb >> bit) & 1) {
                    decimalStr = addStrings(decimalStr, powerOfTwo);
                }
                powerOfTwo = addStrings(powerOfTwo, powerOfTwo);
            }
        }
        return decimalStr;
    }

public:
    uint512(uint64_t low = 0) {
        data.fill(0);
        data[0] = low;
    }
    uint512 operator+(const uint512& other) const {
        uint512 result;
        unsigned __int128 carry = 0;
        for (int i = 0; i < 8; ++i) {
            unsigned __int128 sum = (unsigned __int128)data[i] + other.data[i] + carry;
            result.data[i] = (uint64_t)sum;
            carry = sum >> 64;
        }
        return result;
    }

    uint512 operator-(const uint512& other) const {
        uint512 result;
        unsigned __int128 borrow = 0;
        for (int i = 0; i < 8; ++i) {
            unsigned __int128 a = data[i];
            unsigned __int128 b = (unsigned __int128)other.data[i] + borrow;
            if (a < b) {
                result.data[i] = (uint64_t)(a + ((unsigned __int128)1 << 64) - b);
                borrow = 1;
            } else {
                result.data[i] = (uint64_t)(a - b);
                borrow = 0;
            }
        }
        return result;
    }

    bool operator==(const uint512& other) const {
        return data == other.data;
    }

    bool operator<(const uint512& other) const {
        for (int i = 7; i >= 0; --i) {
            if (data[i] < other.data[i]) return true;
            if (data[i] > other.data[i]) return false;
        }
        return false;
    }

    bool operator>(const uint512& other) const { return other < *this; }
    bool operator<=(const uint512& other) const { return !(*this > other); }
    bool operator>=(const uint512& other) const { return !(*this < other); }

    int length(bool hexMode = false) const {
        if (hexMode) {
            for (int i = 7; i >= 0; --i) {
                if (data[i] != 0) {
                    int count = i * 16; 
                    uint64_t temp = data[i];
                    while (temp > 0) {
                        temp >>= 4;
                        count++;
                    }
                    return count;
                }
            }
            return 1;
        } else {
            string s = this->toDecimalString();
            return static_cast<int>(s.length());
        }
    }

    void print(bool hexMode = true) const {
        if (hexMode) {
            bool leadingZeros = true;
            for (int i = 7; i >= 0; --i) {
                if (leadingZeros && data[i] == 0 && i != 0) continue;
                if (leadingZeros) {
                    cout << hex << data[i];
                    leadingZeros = false;
                } else {
                    cout << setfill('0') << setw(16) << hex << data[i];
                }
            }
            cout << dec << endl;
        } else {
            cout << toDecimalString() << endl;
        }
    }
};

typedef __uint128_t uint128;
vector<uint512> fibs(10000);
int maxn = 0;

uint512 fib(int n) {
	uint512 j;
	if (n <= 1)
		return 1;
	else if (fibs[n] != 0)
		return fibs[n];
	else {
		j = fib(n - 1) + fib(n - 2);
		fibs[n] = j;
		if (n > maxn)
			maxn = n;
		return j;
	}
}

ostream &operator<<(ostream &os, int128 n) {
	if (n == 0)
		return os << "0";
	if (n < 0) {
		os << "-";
		n = -n;
	}
	string s;
	while (n > 0) {
		s += (char)('0' + (n % 10));
		n /= 10;
	}
	reverse(s.begin(), s.end());
	return os << s;
}

int main() {
	int a;
	cin >> a;
	uint512 n = fib(a);
    /*
	for (int i = 0; i < maxn; i++) {
		fibs[i].print(false);
	}*/
	cout << "solution " << endl;
	n.print(false);
    cout << n.length();
}
