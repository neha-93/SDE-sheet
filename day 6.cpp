//find the point of Intersection of two linked lists

//for every node in one linked list traverse the other linked list entirely and check if the same node is present or not
//time O(n^2) space O(1)

//store everynode of first linked list in a hashmap and then traverse the other list and check if node in hashmap or not
//time O(n) space O(n)

//time O(n) space O(1)


ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {

	ListNode *l1 = headA, *l2 = headB;

	while (l1 != l2) {

		l1 = l1 ? l1->next : headB;
		l2 = l2 ? l2->next : headA;

	}
	return l1;
}

//find cycle in linked list

//tell the hashmap approach store every node in hashmap and if node already present the cycle is there
//time O(n) space O(n)

bool hasCycle(ListNode *head) {

	ListNode *slow = head, *fast = head;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast) return true;
	}
	return false;
}


//Reverse linked list in the size of K

ListNode* reverseKGroup(ListNode* head, int k) {

	if (!head || k == 1) return head;

	ListNode *preheader = new ListNode(-1);
	preheader->next = head;

	ListNode *cur = head, *pre = preheader, *nex;

	int cnt = 0;
	while (head) {
		head = head->next;
		cnt++;
	}
	int curcnt = 0;

	while (curcnt + k <= cnt) {

		cur = pre->next;
		nex = cur->next;

		for (int i = 1; i < k; ++i) {
			cur->next = nex->next;
			nex->next = pre->next;
			pre->next = nex;
			nex = cur->next;
		}
		pre = cur;
		curcnt += k;
	}
	return preheader->next;
}

//Linked list is palindrome or not

//store the values of linked list and check if the array is palindrome or not
//time O(2N) space O(N)

//find the middle element and reverse the later half of the linked list and then check if all nodes match
//or not
//time O(N/2+N/2+N/2) space O(1)

ListNode* reverse(ListNode* head) {

	ListNode *pre = NULL, *cur = head, *nex;


	while (cur) {
		nex = cur->next;
		cur->next = pre;
		pre = cur;
		cur = nex;
	}
	return pre;
}

public:
bool isPalindrome(ListNode* head) {

	if (!head || !head->next) return true;
	ListNode *slow = head, *fast = head;

	while (fast->next && fast->next->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	slow->next = reverse(slow->next);

	slow = slow->next;
	fast = head;

	while (slow) {
		if (slow->val != fast->val) return false;
		slow = slow->next;
		fast = fast->next;
	}

	return true;
}

//Starting point of a linked list

//first tell the hashmap approach

//then tell the two pointer slow and fast pointer approach

ListNode *detectCycle(ListNode *head) {

	ListNode *fast = head, *slow = head;

	while (fast && fast->next) {
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow) {
			fast = head;
			while (fast != slow) {
				fast = fast->next;
				slow = slow->next;
			}
			return slow;
		}
	}
	return NULL;
}


//Flattening a linked List

/* Node structure  used in the program

struct Node{
	int data;
	struct Node * next;
	struct Node * bottom;

	Node(int x){
	    data = x;
	    next = NULL;
	    bottom = NULL;
	}

};
*/

/*  Function which returns the  root of
    the flattened linked list. */


Node *mergeList(Node *a, Node *b) {

	Node *temp = new Node(0);
	Node *res = temp;

	while (a && b) {

		if (a->data < b->data) {
			temp->bottom = a;
			temp = temp->bottom;
			a = a->bottom;
		}
		else {
			temp->bottom = b;
			temp = temp->bottom;
			b = b->bottom;
		}

	}

	if (a) temp->bottom = a;
	else temp->bottom = b;

	return res->bottom;
}

Node *flatten(Node *root)
{
	if (!root || !root->next) return root;

	root->next = flatten(root->next);

	root = mergeList(root, root->next);

	return root;
}

//Rotate a linked list by k places

ListNode* rotateRight(ListNode* head, int k) {

	if (!head || k == 0) return head;
	ListNode *right = head, *left = head;

	int cnt = 0;
	while (left) {
		left = left->next;
		cnt++;
	}
	left = head;

	for (int i = 0; i < k % cnt; ++i) right = right->next;

	while (right->next) {
		right = right->next;
		left = left->next;
	}

	right->next = head;
	head = left->next;
	left->next = NULL;

	return head;
}
