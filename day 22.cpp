//convert bst to dll

//first say that we will create a new dll and do the inorder traversal of the bst and keep on adding
//nodes in dll

//say the recursive approach
//for each node its previous node is its inorder predesesor and its next node is its inorder successor
//so for each node make the required changes

Node *tree2list(Node *root) {

	if (!root) return NULL;

	if (root->left) {

		Node *l = tree2list(root->left);

		while (l->right) l = l->right;

		l->right = root;
		root->left = l;
	}
	if (root->right) {

		Node *r = tree2list(root->right);

		while (r->left) r = r->left;

		r->left = root;
		root->right = r;
	}

	return root;
}

public:
//Function to convert binary tree to doubly linked list and return it.
Node * bToDLL(Node *root)
{
	root = tree2list(root);
	while (root->left) root = root->left;
	return root;
}

//find the median of the stream of input data

//first tell that u will maintain an array and push new element to array and sort the array and return
//the middle element

//maintain 2 heaps one maxheap and other minheap push element to maxheap
//take out the max element of maxheap push it into the minheap
//if minheap's size is smaller than max heap's size push the smallest element from minheap to maxheap

priority_queue<int> maxheap;
priority_queue<int, vector<int>, greater<int>> minheap;

MedianFinder() {

	while (!minheap.empty()) minheap.pop();
	while (!maxheap.empty()) maxheap.pop();
}

void addNum(int num) {

	maxheap.push(num);
	int t = maxheap.top();
	maxheap.pop();
	minheap.push(t);

	if (maxheap.size() < minheap.size()) {
		t = minheap.top();
		minheap.pop();
		maxheap.push(t);
	}
}

double findMedian() {

	if (maxheap.size() > minheap.size()) return maxheap.top();

	double e1 = maxheap.top();
	double e2 = minheap.top();

	return (e1 + e2) / 2.0;
}

//kth largest element from a stream of input

//used minheap but first tell the sort approach

priority_queue<int, vector<int>, greater<int>> minheap;
int K;
KthLargest(int k, vector<int>& nums) {

	K = k;
	for (auto r : nums) minheap.push(r);

	while (minheap.size() > k) {
		minheap.pop();
	}
}

int add(int val) {

	minheap.push(val);
	if (minheap.size() > K) minheap.pop();
	return minheap.top();
}

//distinct elements in a window of size k

//first tell that for each window of size k we will calculate the distinct elements
//time 0(n^2)
//maintain a hashmap
//time 0(n) space 0(n)

vector<int> Solution::dNums(vector<int> &A, int B) {

	int n = A.size();
	if (n < B) return {};
	unordered_map<int, int> mp;

	for (int i = 0; i < B; ++i) mp[A[i]]++;
	vector<int> ans;

	ans.push_back(mp.size());

	for (int j = B; j < n; ++j) {

		mp[A[j - B]]--;
		if (mp[A[j - B]] == 0) mp.erase(A[j - B]);

		mp[A[j]]++;
		ans.push_back(mp.size());
	}
	return ans;
}

//kth largest element in an unsorted array

//use minheap

int findKthLargest(vector<int>& nums, int k) {

	priority_queue<int, vector<int>, greater<int>> minheap;
	for (auto e : nums) minheap.push(e);
	while (minheap.size() > k) minheap.pop();
	return minheap.top();
}

//we can also use the merge sort technique

int partition(vector<int>& nums, int l, int h) {

	int i = l - 1;
	int el = nums[h];
	for (int j = l; j < h; ++j) {
		if (nums[j] < el) {
			++i;
			swap(nums[i], nums[j]);
		}
	}
	swap(nums[i + 1], nums[h]);
	return i + 1;
}

public:
int findKthLargest(vector<int>& nums, int k) {

	int l = 0, h = nums.size() - 1;
	int n = nums.size();

	while (l <= h) {

		int p = partition(nums, l, h);
		if (p == n - k) return nums[p];

		else if (p < n - k) l = p + 1;
		else h = p - 1;
	}
	return -1;
}


//Flood fill algorithm

//do the bfs traversal on the grid

bool toColor(int x, int y, vector<vector<int>>& image, int oldColor) {

	if (x < 0 || y < 0 || x == image.size() || y == image[0].size() || image[x][y] !=                    oldColor) return false;
	return true;
}

public:
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {

	int oldColor = image[sr][sc];

	if (newColor == oldColor) return image;

	queue<pair<int, int>> q;
	q.push({sr, sc});
	image[sr][sc] = newColor;

	while (!q.empty()) {

		auto f = q.front();
		q.pop();

		int xdir[] = {0, 0, -1, 1};
		int ydir[] = { -1, 1, 0, 0};

		for (int i = 0; i < 4; ++i) {
			int xnew = f.first + xdir[i];
			int ynew = f.second + ydir[i];

			if (toColor(xnew, ynew, image, oldColor)) {
				q.push({xnew, ynew});
				image[xnew][ynew] = newColor;
			}
		}
	}
	return image;
}

