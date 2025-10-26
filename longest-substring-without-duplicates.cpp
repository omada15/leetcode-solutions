class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        /*
            Brute force solution: literally just find the longest string

            Time complexity: O(1), 0ms beats 100%
            Space complexity: O(1), 10.14MB beats 99.56%
        */
        if (s.length() < 2) {
            return s.length(); // too short
        } else {
            int startValue = 0, maxLength = 0, currentLength = 0;
            for (int x = 1; x<s.length(); x++) { // main loop
                for (int y = startValue; y<x; y++) {
                    startValue = (s[x] == s[y]) ? y+1 : startValue; // adjust start value if duplicate found
                }
                currentLength = x-startValue + 1; // adjust current value
                maxLength = (currentLength>maxLength) ? currentLength : maxLength; // check and adjust
            }
            return maxLength;
        }
    }
};
