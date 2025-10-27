#include <string>
#include <climits>
#include <cctype>

class Solution {
public:
    int myAtoi(string s) {
        /*
            Runtime: O(1) (0ms, beats 100%)
            Space complexity: O(n)
        */

        // Trim leading and trailing spaces, very janky
        size_t start = s.find_first_not_of(' ');
        if (start == string::npos) return 0;
        size_t end = s.find_last_not_of(' ');
        s = s.substr(start, end - start + 1);

        if (s.empty()) { // no empty strings allowed
            return 0;
        }

        int sign = 1, num = 0, i = 0, digit = 0;
        if (s[0] == '-' || s[0] == '+') { // get signedness
            sign = (s[0] == '+') ? 1 : -1;
            i++;
        }

        while (i < (int)s.length() && isdigit(s[i])) {
            digit = s[i] - '0'; // current char to int
            if (num > (INT_MAX - digit) / 10) { // prevent int overflow
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            num = num * 10 + digit; // add digit
            i++; // count up on string
        }
        return sign * num; // bring back sign
    }
};
