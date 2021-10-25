//all permutation of a string

void allPermute(vector<int>& nums, int s, vector<vector<int>>& ans) {

	if (s == nums.size()) {
		ans.push_back(nums);
		return;
	}

	for (int i = s; i < nums.size(); ++i) {

		swap(nums[s], nums[i]);
		allPermute(nums, s + 1, ans);
		swap(nums[s], nums[i]);
	}
}

public:
vector<vector<int>> permute(vector<int>& nums) {

	vector<vector<int>> ans;
	allPermute(nums, 0, ans);
	return ans;
}


//N Queen problem

bool isValid(int r, int c, int n, vector<string>& pos) {

	for (int i = 0; i < n; ++i) {
		if (r != i && pos[i][c] == 'Q') return false;
		if (c != i && pos[r][i] == 'Q') return false;
	}

	for (int i = r + 1, j = c + 1; i < n && j < n; ++i, ++j) {
		if (pos[i][j] == 'Q') return false;
	}
	for (int i = r - 1, j = c - 1; i >= 0 && j >= 0; --i, --j) {
		if (pos[i][j] == 'Q') return false;
	}
	for (int i = r + 1, j = c - 1; i < n && j >= 0; ++i, --j) {
		if (pos[i][j] == 'Q') return false;
	}
	for (int i = r - 1, j = c + 1; i >= 0 && j < n; --i, ++j) {
		if (pos[i][j] == 'Q') return false;
	}

	return true;
}

void solve(vector<string>& pos, int r, int n, vector<vector<string>>& ans) {

	if (r == n) {
		ans.push_back(pos);
		return;
	}

	for (int i = 0; i < n; ++i) {
		if (isValid(r, i, n, pos)) {
			pos[r][i] = 'Q';
			solve(pos, r + 1, n, ans);
			pos[r][i] = '.';
		}
	}
}


public:
vector<vector<string>> solveNQueens(int n) {

	vector<vector<string>> ans;

	vector<string> position(n, string(n, '.'));

	solve(position, 0, n, ans);

	return ans;
}

//M graph coloring problem

//for each node color the node if it could be colored and continue till all nodes are colored

bool possible(int node, vector<int>& color, int c, int n, bool graph[101][101]) {

	for (int i = 0; i < n; ++i) {
		if (i != node && graph[node][i] && color[i] == c) return false;
	}
	return true;
}

bool solve(int node, vector<int>& color, int m, int n, bool graph[101][101]) {

	if (node == n) return true;

	for (int i = 1; i <= m; ++i) {

		if (possible(node, color, i, n, graph)) {
			color[node] = i;
			if (solve(node + 1, color, m, n, graph)) return true;
			color[node] = 0;
		}
	}
	return false;
}

bool graphColoring(bool graph[101][101], int m, int V)
{
	vector<int> color(V, 0);
	return solve(0, color, m, V, graph);
}

//Rat in a maze

//from 0 go to all 4 directions if it is safe and if we reach the destination add the path to answer
//else backtrack

bool safe(vector<vector<int>>& m, int i, int j, int n) {

	if (i < 0 || j < 0 || i == n || j == n) return false;
	if (m[i][j] == 0) return false;
	return true;
}

void paths(vector<vector<int>>& m, string p, int i, int j, int n,
           vector<string>& ans, vector<vector<int>>& vis) {

	if (!safe(m, i, j, n) || vis[i][j]) return;

	if (i == n - 1 && j == n - 1) {
		ans.push_back(p);
		return;
	}

	vis[i][j] = 1;
	paths(m, p + 'D', i + 1, j, n, ans, vis);
	paths(m, p + 'L', i, j - 1, n, ans, vis);
	paths(m, p + 'R', i, j + 1, n, ans, vis);
	paths(m, p + 'U', i - 1, j, n, ans, vis);
	vis[i][j] = 0;
}


public:
vector<string> findPath(vector<vector<int>> &m, int n) {

	vector<string> ans;
	string p;
	vector<vector<int>> vis(n, vector<int>(n, 0));

	paths(m, p, 0, 0, n, ans, vis);

	return ans;

}

//word break baki h trie wala solution tle de raha tha and dp wala bad me karenge.
