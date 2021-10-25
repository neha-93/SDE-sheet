//Implement stack using arrays

#include <bits/stdc++.h>
using namespace std;

class MyStack {

private:
	int arr[1000];
	int top;

public:
	MyStack() {
		top = -1;
	}
	int pop();
	void push(int);
};

int MyStack :: pop() {

	if (top == -1) return -1;
	return arr[top--];
}

void MyStack :: push(int x) {
	arr[++top] = x;
}

int main() {

	int t;
	cin >> t;
	MyStack *s = new MyStack();
	while (t--) {
		int ty, num;
		cin >> ty;
		if (ty == 1) {
			cin >> num;
			s->push(num);
		}
		else {
			cout << s->pop() << endl;
		}
	}
	return 0;
}

//Implement Queue using array

#include <bits/stdc++.h>
using namespace std;

class Queue {
private:
	int a[1000];
	int c;
	int cnt, rear, front;

public:
	Queue() {
		front = rear = cnt = 0;
		c = 1000;
	}
	void push(int);
	int top();
	int pop();
	int size();
};

void Queue::push(int x) {

	if (cnt == c) {
		cout << "Over flow\n";
		return;
	}
	a[rear % c] = x;
	rear++;
	cnt++;
}

int Queue::top() {

	//cout << front << " " << rear << endl;
	if (front == rear) return -1;
	return a[front % c];
}

int Queue::pop() {

	//cout << front << " " << rear << endl;
	if (front == rear) return -1;
	int el = a[front % c];
	front++;
	cnt--;
	return el;
}

int Queue::size() {
	return cnt;
}

int main() {
	int t;
	cin >> t;
	Queue *q = new Queue();

	while (t--) {
		int type, el;
		cin >> type;

		if (type == 1) {
			cin >> el;
			q->push(el);
		}
		else if (type == 2) {
			cout << q->top() << endl;
		}
		else if (type == 3) {
			cout << q->pop() << endl;
		}
		else cout << q->size() << endl;
	}
	return 0;
}

//Implement stack using queue

//using a single queue
class MyStack {
public:
	/** Initialize your data structure here. */
	MyStack() {

	}
	queue<int> q;
	/** Push element x onto stack. */
	void push(int x) {

		q.push(x);

		int sz = q.size();

		for (int i = 1; i < sz; ++i) {

			int f = q.front();
			q.pop();
			q.push(f);
		}
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {

		int t = q.front();
		q.pop();
		return t;
	}

	/** Get the top element. */
	int top() {

		return q.front();
	}

	/** Returns whether the stack is empty. */
	bool empty() {

		return q.empty();
	}
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

//using 2 queues

//add x to q2
//move all elements frim q1 to q2
//swap q1 and q2


class MyStack {
public:
	/** Initialize your data structure here. */
	MyStack() {

	}
	queue<int> q1, q2;
	/** Push element x onto stack. */
	void push(int x) {

		q2.push(x);
		while (!q1.empty()) {
			q2.push(q1.front());
			q1.pop();
		}

		while (!q2.empty()) {
			q1.push(q2.front());
			q2.pop();
		}
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {

		int t = q1.front();
		q1.pop();
		return t;
	}

	/** Get the top element. */
	int top() {
		return q1.front();
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return q1.empty();
	}
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

//Implement stack using queues

//O(N) solution

MyQueue() {

}
stack<int> s1, s2;
/** Push element x to the back of queue. */
void push(int x) {

	while (!s1.empty()) {
		s2.push(s1.top());
		s1.pop();
	}
	s2.push(x);

	while (!s2.empty()) {
		s1.push(s2.top());
		s2.pop();
	}

}

/** Removes the element from in front of queue and returns that element. */
int pop() {
	int t = s1.top();
	s1.pop();
	return t;
}

/** Get the front element. */
int peek() {
	return s1.top();
}

/** Returns whether the queue is empty. */
bool empty() {
	return s1.empty();
}

//amotized O(1) solution

class MyQueue {
public:
	/** Initialize your data structure here. */
	MyQueue() {

	}
	stack<int> s1, s2;
	/** Push element x to the back of queue. */
	void push(int x) {

		s1.push(x);
	}

	/** Removes the element from in front of queue and returns that element. */
	int pop() {

		if (empty()) return -1;
		if (s2.empty()) {
			while (!s1.empty()) {
				s2.push(s1.top());
				s1.pop();
			}
		}
		int t = s2.top();
		s2.pop();
		return t;
	}

	/** Get the front element. */
	int peek() {

		if (s2.empty()) {
			while (!s1.empty()) {
				s2.push(s1.top());
				s1.pop();
			}
		}
		return s2.top();
	}

	/** Returns whether the queue is empty. */
	bool empty() {
		if (s1.empty() && s2.empty()) return true;
		return false;
	}
};

//Balanced paranthesis

//time O(N) and space O(N)

bool isValid(string s) {

	stack<char> st;

	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '[' || s[i] == '(' || s[i] == '{') st.push(s[i]);
		else if (!st.empty()) {

			if (s[i] == ']' && st.top() == '[') {
				st.pop();
			}
			else if (s[i] == '}' && st.top() == '{') {
				st.pop();
			}
			else if (s[i] == ')' && st.top() == '(') {
				st.pop();
			}
			else return false;
		}

		else return false;
	}

	if (st.empty()) return true;
	return false;
}

//next greater element

//first tell the O(n^2) approch say for every element we will check the left half for the next greater
//element

//tell the stack approach

vector<int> nextGreaterElements(vector<int>& nums) {

	int n = nums.size();
	vector<int> nge(n);

	stack<int> st;

	for (int i = 2 * n - 1; i >= 0; --i) {

		while (!st.empty() && st.top() <= nums[i % n]) {
			st.pop();
		}
		if (i < n) {
			if (!st.empty()) nge[i] = st.top();
			else nge[i] = -1;
		}
		st.push(nums[i % n]);
	}
	return nge;

}

//sort a stack

//used recursion


void sortedInsert(stack<int>& s, int ele) {

	if (s.empty()) {
		s.push(ele);
		return;
	}
	if (s.top() <= ele) {
		s.push(ele);
	}
	else {
		int temp = s.top();
		s.pop();
		sortedInsert(s, ele);
		s.push(temp);
	}
}

void SortedStack :: sort()
{
	if (s.empty()) return;

	int temp = s.top();
	s.pop();
	sort();
	sortedInsert(s, temp);

}

