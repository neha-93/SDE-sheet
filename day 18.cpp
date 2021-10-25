
//In level order do not reverse the odd level nodes

//zig-zag traversal

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

	if (!root) return {};

	vector<vector<int>> ans;
	vector<int> level;
	queue<TreeNode*> q;

	q.push(root);
	int l = 0;

	while (!q.empty()) {

		int sz = q.size();
		level.clear();

		while (sz--) {

			root = q.front();
			level.push_back(root->val);
			q.pop();
			if (root->left) q.push(root->left);
			if (root->right) q.push(root->right);
		}
		if (l % 2) reverse(level.begin(), level.end());

		ans.push_back(level);
		l++;
	}
	return ans;
}

//height of binary tree

int height(struct Node* head) {

	if (!head) return 0;
	if (!head->right && !head->left) return 1;

	int left = 0, right = 0;
	if (head->left) left = height(head->left);
	if (head->right) right = height(head->right);

	return max(left, right) + 1;
}

//diameter of binary tree

//diameter at any node is the max of left diameter or right diameter or height of left subtree + height
//right subtree + 1

//time O(n^2)

int height(Node* root) {

	if (!root) return 0;

	int l = height(root->left);
	int r = height(root->right);

	return max(l, r) + 1;
}

public:
// Function to return the diameter of a Binary Tree.
int diameter(Node* root) {

	if (!root) return 0;

	int lh = height(root->left);
	int rh = height(root->right);

	int ld = diameter(root->left);
	int rd = diameter(root->right);

	return max(lh + rh + 1, max(ld, rd));
}

//we can reduce the time complexity by merging the 2 recursions of diameter and height into one

struct Node
{
	int data;
	struct Node* left;
	struct Node* right;

	Node(int x) {
		data = x;
		left = right = NULL;
	}
};

class Solution {

	int dia(Node* root, int& height) {

		if (!root) {
			height = 0;
			return 0;
		}
		int lh = 0, rh = 0;

		int ld = dia(root->left, lh);
		int rd = dia(root->right, rh);

		height = max(lh, rh) + 1;

		return max(lh + rh + 1, max(ld, rd));
	}

public:
	// Function to return the diameter of a Binary Tree.
	int diameter(Node* root) {

		int h = 0;
		return dia(root, h);
	}
};

//check if the tree is balanced or not

bool balanced(Node *root, int& h) {

	if (!root) {
		h = 0;
		return 1;
	}

	int lh = 0, rh = 0;

	bool isleft = balanced(root->left, lh);
	bool isRight = balanced(root->right, rh);

	h = max(lh, rh) + 1;

	if (abs(lh - rh) <= 1)
		return isleft && isRight;
	return false;

}

public:
//Function to check whether a binary tree is balanced or not.
bool isBalanced(Node *root)
{
	int h = 0;
	return balanced(root, h);
}

//lca of two nodes in a binary tree

//a node is lca if it is either of the 2 nodes or one of the two nodes is left child and another
//one is the right child.

Node* lca(Node* root , int n1 , int n2 )
{
	if (!root) return NULL;

	if (root->data == n1 || root->data == n2) return root;

	Node *left_lca = lca(root->left, n1, n2);
	Node *right_lca = lca(root->right, n1, n2);

	if (left_lca && right_lca) return root;

	return left_lca ? left_lca : right_lca;
}


//check if 2 trees are same or not

bool isSameTree(TreeNode* p, TreeNode* q) {

	if (!p && !q) return true;
	if (!p || !q) return false;

	if (p->val != q->val) return false;

	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}





