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

ListNode* advance(ListNode* ln) {
    return ln ? ln->next : nullptr;
}

template <typename T, typename ITER, typename PRED>
T count_until(ITER iter, T init, PRED pred) {
    T count{init};
    for (;pred(iter); iter = advance(iter)) { ++count; }
    return count;
}

template <typename ITER>
std::tuple<ITER, ITER> find_middle(ITER iter, int cnt) {
    auto prev = iter;
    for (int i = 0; i++ < cnt / 2; iter = advance(iter)) {
        prev = iter;
    }
    return std::make_tuple(prev, iter);
}

template <typename ITER>
bool equal(ITER iter1, ITER iter2) {
    bool success = true;
    while(iter1 != iter2) {
        if (iter1->val != iter2->val) {
            success = false;
            break;
        }
        if (iter1->next == iter2) break;
        iter1 = iter1->next;
        iter2 = iter2->next;
    }
    return success;
}

std::tuple<ListNode*, ListNode*> flip(ListNode* middle , ListNode* prev_middle) {
    while(middle->next) {
        auto* next = middle->next;
        middle->next = prev_middle;
        prev_middle = middle;
        middle = next;
    }
    middle->next = prev_middle;
    return std::make_tuple(prev_middle, middle);
}

void flip_back(ListNode* prev_end, ListNode* middle, ListNode* end_flipped) {
    while (prev_end != middle) {
        auto *next = prev_end->next;
        prev_end->next = end_flipped;
        end_flipped = prev_end;
        prev_end = next;
    }
    middle->next = end_flipped;
}

class Solution {
public:
  static bool isPalindrome(ListNode* head) {
    if (!head) return true;
    const auto isend([](auto iter){ return iter != nullptr; });
    auto cnt = count_until(head, 0, isend);
    auto [prev_middle, middle] = find_middle(head, cnt);
    auto [prev_end, end_flipped] = flip(middle, prev_middle);
    bool success = equal(head, end_flipped);
    flip_back(prev_end, middle, end_flipped);
    end_flipped->next = nullptr;
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
    std::clog << std::endl;
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
