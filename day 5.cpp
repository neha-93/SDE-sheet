//reverse a linked list

//maintain 2 pointers one prev and one next at each point make head->next = prev and increament prev
//and next pointer untill head becomes null

ListNode* reverseList(ListNode* head) {

	if (!head || !head->next) return head;
	ListNode *prev = NULL, *nex;

	while (head) {
		nex = head->next;
		head->next = prev;
		prev = head;
		head = nex;
	}
	return prev;
}

//middle of the linked list

//we will tell that we will count the number of nodes of the linked list
//and in the next iteration we will traverse the linked list to get numberOfNodes/2 + 1th node of the
//linked list


//we we tell the two fast and slow pointer approach

ListNode* middleNode(ListNode* head) {

	if (!head || !head->next) return head;

	ListNode *slow = head, *fast = head;

	while (fast && fast->next) {

		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}


//merge two sorted linked list
//create a new linked list with the smaller node
//time O(n1+n2) space O(n1+n2)

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {

	ListNode *head = new ListNode();
	ListNode *preheader = head;

	while (l1 && l2) {

		if (l1->val < l2->val) {

			ListNode *tmp = new ListNode(l1->val);
			head->next = tmp;
			head = tmp;
			l1 = l1->next;

		}
		else {
			ListNode *tmp = new ListNode(l2->val);
			head->next = tmp;
			head = tmp;
			l2 = l2->next;
		}
	}

	while (l1) {
		ListNode *tmp = new ListNode(l1->val);
		head->next = tmp;
		head = tmp;
		l1 = l1->next;
	}
	while (l2) {
		ListNode *tmp = new ListNode(l2->val);
		head->next = tmp;
		head = tmp;
		l2 = l2->next;
	}
	return preheader->next;
}

//just change the pointers
//time O(n1+n2) space O(1)

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {

	if (!l1) return l2;
	if (!l2) return l1;

	ListNode *head1 = l1, *head2 = l2;

	ListNode *tmp;

	if (head1->val > head2->val) swap(head1, head2);
	ListNode *header = head1;

	while (head1 && head2) {

		while (head1 && head1->val <= head2->val) {
			tmp = head1;
			head1 = head1->next;
		}
		tmp->next = head2;
		swap(head1, head2);
	}
	return header;
}

//delete nth node from the linked list
//first count the number of nodes then go to n-k-1th node and do head->next = head->next->next;

//maintain 2 pointers move the first pointer by n position and then move untill end of the linked list
//for left pointer do left->next = left->next->next

ListNode* removeNthFromEnd(ListNode* head, int n) {

	if (!head || !head->next) return NULL;

	ListNode *preheader = new ListNode(-1);
	preheader->next = head;
	ListNode *left = preheader, *right = preheader;

	for (int i = 0; i < n; ++i) {
		right = right->next;
	}

	while (right->next) {
		left = left->next;
		right = right->next;
	}

	left->next = left->next->next;

	return preheader->next;

}

//delete a node in a linked list

void deleteNode(ListNode* node) {

	node->val = node->next->val;

	node->next = node ->next->next;
}

//numbers is represented as linked list add those numbers

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

	ListNode *preheader = new ListNode();
	ListNode *head = preheader;
	int sum ;
	int carry = 0;

	while (l1 && l2) {

		sum = l1->val + l2->val;
		sum += carry;
		carry = sum / 10;
		sum = sum % 10;

		ListNode *newNode = new ListNode(sum);
		head->next = newNode;
		head = head->next;
		l1 = l1->next;
		l2 = l2->next;
	}

	while (l1) {
		sum = l1->val + carry;
		carry = sum / 10;
		sum = sum % 10;

		ListNode *newNode = new ListNode(sum);
		head->next = newNode;
		head = head->next;
		l1 = l1->next;
	}

	while (l2) {
		sum = l2->val + carry;
		carry = sum / 10;
		sum = sum % 10;

		ListNode *newNode = new ListNode(sum);
		head->next = newNode;
		head = head->next;
		l2 = l2->next;
	}

	if (carry) {
		ListNode *newNode = new ListNode(carry);
		head->next = newNode;
		head = head->next;
	}
	return preheader->next;
}