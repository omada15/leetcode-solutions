#include <stdexcept>

class Solution {
public:
    bool isPalindrome(int x) {
        /*
            Write int reverse, check against original

            Time complexity: O(n)
        */
        try {
            if (x < 0) {
                return false; // negative numbers cannot be palindromes
            } else {
                string s = to_string(x);
                string pdn = "";
                for (int i = 0; i < s.length(); i++) {
                    pdn += s[s.length() - i - 1];
                }
                if (x == stoi(pdn)) {
                    return true;
                } else {
                    return false;
                }
            }
        } catch (const exception&) {
            return false;
        }
    }
};
