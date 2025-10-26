/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        /*
            Uses a "binary add" style solution
            uses carry

            Time complexity: O(Max(M, N))
            Memory complexity: O(Max(M, N))
        */
        ListNode* dummy = new ListNode(); // initiate empty node
        ListNode* res = dummy; // pointer to store 1st pos
        int total = 0, carry = 0;

        while (l1 || l2 || carry) {
            total = carry; // add carry

            if (l1) {
                total += l1->val; 
                l1 = l1->next;
            }
            if (l2) {
                total += l2->val;
                l2 = l2->next;
            }

            int num = total % 10; // drop carry
            carry = total / 10; // because carry is int, it must be 1 or 0
            dummy->next = new ListNode(num); // add to dummy
            dummy = dummy->next; // loop on
        }

        ListNode* result = res->next; // first node is empty
        delete res; // prevent leakage
        return result;    
    }
};
