//
// Created by kobi on 9/12/20.
// https://leetcode.com/problems/palindrome-linked-list/

#include <cassert>
#include <iomanip>
#include <iostream>

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
    auto *middle = head;
    std::clog << "middle phase: head " << middle->val << " prev " << prev->val << '\n';
    // flip
    while(head->next) {
      auto* next = head->next;
      head->next = prev;
      prev = head;
      head = next;
    }
    head->next = prev;

    std::clog << "head " << head->val << " next " << head->next->val << " prev " << prev->val << '\n';

    // go from 2 directions
    auto* fwd = orig;
    auto* back = head;
    bool success = true;
    while(fwd != back) {
      if (fwd->val != back->val) {
        success = false;
        break;
      }
      if (fwd->next == back) break;
      fwd = fwd->next;
      back = back->next;
    }

    // leetcode is allocating on the heap and need to re-do the whole flipping
    auto* end = head;
    if (head->next == middle) {
      middle->next = head;
    } else {
      while (head->next != middle) {
        auto *next = prev->next;
        prev->next = head;
        head = prev;
        prev = next;
      }
    }
    end->next = nullptr;

    return success;
  }
};

int main() {
  {
    ListNode l1(1), l2(2), l3(3), l4(2), l5(1);
    l1.next = &l2;
    l2.next = &l3;
    l3.next = &l4;
    l4.next = &l5;
    const auto sol = Solution::isPalindrome(&l1);
    std::clog << std::boolalpha << sol << '\n';
    std::clog << l1.val << ',' << l1.next->val << ',' << l1.next->next->val
              << ',' << l1.next->next->next->val << ','
              << l1.next->next->next->next->val << '\n';
    assert(l1.next->next->next->next->next == nullptr);
    assert(sol);
  }

  {
    ListNode l1(1), l2(2);
    l1.next = &l2;
    const auto sol = Solution::isPalindrome(&l1);
    std::clog << std::boolalpha << sol << '\n';
    std::clog << l1.val << ',' << l1.next->val << '\n';
    assert(l1.next->next == nullptr);
    assert(!sol);
  }

  {
    ListNode l1(0), l2(0);
    l1.next = &l2;
    const auto sol = Solution::isPalindrome(&l1);
    std::clog << std::boolalpha << sol << '\n';
    std::clog << l1.val << ',' << l1.next->val << '\n';
    assert(l1.next->next == nullptr);
    assert(sol);
  }

  {
    ListNode l1(1), l2(0), l3(0);
    l1.next = &l2;
    l2.next = &l3;
    const auto sol = Solution::isPalindrome(&l1);
    std::clog << std::boolalpha << sol << '\n';
    std::clog << l1.val << ',' << l1.next->val << '\n';
    assert(l1.next->next->next == nullptr);
    assert(!sol);
  }

}
