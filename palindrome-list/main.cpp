//
// Created by kobi on 9/12/20.
// https://leetcode.com/problems/palindrome-linked-list/

#include <iostream>
#include <iomanip>

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

struct ListNode final {
  int val{};
  ListNode *next{};
  ListNode() : val(0), next(nullptr) {}
  explicit ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  static bool isPalindrome(ListNode* head) {
    if (!head) return true;
    auto* orig = head;
    auto cnt = 1UL;
    // find total O(N)
    while(head) {
      if (!head->next) break;
      head = head->next;
      ++cnt;
    }
    std::clog << "count " << cnt << '\n';
    // go to middle and flip the "next"
    head = orig;
    auto* prev = head;
    for(auto i = 0UL; i < cnt/2 ; ++i) {
      if (head->next) {
        prev = head;
        head = head->next;
      }
    }
    std::clog << "middle phase: head " << head->val << " prev " << prev->val << '\n';
    // flip
    while(head->next) {
      auto* next = head->next;
      head->next = prev;
      prev = head;
      head = next;
    }
    head->next = prev;

    std::clog << "head " << head->val << " next " << head->next->val << '\n';

    // go from 2 directions
    auto* fwd = orig;
    auto* back = head;
    while(fwd != back) {
      if (fwd->val != back->val) return false;
      fwd = fwd->next;
      back = back->next;
    }

    // leetcode is allocating on the heap and need to re-do the whole flipping


    return true;
  }
};

int main() {
  ListNode l1(1), l2(2), l3(3), l4(2), l5(1);
  l1.next = &l2;
  l2.next = &l3;
  l3.next = &l4;
  l4.next = &l5;
  std::clog << std::boolalpha << Solution::isPalindrome(&l1) << '\n';
}
