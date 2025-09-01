#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>
}
//
impl ListNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        ListNode {
            next: None,
            val
        }
    }
}

pub fn vector2list(vec: Vec<i32>) -> Option<Box<ListNode>> {
    let mut result: Option<Box<ListNode>> = None;
    for i in 0..vec.len() {
        let mut new_result = Some(Box::new(ListNode::new(vec[vec.len() - i - 1])));
        new_result.as_mut().unwrap().next = result;
        result = new_result;
    }
    result
}

pub fn list2vector(lst: Option<Box<ListNode>>) -> Vec<i32> {
    let mut result: Vec<i32> = Vec::new();
    let mut cur = &lst;
    loop {
        match cur {
            None => break,
            Some(node) => {
                result.push(node.val);
                cur = &node.next;
            },
        }
    }
    result
}