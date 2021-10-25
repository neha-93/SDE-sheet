//coin change problem

int coinChange(vector<int>& coins, int amount) {

	int n = coins.size();
	vector<int> dp(amount + 1, INT_MAX);
	dp[0] = 0;

	for (int i = 1; i <= amount; ++i) {

		for (int j = 1; j <= n; ++j) {

			if (i >= coins[j - 1] && dp[i - coins[j - 1]] != INT_MAX) dp[i] = min(dp[i], 1 + dp[i - coins[j - 1]]);
		}
	}
	return dp[amount] == INT_MAX ? -1 : dp[amount];
}

//subset sum

//similar to 0-1 knapsack

bool isSubset(int n, int arr[], int sum, vector<vector<int>>& dp) {

	if (sum == 0) return 1;
	if (n == 0) return 0;
	if (dp[n][sum] != -1) return dp[n][sum];

	if (sum < arr[n - 1]) return dp[n][sum] = isSubset(n - 1, arr, sum, dp);

	return dp[n][sum] = isSubset(n - 1, arr, sum - arr[n - 1], dp) || isSubset(n - 1, arr, sum, dp);
}


public:
bool isSubsetSum(int N, int arr[], int sum) {
	// code here

	vector<vector<int>> dp(N + 1, vector<int>(sum + 1, -1));

	return isSubset(N, arr, sum, dp);

}

//maximize rod cutting segments

int maximizeTheCuts(int n, int x, int y, int z)
{

	vector<int> dp(n + 1, -1);
	dp[0] = 0;

	for (int i = 1; i <= n; ++i) {


		if (i >= x && dp[i - x] != -1) dp[i] = max(dp[i], 1 + dp[i - x]);
		if (i >= y && dp[i - y] != -1) dp[i] = max(dp[i], 1 + dp[i - y]);
		if (i >= z && dp[i - z] != -1) dp[i] = max(dp[i], 1 + dp[i - z]);
	}

	if (dp[n] == -1) return 0;
	return dp[n];
}

//egg drop puzzle

//we can further memoise the up and down

int eggDrops(int e, int f, vector<vector<int>>& dp) {

	if (f <= 1) return f;
	if (e == 1) return f;
	if (dp[e][f] != -1) return dp[e][f];

	int tmp, mini = INT_MAX;

	for (int i = 1; i <= f; ++i) {

		int up = eggDrops(e, f - i, dp);
		int down = eggDrops(e - 1, i - 1, dp);
		tmp = max(up, down) + 1;
		mini = min(mini, tmp);
	}

	return dp[e][f] = mini;
}

public:
//Function to find minimum number of attempts needed in
//order to find the critical floor.
int eggDrop(int n, int k)
{
	vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1));

	return eggDrops(n, k, dp);
}


//word break

//trie + dp solution

class TrieNode {
public:
	unordered_map<char, TrieNode*> child;
	bool isLast;

	TrieNode () {
		isLast = false;
		for (char i = 'a'; i <= 'z'; ++i) child[i] = NULL;
	}
};

void insert(TrieNode *root, string s) {

	TrieNode *itr = root;

	for (int i = 0; i < s.size(); ++i) {

		TrieNode *nextNode = itr->child[s[i]];
		if (!nextNode) {
			nextNode = new TrieNode();
			itr->child[s[i]] = nextNode;
		}
		itr = nextNode;

		if (i == s.size() - 1) itr->isLast = true;
	}
}

bool search(TrieNode *root, string s) {

	TrieNode *itr = root;

	for (int i = 0; i < s.size(); ++i) {
		if (!itr->child[s[i]]) return false;
		itr = itr->child[s[i]];
	}

	return itr->isLast;
}

bool rc(TrieNode *root, string s, vector<string> & wordDict) {

	int sz = s.size();
	if (sz == 0) return true;

	for (int i = 1; i <= sz; ++i) {
		if (search(root, s.substr(0, i)) && rc(root, s.substr(i, sz - i), wordDict)) return true;
	}
	return false;

}
public:
bool wordBreak(string s, vector<string>& wordDict) {

	TrieNode *root = new TrieNode();

	for (auto w : wordDict) {
		insert(root, w);
	}

	int n = s.size();
	int dp[n + 1];
	memset(dp, 0, sizeof dp);

	dp[0] = 1;

	for (int i = 1; i <= n; ++i) {

		for (int j = i - 1; j >= 0; --j) {
			if (dp[j]) {
				if (search(root, s.substr(j, i - j))) {
					dp[i] = 1;
					break;
				}
			}
		}
	}
	return dp[n];
}


//palindrome partitioning

//mcm variation

int dp[503][503];

bool isPalindrome(string str, int i, int j) {

	while (i < j) {
		if (str[i] != str[j]) return false;
		i++, --j;
	}
	return true;
}

int minPartition(string s, int i, int j) {

	if (i >= j || isPalindrome(s, i, j)) return 0;
	if (dp[i][j] != -1) return dp[i][j];

	int ans = INT_MAX, left, right;

	for (int k = i; k < j; ++k) {

		if (dp[i][k] != -1) left = dp[i][k];
		else left = minPartition(s, i, k);

		if (dp[k + 1][j] != -1) right = dp[k + 1][j];
		else right = minPartition(s, k + 1, j);

		ans = min(ans, 1 + left + right);
	}

	dp[i][j] = ans;
	return dp[i][j];
}


public:
int palindromicPartition(string str)
{
	memset(dp, -1, sizeof(dp));

	return minPartition(str, 0, str.size() - 1);
}


//maximum profit in weighted job scheduling

struct job {
	int start, end, profit;
};

static bool compare(job a, job b) {
	return a.end < b.end;
}

int findjobBefore(vector<job>& jobs, int l, int h, int i) {

	int ind = -1;
	while (l <= h) {

		int mid = (l + h) / 2;
		if (jobs[mid].end <= jobs[i].start) {
			ind = mid;
			l = mid + 1;
		}
		else h = mid - 1;

	}
	return ind;
}


public:
int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {

	int n = startTime.size();
	vector<job> jobs(n);

	for (int i = 0; i < n; ++i) {

		jobs[i].start = startTime[i];
		jobs[i].end = endTime[i];
		jobs[i].profit = profit[i];

	}

	sort(jobs.begin(), jobs.end(), compare);

	int dp[n];
	dp[0] = jobs[0].profit;

	for (int i = 1; i < n; ++i) {

		int incProfit = jobs[i].profit;

		int ind = findjobBefore(jobs, 0, i - 1, i);
		if (ind != -1) incProfit += dp[ind];

		dp[i] = max(incProfit, dp[i - 1]);

	}
	return dp[n - 1];

}