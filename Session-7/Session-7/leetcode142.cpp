// LeetCode 142 - Linked List Cycle II
// This file contains only the Solution class as used on LeetCode.
// Input and test cases are handled by the LeetCode platform itself.
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head==NULL ||head->next==NULL)
        return NULL;

        ListNode* slow=head;
        ListNode* fast=head;

        while(fast!=NULL && fast->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
            if (slow==fast){
                break;
            }
        }
        if (fast ==NULL || fast->next ==NULL)
        return NULL;

        slow=head;
        while(slow!=fast){
            slow=slow->next;
            fast=fast->next;
        }
        return slow;
    }
};