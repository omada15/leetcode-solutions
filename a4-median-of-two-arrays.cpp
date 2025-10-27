class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        /*
            Just finding median
            Time Complexity: O(n) = n*log(n)
        */
        for (int i = 0; i<nums2.size(); i++) { // merge vectors
            nums1.push_back(nums2[i]); // this is where n comes from
        }
        sort(nums1.begin(), nums1.end()); // then log n from here

        double out = 0.0; int middleInt = 0;
        if (nums1.size() % 2 == 0) { // check parity of vector length
            middleInt = nums1.size()/2 - 1; // find middle int
            out = (float(nums1[middleInt]) + float(nums1[middleInt+1]))/2; // take average
        } else {
            middleInt = (nums1.size()-1) / 2; // get index of middle integer
            out = nums1[middleInt];
        }
        return out;
    }
};
