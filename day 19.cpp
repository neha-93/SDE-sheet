//Binary tree maximum path sum

int maxi(TreeNode* root, int& res) {

	if (!root) return 0;

	int lm = maxi(root->left, res);
	int rm = maxi(root->right, res);

	int single_max = max(max(lm, rm) + root->val, root->val);

	int top_max = max(single_max, lm + rm + root->val);
	res = max(top_max, res);

	return single_max;
}

public:
int maxPathSum(TreeNode* root) {

	int res = INT_MIN;
	maxi(root, res);
	return res;
}

//Build tree from preorder and inorder tree traversals

TreeNode* build(vector<int>& pre, vector<int>& in, int preS, int preE, int inS, int inE) {

	if (inS > inE) return NULL;

	int rootInd = -1;
	int rootData = pre[preS];

	for (int i = inS; i <= inE; ++i) {
		if (in[i] == rootData) {
			rootInd = i;
			break;
		}
	}

	int inLS = inS;
	int inLE = rootInd - 1;
	int inRS = rootInd + 1;
	int inRE = inE;
	int preLS = preS + 1;
	int preLE = inLE - inLS + preLS;
	int preRS = preLE + 1;
	int preRE = preE;

	TreeNode *root = new TreeNode(rootData);
	root->left = build(pre, in, preLS, preLE, inLS, inLE);
	root->right = build(pre, in, preRS, preRE, inRS, inRE);

	return root;
}

public:
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {

	int n = preorder.size();
	return build(preorder, inorder, 0, n - 1, 0, n - 1);
}

//build tree from inorder and postorder tree traversal

TreeNode* build(vector<int>& in, vector<int>& post, int inS, int inE, int postS, int postE) {

	if (inS > inE) return NULL;

	int rootInd = -1;
	int rootData = post[postE];

	for (int i = inS; i <= inE; ++i) {
		if (rootData = in[i]) {
			rootInd = i;
			break;
		}
	}

	int inLS = inS + 1;
	int inLE = rootInd - 1;
	int inRS = rootInd + 1;
	int inRE = inE;
	int postLS = postS;
	int postLE = inLE - inLS + postLS;
	int postRS = postLE + 1;
	int postRE = postE;

	TreeNode* root = new TreeNode(rootData);
	root->left = build(in, post, inLS, inLE, postLS, postLE);
	root->right = build(in, post, inRS, inRE, postRS, postRE);

	return root;
}

public:
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {

	int n = inorder.size();
	return build(inorder, postorder, 0, n - 1, 0, n - 1);
}

//symmetric tree /tree is a mirror image of itself

int Solution::isSymmetric(TreeNode* root) {

	if (!root) return 1;

	queue<pair<TreeNode*, TreeNode*>> q;
	q.push({root->left, root->right});

	while (!q.empty()) {

		auto f = q.front();
		q.pop();
		if (!f.first && !f.second) continue;
		if (!f.first || !f.second) return 0;
		if (f.first->val != f.second->val) return 0;

		q.push({f.first->left, f.second->right});
		q.push({f.first->right, f.second->left});
	}

	return 1;
}

//flattening of binary tree

//it the tree has both left child and right child go to the rightmost child of left child of root
//node and make it right point to root->right and make root left child its right and root->left as
//null

//if the node has leftnode only the make the left node its right

//repeat till we reach the rightmost node of the tree

void flatten(TreeNode* root) {

	while (root) {

		if (root->left && root->right) {

			TreeNode *t = root->left;
			while (t->right) t = t->right;
			t->right = root->right;
		}
		if (root->left) root->right = root->left;
		root->left = NULL;
		root = root->right;
	}
}

