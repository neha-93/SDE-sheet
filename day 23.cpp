//clone a graph


//first clone all the nodes by traversing through the graph
//and in the next traversal copy the edges

class Node {
public:
	int val;
	vector<Node*> neighbors;
	Node() {
		val = 0;
		neighbors = vector<Node*>();
	}
	Node(int _val) {
		val = _val;
		neighbors = vector<Node*>();
	}
	Node(int _val, vector<Node*> _neighbors) {
		val = _val;
		neighbors = _neighbors;
	}
};


class Solution {
public:
	Node* cloneGraph(Node* node) {

		if (!node) return NULL;
		unordered_map<Node*, bool> vis;

		unordered_map<Node*, Node*> cloned;

		cloned[node] = new Node(node->val);
		vis[node] = true;
		queue<Node*> q;
		q.push(node);

		while (!q.empty()) {

			Node *f = q.front();
			q.pop();
			for (auto k : f->neighbors) {

				if (!vis[k]) {
					cloned[k] = new Node(k->val);
					vis[k] = true;
					q.push(k);
				}
			}
		}

		vis.clear();
		q.push(node);
		vis[node] = true;

		while (!q.empty()) {

			Node *f = q.front();
			q.pop();
			for (auto k : f->neighbors) {
				cloned[f]->neighbors.push_back(cloned[k]);
				if (!vis[k]) {
					vis[k] = true;
					q.push(k);
				}

			}
		}

		return cloned[node];

	}
};

//dfs traversal of a graph

void dfs(int node, vector<bool>& vis, vector<int> adj[], vector<int>& ans) {

	vis[node] = true;
	ans.push_back(node);

	for (auto k : adj[node]) {
		if (!vis[k]) dfs(k, vis, adj, ans);
	}
}


public:
// Function to return a list containing the DFS traversal of the graph.
vector<int> dfsOfGraph(int V, vector<int> adj[]) {

	vector<int> ans;
	vector<bool> vis(V, false);

	for (int i = 0; i < V; ++i) {
		if (!vis[i]) {
			dfs(i, vis, adj, ans);
		}
	}

	return ans;
}


//bfs traversal of a graph

vector<int> bfsOfGraph(int V, vector<int> adj[]) {

	vector<int> ans;
	queue<int> q;
	vector<bool> vis(V, false);
	q.push(0);
	vis[0] = true;

	while (!q.empty()) {

		int f = q.front();
		q.pop();
		ans.push_back(f);

		for (auto k : adj[f]) {
			if (!vis[k]) {
				vis[k] = true;
				q.push(k);
			}
		}
	}
	return ans;
}

//cycle detection in undirected graph

bool dfs(int node, int parent, vector<bool>& vis, vector<int> adj[]) {

	vis[node] = true;

	for (auto k : adj[node]) {

		if (vis[k] && k != parent) return true;
		if (!vis[k]) {
			if (dfs(k, node, vis, adj)) return true;
		}
	}
	return false;
}


public:
// Function to detect cycle in an undirected graph.
bool isCycle(int V, vector<int> adj[]) {

	vector<bool> vis(V, false);

	for (int i = 0; i < V; ++i) {

		if (!vis[i]) {
			if (dfs(i, -1, vis, adj)) return true;
		}
	}
	return false;
}

//cycle detection in directed graph

bool dfs(int node, vector<bool>& vis, vector<bool>& rec, vector<int> adj[]) {

	vis[node] = true;
	rec[node] = true;

	for (auto k : adj[node]) {

		if (rec[k]) return true;
		if (!vis[k]) {
			if (dfs(k, vis, rec, adj)) return true;
		}
	}
	rec[node] = false;
	return false;
}


public:
// Function to detect cycle in a directed graph.
bool isCyclic(int V, vector<int> adj[]) {

	vector<bool> vis(V, false);
	vector<bool> rec(V, false);

	for (int i = 0; i < V; ++i) {
		if (!vis[i]) {
			if (dfs(i, vis, rec, adj)) return true;
		}
	}
	return false;
}

//topological sort
//do dfs and at the end push the element into the stack

void dfs(int node, vector<bool>& vis, stack<int>& st, vector<int> adj[]) {

	vis[node] = true;

	for (auto k : adj[node]) {
		if (!vis[k]) dfs(k, vis, st, adj);
	}

	st.push(node);
}


public:
//Function to return list containing vertices in Topological order.
vector<int> topoSort(int V, vector<int> adj[])
{
	vector<bool> vis(V, false);
	stack<int> st;

	for (int i = 0; i < V; ++i) {
		if (!vis[i]) dfs(i, vis, st, adj);
	}

	vector<int> ans;

	while (!st.empty()) {

		int t = st.top();
		st.pop();
		ans.push_back(t);
	}

	return ans;
}

//number of islands

//using dfs

void dfs(int x, int y, vector<vector<char>>& grid) {

	if (x < 0 || x == grid.size() || y < 0 || y == grid[0].size() || grid[x][y] == '0') return;
	grid[x][y] = '0';
	dfs(x, y - 1, grid);
	dfs(x, y + 1, grid);
	dfs(x + 1, y, grid);
	dfs(x - 1, y, grid);
}


public:
int numIslands(vector<vector<char>>& grid) {

	int cnt = 0;

	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[0].size(); ++j) {

			if (grid[i][j] == '1') {
				dfs(i, j, grid);
				cnt++;
			}
		}
	}
	return cnt;
}

//using bfs

bool safePosition(int x, int y, vector<vector<char>>& grid) {

	if (x < 0 || x == grid.size() || y < 0 || y == grid[0].size() || grid[x][y] == '0') return false;
	return true;
}

void bfs(int x, int y, vector<vector<char>>& grid) {

	queue<pair<int, int>> q;
	q.push({x, y});
	grid[x][y] = '0';

	while (!q.empty()) {

		auto f = q.front();
		q.pop();

		int xdir[] = { -1, 1, 0, 0};
		int ydir[] = {0, 0, -1, 1};

		for (int i = 0; i < 4; ++i) {

			int newx = f.first + xdir[i];
			int newy = f.second + ydir[i];

			if (safePosition(newx, newy, grid)) {
				grid[newx][newy] = '0';
				q.push({newx, newy});
			}
		}
	}

}


public:
int numIslands(vector<vector<char>>& grid) {

	int cnt = 0;

	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[0].size(); ++j) {

			if (grid[i][j] == '1') {
				cnt++;
				bfs(i, j, grid);
			}
		}
	}
	return cnt;
}


//Is graph bipartite

//using bfs approach

bool bipartite(int node, vector<int>& color, vector<vector<int>>& graph) {

	queue<int> q;
	color[node] = 1;
	q.push(node);

	while (!q.empty()) {

		int f = q.front();
		q.pop();

		for (auto k : graph[f]) {

			if (color[k] == -1) {
				color[k] = 1 - color[f];
				q.push(k);
			}
			else if (color[k] == color[f]) return false;
		}
	}
	return true;
}

public:
bool isBipartite(vector<vector<int>>& graph) {

	int n = graph.size();
	vector<int> color(n, -1);

	for (int i = 0; i < n; ++i) {

		if (color[i] == -1 && !bipartite(i, color, graph)) return false;
	}
	return true;
}

//dfs approach

bool bipartite(int node, vector<int>& color, vector<vector<int>>& graph) {


	for (auto k : graph[node]) {

		if (color[k] == color[node]) return false;
		if (color[k] == -1) {
			color[k] = 1 - color[node];
			if (!bipartite(k, color, graph)) return false;
		}
	}
	return true;
}

public:
bool isBipartite(vector<vector<int>>& graph) {

	int n = graph.size();
	vector<int> color(n, -1);

	for (int i = 0; i < n; ++i) {

		if (color[i] == -1) {
			color[i] = 1;
			if (!bipartite(i, color, graph)) return false;
		}
	}
	return true;
}