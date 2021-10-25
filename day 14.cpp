//Previous smaller element

//say the n^2 approach for every element check left half for smaller elements

//then say the stack approach


vector<int> Solution::prevSmaller(vector<int> &A) {

	stack<int> st;
	int n = A.size();
	vector<int> g(n);

	for (int i = 0; i < A.size(); ++i) {

		while (!st.empty() && st.top() >= A[i]) st.pop();
		if (st.empty()) g[i] = -1;
		else g[i] = st.top();

		st.push(A[i]);

	}
	return g;
}

//LRU cache

//O(1) get and O(1) put
//used doubly linked list + hashmap

class LRUCache {
public:
	class node {

	public:
		int key, val;
		node *prev, *next;

		node (int _key, int _val) {
			key = _key;
			val = _val;
		}
	};

	int cap;
	unordered_map<int, node*> m;

	node *head = new node(-1, -1);
	node *tail = new node(-1, -1);

	LRUCache(int capacity) {
		cap = capacity;

		head->next = tail;
		tail->prev = head;
	}

	void addNode(int key_, int val_) {

		node *temp = new node(key_, val_);
		node *nx = head->next;
		head->next = temp;
		nx->prev = temp;
		temp->next = nx;
		temp->prev = head;
	}

	void deleteNode(node *d) {

		node *delprev = d->prev;
		node *delnext = d->next;

		delprev->next = delnext;
		delnext->prev = delprev;
	}

	int get(int key) {

		if (m.find(key) != m.end()) {

			int v = m[key]->val;
			deleteNode(m[key]);
			addNode(key, v);
			m[key] = head->next;
			return v;
		}
		return -1;
	}

	void put(int key, int value) {

		if (m.find(key) != m.end()) {

			deleteNode(m[key]);
		}
		else if (cap == m.size()) {
			m.erase(tail->prev->key);
			deleteNode(tail-> prev);
		}

		addNode(key, value);
		m[key] = head->next;
	}
};


//largest histogram

//2 pass solution
//1st pass find the left smaller element
//2nd pass find the right smaller element and update to get the size of largest histogram

int largestRectangleArea(vector<int>& heights) {

	int n = heights.size();
	vector<int> leftSmall(n), rightSmall(n);

	stack<pair<int, int>> st, st2;

	for (int i = 0; i < n; ++i) {

		while (!st.empty() && st.top().second >= heights[i]) st.pop();

		if (st.empty()) leftSmall[i] = 0;
		else leftSmall[i] = st.top().first + 1;

		st.push({i, heights[i]});

	}

	int ans = 0;

	for (int i = n - 1; i >= 0; --i) {

		while (!st2.empty() && st2.top().second >= heights[i]) st2.pop();

		if (st2.empty()) rightSmall[i] = n - 1;
		else rightSmall[i] = st2.top().first - 1;

		ans = max(ans, heights[i] * (rightSmall[i] - leftSmall[i] + 1));

		st2.push({i, heights[i]});
	}

	return ans;

}

//one pass solution

int largestRectangleArea(vector<int>& heights) {

	int n = heights.size();
	int ans = 0;

	stack<int> st;

	for (int i = 0; i <= n; ++i) {

		while (!st.empty() && (i == n || heights[st.top()] >= heights[i])) {

			int height = heights[st.top()];
			st.pop();

			int width;
			if (st.empty()) width = i;
			else width = i - st.top() - 1;

			ans = max(ans, height * width);
		}
		st.push(i);
	}
	return ans;
}

//sliding window maximum

//first tell that for i=0 -> i-k for each i we will find the maximum and push it to the ans

//then tell the deque approach where we will maintain the deque in decreasing sequence

vector<int> maxSlidingWindow(vector<int>& nums, int k) {

	vector<int> ans;
	deque<int> dq;

	int n = nums.size();

	for (int i = 0; i < n; ++i) {

		if (!dq.empty() && dq.front() <= i - k) dq.pop_front();

		while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
		dq.push_back(i);

		if (i >= k - 1) ans.push_back(nums[dq.front()]);

	}
	return ans;
}

//Min stack

//we can store pair in the stack first element the number and second the minimum till now

//we can store numbers in the stack and if we incounter a new min we cal get the previous minimum by
//the modified value stored in the stack

#define ll long long

class MinStack {
public:
	/** initialize your data structure here. */

	ll minn;
	stack<ll> st;


	MinStack() {
		while (!st.empty()) st.pop();
		minn = INT_MAX;
	}

	void push(int value) {

		ll val = value;
		if (st.empty()) {
			st.push(val);
			minn = val;
		}
		else {
			if (minn <= val) st.push(val);
			else {
				minn = val;
				st.push(2 * val * 1LL - minn);
			}
		}
	}

	void pop() {

		if (st.empty()) return;
		ll el = st.top();
		st.pop();

		if (el < minn) {
			minn = 2 * minn - el;
		}
	}

	int top() {

		if (st.empty()) return -1;
		ll el = st.top();

		if (el < minn) return minn;
		return el;
	}

	int getMin() {
		return minn;
	}
};

//Rotten oranges use bfs

bool valid(int x, int y, vector<vector<int>>& grid) {

	if (x < 0 || y < 0 || x == grid.size() || y == grid[0].size() || grid[x][y] != 1) return false;
	return true;
}

public:
int orangesRotting(vector<vector<int>>& grid) {

	int oranges = 0, rotten = 0;

	queue<vector<int>> q;

	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[0].size(); ++j) {

			if (grid[i][j] == 2) {
				rotten++;
				oranges++;
				q.push({i, j, 0});
			}
			else if (grid[i][j] == 1) oranges++;
		}
	}

	while (!q.empty()) {

		auto f = q.front();
		q.pop();
		int x = f[0], y = f[1], l = f[2];

		if (rotten == oranges) return l;

		int dirx[] = {0, 0, 1, -1};
		int diry[] = {1, -1, 0, 0};

		for (int i = 0; i < 4; ++i) {
			int nx = x + dirx[i];
			int ny = y + diry[i];
			if (valid(nx, ny, grid)) {
				grid[nx][ny] = 2;
				rotten++;
				q.push({nx, ny, l + 1});
			}
		}
	}

	return -1;
}


//stock span problem

//here we basically need to calculate the previous greater element use stack to find and maintain the
//stack in decreasing order.

vector <int> calculateSpan(int price[], int n)
{
	vector<int> pge(n);

	pge[0] = 1;
	stack<int> st;
	st.push(0);
	int ind;

	for (int i = 1; i < n; ++i) {

		while (!st.empty() && price[st.top()] <= price[i]) st.pop();

		if (st.empty()) pge[i] = i + 1;
		else pge[i] = i - st.top();

		st.push(i);
	}
	return pge;
}

//find the maximum of minimums of window of each size

//find the next smaller and previous smaller elements

vector <int> maxOfMin(int arr[], int n)
{
	vector<int> right(n), left(n);

	stack<int> st;

	for (int i = 0; i < n; ++i) {

		while (!st.empty() && arr[st.top()] >= arr[i]) st.pop();

		if (st.empty()) left[i] = -1;
		else left[i] = st.top();

		st.push(i);
	}

	while (!st.empty()) st.pop();

	for (int i = n - 1; i >= 0; --i) {

		while (!st.empty() && arr[st.top()] >= arr[i]) st.pop();

		if (st.empty()) right[i] = n;
		else right[i] = st.top();

		st.push(i);
	}

	int len;
	vector<int> ans(n);

	for (int i = 0; i < n; ++i) {

		len = right[i] - left[i] - 1;
		ans[len - 1] = max(ans[len - 1], arr[i]);
	}

	for (int i = n - 2; i > 0; --i) ans[i] = max(ans[i + 1], ans[i]);

	return ans;
}

//The celebrity problem

//use two pointer approach if i knows j, i cant be celeb else j cant be celeb
//at last check for i that it doesnt knows anyone and everyone knows him

//time O(N) and space O(1)

int celebrity(vector<vector<int> >& M, int n)
{
	int i = 0, j = n - 1;

	while (i < j) {

		if (M[i][j]) i++;
		else j--;
	}

	for (int k = 0; k < n; ++k) {
		if (M[i][k]) return -1;
		if (M[k][i] == 0 && k != i) return -1;
	}

	return i;
}

//we can also use stack
//push all elements into stack pop 2 elements and push element which can be celeb
//untill a single element remains in the stack

//for the remaining element check if it is celeb or not

//time O(N) and space O(N)