#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        /*
            This solution is done by literally reversing the linked list, first
            storing it inside of vector ans, then reading vector ans in reverse

        Time complexity: O(n)
        Space complexity: O(n)
        */
        vector<int> ans;
        ListNode *headMirror= head;
        /*
            headMirror will perfectly match head, any 
            changes made to headMirror also affect head
        */
        while(headMirror!=NULL) {
            ans.push_back(headMirror->val); // store values in vector ans
            headMirror=headMirror->next; // next value
        }
        headMirror=head; // bring back to front
        for (int i=ans.size()-1; headMirror!=NULL; i--){
            /*
                this for loop will loop through ans and place them into headMirror
                but in reverse order. All changes made to headMirror matches head
            */
            headMirror->val=ans[i]; // i counts down, so this works
            headMirror=headMirror->next;
        }
        return head;
    }
};
