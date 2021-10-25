//floor and ceil of a bst

void floorCeilBSTHelper(Node* root, int key, int& floor, int& ceil)
{

	while (root) {

		if (root->data == key) {
			ceil = root->data;
			floor = root->data;
			return;
		}

		if (key > root->data) {
			floor = root->data;
			root = root->right;
		}
		else {
			ceil = root->data;
			root = root->left;
		}
	}
	return;
}

//kth smallest element in bst

//do the inorder traversal of bst and store the elements in an array and return the k-1th element
//of the array

int kthSmallest(TreeNode* root, int k) {

	if (!root) return -1;

	stack<TreeNode*> st;

	while (!st.empty() || root) {

		if (root) {
			st.push(root);
			root = root->left;
		}
		else {
			root = st.top();
			st.pop();
			if (--k == 0) return root->val;
			root = root->right;
		}
	}
	return -1;
}


//we can use recursion

int count(TreeNode* root) {

	if (!root) return 0;
	return 1 + count(root->left) + count(root->right);
}

public:
int kthSmallest(TreeNode* root, int k) {

	if (!root) return -1;
	int cnt = count(root->left);

	if (k <= cnt) return kthSmallest(root->left, k);
	else if (k > cnt + 1) return kthSmallest(root->right, k - cnt - 1);

	return root->val;
}

//Kth largest element in bst

//reverse inorder traversal

int kthLargest(Node *root, int K)
{
	if (!root) return -1;

	stack<Node*> st;

	while (!st.empty() || root) {

		if (root) {
			st.push(root);
			root = root->right;
		}
		else {
			root = st.top();
			st.pop();
			if (--K == 0) return root->data;
			root = root->left;
		}
	}
	return -1;
}

//two sum in bst

//we can do inorder tree traversal and then use two pointers

//we can use unordered_set to store node values and do recursive tree traversal and if we get
//k-root->val already return true

bool twoSum(TreeNode* root, unordered_set<int>& set, int k) {

	if (!root) return false;
	if (set.count(k - root->val)) return true;
	set.insert(root->val);

	return twoSum(root->left, set, k) || twoSum(root->right, set, k);
}

public:
bool findTarget(TreeNode* root, int k) {

	unordered_set<int> set;
	return twoSum(root, set, k);
}

//BST iterator

//basically a modified form of inorder tree traversal

stack<TreeNode*> s;

void pushx(TreeNode *root) {
	while (root) {
		s.push(root);
		root = root->left;
	}
}

public:
BSTIterator(TreeNode* root) {
	pushx(root);
}

int next() {

	TreeNode *nex = s.top();
	s.pop();
	pushx(nex->right);
	return nex->val;

}

bool hasNext() {
	return !s.empty();
}

//largest bst in a binary tree

//in the bottom up manner check if for every node its inorder predesesor is smaller than it and
//its inorder successor is greater than it if it is update ans else pass the previous greatest
//answer

struct Info {
	int min, max, ans;
	bool isBST;
};

Info largest(Node* root) {

	if (!root) return {INT_MAX, INT_MIN, 0, true};
	if (!root->left && !root->right) return {root->data, root->data, 1, true};

	Info l = largest(root->left);
	Info r = largest(root->right);

	Info cur;

	if (l.isBST && r.isBST && l.max < root->data && r.min > root->data) {

		cur.ans = l.ans + r.ans + 1;
		cur.min = min(l.min, min(root->data, r.min));
		cur.max = max(l.max, max(root->data, r.max));
		cur.isBST = true;

		return cur;
	}

	cur.ans = max(l.ans, r.ans);
	cur.isBST = false;

	return cur;
}


int largestBst(Node *root)
{
	return largest(root).ans;
}

//deserialize and serialize a binary tree

//did the perorder serialization

int findVal(string& data) {

	int pos = data.find(',');
	string el = data.substr(0, pos);
	data = data.substr(pos + 1);
	return stoi(el);
}

TreeNode* mydeserialize(string& data) {

	if (data[0] == '#') {
		if (data.size() > 1) data = data.substr(2);
		return NULL;
	}
	TreeNode *root = new TreeNode(findVal(data));
	root->left = mydeserialize(data);
	root->right = mydeserialize(data);

	return root;
}

public:

// Encodes a tree to a single string.
string serialize(TreeNode* root) {

	if (!root) return "#";
	return to_string(root->val) + ',' + serialize(root->left) + ',' + serialize(root->right);
}

// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
	return mydeserialize(data);
}