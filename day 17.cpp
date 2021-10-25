//inorder tree traversal

//recursive solution

void inorder(TreeNode* root, vector<int>& ans) {

	if (!root) return;

	inorder(root->left, ans);
	ans.push_back(root->val);
	inorder(root->right, ans);
}

public:
vector<int> inorderTraversal(TreeNode* root) {

	vector<int> ans;
	inorder(root, ans);
	return ans;

}

//iterative solution

vector<int> inorderTraversal(TreeNode* root) {

	stack<TreeNode*> st;
	vector<int> ans;

	if (!root) return ans;

	while (!st.empty() || root) {

		if (root) {
			st.push(root);
			root = root->left;
		}
		else {
			root = st.top();
			st.pop();
			ans.push_back(root->val);
			root = root->right;
		}
	}

	return ans;
}

//preorder traversal

//iterative solution

void pre(TreeNode* root, vector<int>& ans) {

	if (!root) return;
	ans.push_back(root->val);
	pre(root->left, ans);
	pre(root->right, ans);
}

public:
vector<int> preorderTraversal(TreeNode* root) {

	vector<int> ans;
	pre(root, ans);
	return ans;
}

//iterative solution

vector<int> preorderTraversal(TreeNode* root) {

	if (!root) return {};
	vector<int> ans;
	stack<TreeNode*> st;

	while (!st.empty() || root) {

		if (root) {
			ans.push_back(root->val);
			st.push(root);
			root = root->left;
		}
		else {
			root = st.top();
			st.pop();
			root = root->right;
		}
	}
	return ans;
}

//posorder traversal

//recursive solution

void post(TreeNode* root, vector<int>& ans) {

	if (!root) return;
	post(root->left, ans);
	post(root->right, ans);
	ans.push_back(root->val);
}

public:
vector<int> postorderTraversal(TreeNode* root) {

	vector<int> ans;
	post(root, ans);
	return ans;
}

//iterative solution

vector<int> postorderTraversal(TreeNode* root) {

	if (!root) return {};
	vector<int> ans;
	stack<TreeNode*> st;
	st.push(root);

	while (!st.empty()) {

		root = st.top();
		st.pop();
		ans.push_back(root->val);
		if (root->left)st.push(root->left);
		if (root->right) st.push(root->right);

	}
	reverse(ans.begin(), ans.end());
	return ans;

}

//left view of binary tree

//level order traversal , print the first node of each level

vector<int> leftView(Node *root)
{
	// Your code here
	if (!root) return {};
	vector<int> ans;

	queue<Node*> q;
	q.push(root);

	while (!q.empty()) {

		int sz = q.size();
		int n = sz;

		while (sz--) {
			root = q.front();
			q.pop();
			if (n == sz + 1) ans.push_back(root->data);

			if (root->left) q.push(root->left);
			if (root->right) q.push(root->right);
		}

	}
	return ans;
}

//Bottom view of binary tree

vector <int> bottomView(Node *root) {
	// Your Code Here
	if (!root) return {};

	vector<int> ans;
	map<int, int> mp;
	queue<pair<Node*, int>> q;

	q.push({root, 0});

	while (!q.empty()) {

		auto f = q.front();
		q.pop();
		mp[f.second] = f.first->data;

		if (f.first->left) q.push({f.first->left, f.second - 1});
		if (f.first->right) q.push({f.first->right, f.second + 1});

	}
	for (auto k : mp) {
		ans.push_back(k.second);
	}
	return ans;
}

//top view of binary tree

vector<int> topView(Node *root)
{

	vector<int> ans;

	queue<pair<Node*, int>> q;
	map<int, int> mp;

	if (!root) return ans;
	q.push({root, 0});

	while (!q.empty()) {

		auto f = q.front();
		q.pop();
		if (!mp[f.second]) mp[f.second] = f.first->data;

		if (f.first->left) q.push({f.first->left, f.second - 1});
		if (f.first->right) q.push({f.first->right, f.second + 1});
	}

	for (auto k : mp) {
		ans.push_back(k.second);
	}
	return ans;
}