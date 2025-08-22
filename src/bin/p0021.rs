use leetcode::list::*;

impl Solution {
    pub fn merge_two_lists(list1: Option<Box<ListNode>>, list2: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let mut p1 = &list1;
        let mut p2 = &list2;
        let mut result: Vec<i32> = vec!();
        loop {
            let v1: i32;
            let v2: i32;
            match p1 {
                None => {
                    match p2 {
                        None => break,
                        Some(px) => {
                            result.push(px.val);
                            p2 = &px.next;
                            continue;
                        }
                    }
                },
                Some(p1) => { v1 = p1.val; },
            }
            match p2 {
                None => {
                    match p1 {
                        None => break,
                        Some(px) => {
                            result.push(px.val);
                            p1 = &px.next;
                            continue;
                        }
                    }
                },
                Some(p2) => { v2 = p2.val; },
            }
            if v1 <= v2 {
                result.push(v1);
                p1 = match p1 {
                    Some(px) => &px.next,
                    None => p1,
                };
            } else {
                result.push(v2);
                p2 = match p2 {
                    Some(px) => &px.next,
                    None => p2,
                };
            }
        }
        vector2list(result)
    }
}

struct Solution {}
fn main() {
    println!("{:?}", list2vector(
        Solution::merge_two_lists(vector2list(vec!(1,3,5)),
                                  vector2list(vec!(2,4,6)))));
}