class Solution {
public:
    int reverse(int x) {
        /*
            Store to list, then un-ravel the list

            Time complexity: O(n)
            Space complexity: O(n)
        */
        string curString = ""; bool neg = x<0; vector<int> revNum;
        try { // errors -> 0
            if (neg) {
                x = stoi(to_string(x).substr(1)); // remove sign before reverse
            }
            for (int i = 0; i<to_string(x).length(); i++) {
                curString += to_string(x)[i]; // slightly janky
                revNum.push_back(stoi(curString));
                curString = ""; // clear string
            }
            string rn = "";
            for (int j = revNum.size()-1; j>=0; j--) { // read in reverse
                rn = rn + to_string(revNum[j]);  // append back           
            }
            if (neg) { // add sign back
                rn = "-"+rn;
            }
            return stoi(rn);
        } catch (exception& e) {
            return 0;
        }
    }
};
