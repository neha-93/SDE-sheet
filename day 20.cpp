//populating next right pointer in each node

//recursive solution

Node* connect(Node* root) {

	if (!root) return NULL;

	if (root->left) {
		root->left->next = root->right;
		if (root->next) root->right->next = root->next->left;
	}

	connect(root->left);
	connect(root->right);

	return root;
}

//using the concept of level order traversal

Node* connect(Node* root) {

	if (!root) return NULL;

	queue<Node*> q;
	q.push(root);

	while (!q.empty()) {

		int sz = q.size();

		while (sz--) {

			auto f = q.front();
			q.pop();
			Node *s;
			if (sz) s = q.front();
			else s = NULL;
			f->next = s;
			if (f->left) q.push(f->left);
			if (f->right) q.push(f->right);
		}
	}
	return root;
}


//Search for a key in a Binary Search Tree

TreeNode* searchBST(TreeNode* root, int val) {

	if (!root) return NULL;

	if (root->val == val) return root;
	if (root->val < val) return searchBST(root->right, val);
	return searchBST(root->left, val);
}


//creating a bst from given keys

#include <bits/stdc++.h>
using namespace std;

class TreeNode {

public:
	int val;
	TreeNode *left, *right;

	TreeNode(int v): val(v), left(NULL), right(NULL) {}
};

TreeNode* addNode(TreeNode *root, int val) {

	if (!root) {
		TreeNode *node = new TreeNode(val);
		return node;
	}
	if (root->val <= val) root->right = addNode(root->right, val);
	else root->left = addNode(root->left, val);

	return root;
}

void inorder(TreeNode *root) {

	if (!root) return;
	inorder(root->left);
	cout << root->val << " ";
	inorder(root->right);
}

int main() {

	int n;
	cin >> n;
	int a[n];
	for (int i = 0; i < n; ++i) cin >> a[i];

	TreeNode *root = new TreeNode(a[0]);

	for (int i = 1; i < n; ++i) {

		addNode(root, a[i]);
	}
	inorder(root);
	return 0;
}

//Build Tree from preorder traversal

TreeNode* build(vector<int>& pre, int s, int e) {

	if (s > e) return NULL;
	int rootData = pre[s];
	int rs = -1;

	for (int i = s; i <= e; ++i) {
		if (pre[i] > rootData) {
			rs = i;
			break;
		}
	}
	TreeNode *root = new TreeNode(rootData);

	if (rs != -1) {
		root->left = build(pre, s + 1, rs - 1);
		root->right = build(pre, rs, e);
	}
	else root->left = build(pre, s + 1, e);

	return root;
}

public:
TreeNode* bstFromPreorder(vector<int>& preorder) {

	return build(preorder, 0, preorder.size() - 1);
}


//valid bst

//modify the iterative in order traversal to check if the previous nodes value is always less than
//the current nodes value

bool isValidBST(TreeNode* root) {

	if (!root) return true;

	stack<TreeNode*> st;
	TreeNode *prev = NULL;

	while (!st.empty() || root) {

		if (root) {
			st.push(root);
			root = root->left;
		}
		else {
			root = st.top();
			st.pop();
			if (prev && prev->val >= root->val) return false;
			prev = root;
			root = root->right;
		}
	}
	return true;
}

//recursive approach

bool isValid(Node* root, Node* minNode, Node* maxNode) {

	if (!root) return true;
	if ((minNode && root->data <= minNode->data) || (maxNode && root->data >= maxNode->data)) return false;
	return isValid(root->left, minNode, root) && isValid(root->right, root, maxNode);
}
public:
//Function to check whether a Binary Tree is BST or not.
bool isBST(Node* root)
{
	return isValid(root, NULL, NULL);
}

//LCA of a bst

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

	if (!root) return NULL;
	while ((p->val - root->val) * (q->val - root->val) > 0) {
		root = p->val < root->val ? root->left : root->right;
	}
	return root;
}

//Find the inorder successor and predecessor of the key in a bst

void findPreSuc(Node* root, Node*& pre, Node*& suc, int key)
{
	if (!root) return;

	if (root->key < key) {
		if (!pre) pre = root;
		else if (pre->key < root->key) pre = root;
	}
	if (root->key > key) {
		if (!suc) suc = root;
		else if (suc->key > root->key) suc = root;
	}

	findPreSuc(root->left, pre, suc, key);
	findPreSuc(root->right, pre, suc, key);

}
