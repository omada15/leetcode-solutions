class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        /*
            Possibly the least efficient solution, this will take O(n^2) at worst
            This is quite space efficient, with an O(1) space complexity

            The solution is to loop through and brute force a solution
        */
        vector<int> solution;
        for (int i = 0; i<nums.size(); i++) {
            for (int j = i+1; j<nums.size(); j++) { // use i+1 to prevent checking same number
                if (nums[i]+nums[j] == target) { // check
                    solution.push_back(i);
                    solution.push_back(j);
                }
            }
        }
        return solution;
    }
};
