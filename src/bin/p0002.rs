use leetcode::list::*;

struct Solution {}

impl Solution {
    pub fn add_two_numbers(l1: Option<Box<ListNode>>, l2: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let mut result: Option<Box<ListNode>> = None;
        let mut cur1 = &l1;
        let mut cur2 = &l2;
        let mut carry: i32 = 0;
        {
            let mut cur_res = &mut result;
            loop {
                if *cur1 == None && *cur2 == None && carry == 0 {
                    break;
                } else {
                    let n1 = match cur1 {
                        Some(node) => {
                            cur1 = &cur1.as_ref().unwrap().next;
                            node.val
                        },
                        None => 0
                    };
                    let n2 = match cur2 {
                        Some(node) => {
                            cur2 = &cur2.as_ref().unwrap().next;
                            node.val
                        },
                        None => 0
                    };
                    let n = (n1 + n2 + carry) % 10;
                    carry = if (n1 + n2 + carry) >= 10 { 1 } else { 0 };
                    *cur_res = Some(Box::new(ListNode::new(n)));
                    cur_res = &mut cur_res.as_mut().unwrap().next;
                    continue;
                }
            }
        }
        result
    }
}

fn test(l1: Vec<i32>, l2: Vec<i32>) -> Vec<i32> {
    list2vector(Solution::add_two_numbers(vector2list(l1), vector2list(l2)))
}

fn main() {
    println!("{:?}", test(vec![1,2,3], vec![4,5,6]));
}
