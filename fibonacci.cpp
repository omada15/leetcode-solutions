/*
    Yes, this code is undocumented (not anymore, but i dont delete/edit old comments. the documentation is not written for a coder)

    drag the bar to the right until you can see the head of the arrow
    just make sure the input on the box over there ------------------------------------------------------------------------------------------------------------------------->
    is exactly one number which is int32 and less than 10000 because the 10kth fibonacci number is quite close to 2^512
*/

// these are libraries, don't worry about them
#include <bits/stdc++.h>
#include <cstdint>
#include <iostream>
using namespace std;
typedef __int128_t int128;
typedef __uint128_t uint128;
const size_t bitLimit = 512;

int intBitLimit = bitLimit; //appease the c++ gods by converting size_t to int

/**
    In coding, we use the binary system.
    these numbers can get very long
    think 01010100101111010101111010111011010 (11373573594)
    that number has quite a few digits
    c++ by default lets you use 32 digits to store these numbers

    but if you ran the program, you might notice thats a lot more than 32 digits
    the code below makes a special structure that lets me exceed that.
    You do not need to read the code to understand the rest of the function, but just know
    it lets me go up to 64*bitLimit digits (1.09e+2466)
*/
class bigInt {
private:
    array<uint64_t, bitLimit> data; // the actual structure is broken into 128 64 bit long segments. a bit is a 1 or a 0 in binary

    static string addStrings(string s1, const string& s2) { // this is a helper function i will not document
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

    string toDecimalString() const { // as is this one
        string decimalStr = "0";
        string powerOfTwo = "1";

        for (int i = 0; i < bitLimit; ++i) {
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
    bigInt(uint64_t low = 0) { // this sets the default value of a bigInt (0), which is used later
        data.fill(0);
        data[0] = low;
    }
    /*
        This is what I actually wrote this code for, learning how to overlaod the operator[operation]() function
        it allows me to make +  and - do what i want
    */
    bigInt operator+(const bigInt& other) const { 
        bigInt result;
        unsigned __int128 carry = 0;
        for (size_t i = 0; i < bitLimit; ++i) {
            unsigned __int128 sum = (unsigned __int128)data[i] + other.data[i] + carry;
            result.data[i] = (uint64_t)sum;
            carry = sum >> 64;
        }
        return result;
    }

    bigInt operator-(const bigInt& other) const {
        bigInt result;
        unsigned __int128 borrow = 0;
        for (size_t i = 0; i < bitLimit; ++i) {
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

    // these operator overloads are the standard operations you can run. ==, <, >, <=, >=
    bool operator==(const bigInt& other) const {
        return data == other.data;
    }

    bool operator<(const bigInt& other) const {
        for (size_t i = (bitLimit/2)-1; i >= 0; --i) {
            if (data[i] < other.data[i]) return true;
            if (data[i] > other.data[i]) return false;
        }
        return false;
    }

    bool operator>(const bigInt& other) const { return other < *this; } // im lazy
    bool operator<=(const bigInt& other) const { return !(*this > other); } // very lazy
    bool operator>=(const bigInt& other) const { return !(*this < other); } 
    bool operator!=(const bigInt& other) const { return !(*this == other); }

    int length(bool hexMode = false) const { // yet another helper function, returns the length
        if (hexMode) {
            for (size_t i = (bitLimit/2)-1; i >= 0; --i) {
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

    void print(bool hexMode = true) const { // printer function because cout << does not accept 512 bit integers
        if (hexMode) {
            bool leadingZeros = true;
            for (size_t i = (bitLimit/2)-1; i >= 0; --i) {
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

ostream &operator<<(ostream &os, int128 n) { // a helper function to print 128 bit numbers
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

// ah here our code starts
vector<bigInt> fibs(20000); // this is a list that i will use to store fibonacci numbers. all the values are automatically set to the default value
int maxn = 0; // this variable is used for printing fibonacci number list

bigInt fib(int n) { // this is the actual code that calculates fibonacci numbers
	bigInt j; 
    size_t i = n;
	if (n <= 1) // the 1st (and 0th) fibonacci numbers are both 1
		return 1;
	else if (fibs[i] != 0) // this is where the default value from line 61 is used. I am checking if the nth fibonacci number was already calculated
		return fibs[i]; // if it is then use that because otherwise slow 
	else {
		j = fib(n - 1) + fib(n - 2); // this is the core of the calculation. if you need a refresher, the nth fibonacci number is the sum of the two previous fibonacci numbers
		fibs[i] = j;
		if (n > maxn)
			maxn = n;
		return j;
	}
}

int main() {
	int a = 0;
    cin >> a;
    if (a > 10000) {a = 10000; cout << "No greater than 10k pls";}
    cout << "bit limit " << bitLimit*64 << endl;
	bigInt n = fib(a);
    /*
	for (int i = 0; i < maxn; i++) { // here i need to know what the highest fibonacci number that was calculated is for printing the list
		fibs[i].print(false);
	}*/
    cout << "solution ";
	n.print(false); // print the fibonacci number
    cout << "digits " << n.length(); // and its length
    return 0;
}
