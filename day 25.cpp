//Maximum product subarray


//first tell that you would generate all possible subarrays and return the maximum product
//time O(n^2)

//tell that we would maintain maxprod and minprod and return the maximum product obtained
//dp

int maxProduct(vector<int>& nums) {

	int maxProd = nums[0];
	int minProd = nums[0];
	int gmax = nums[0];

	for (int i = 1; i < nums.size(); ++i) {

		int tmp = maxProd;
		maxProd = max(max(maxProd * nums[i], minProd * nums[i]), nums[i]);
		minProd = min(min(minProd * nums[i], tmp * nums[i]), nums[i]);

		gmax = max(maxProd, gmax);
	}
	return gmax;
}

//longest increasing sequence

int longestSubsequence(int n, int a[])
{
	int gmax = 1;
	vector<int> lis(n, 1);

	for (int i = 1; i < n; ++i) {

		for (int j = i - 1; j >= 0; --j) {
			if (a[j] < a[i]) lis[i] = max(lis[i], lis[j] + 1);
		}
		gmax = max(gmax, lis[i]);
	}
	return gmax;
}

//longest common subsequence

int lcs(int x, int y, string s1, string s2)
{
	int dp[x + 1][y + 1];
	memset(dp, 0, sizeof dp);

	for (int i = 1; i <= x; ++i) {
		for (int j = 1; j <= y; ++j) {

			if (s1[i - 1] != s2[j - 1]) dp[i][j] = max(dp[i - 1][j - 1], max(dp[i][j - 1], dp[i - 1][j]));
			else dp[i][j] = dp[i - 1][j - 1] + 1;
		}
	}
	return dp[x][y];
}

//0-1 knapsack

//memoisation + recursion

int knapsack(int W, int wt[], int val[], int n, vector<vector<int>>& dp) {

	if (n == 0) return 0;
	if (dp[W][n] != -1) return dp[W][n];
	if (wt[n - 1] > W) return dp[W][n] = knapsack(W, wt, val, n - 1, dp);

	return dp[W][n] = max(knapsack(W, wt, val, n - 1, dp), val[n - 1] +
	                      knapsack(W - wt[n - 1], wt, val, n - 1, dp));
}

public:
//Function to return max value that can be put in knapsack of capacity W.
int knapSack(int W, int wt[], int val[], int n)
{
	vector<vector<int>> dp(W + 1, vector<int>(n + 1, -1));

	return knapsack(W, wt, val, n, dp);
}


//iterative solution

int knapSack(int W, int wt[], int val[], int n)
{
	// Your code here
	int dp[n + 1][W + 1];
	memset(dp, 0, sizeof dp);

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= W; ++j) {

			if (i == 0 || j == 0) {
				dp[i][j] = 0;
				continue;
			}
			if (j < wt[i - 1]) dp[i][j] = dp[i - 1][j];
			else dp[i][j] = max(val[i - 1] + dp[i - 1][j - wt[i - 1]], dp[i - 1][j]);
		}
	}
	return dp[n][W];
}

//Edit distance

int editDistance(string s, string t) {
	// Code here
	int n = s.size();
	int m = t.size();

	int dp[n + 1][m + 1];

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {

			if (i == 0) dp[i][j] = j;
			else if (j == 0) dp[i][j] = i;
			else if (s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j - 1];
			else dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j]));
		}
	}
	return dp[n][m];
}

//maximum sum increasing sequence

//a variation of lis

int maxSumIS(int arr[], int n)
{
	// Your code goes here
	int sum[n];
	int gmax = arr[0];
	for (int i = 0; i < n; ++i) sum[i] = arr[i];

	for (int i = 0; i < n; ++i) {

		for (int j = 0; j < i; ++j) {

			if (arr[i] > arr[j]) sum[i] = max(sum[j] + arr[i], sum[i]);
		}
		gmax = max(gmax, sum[i]);
	}
	return gmax;

}

//Matrix chain multiplication

//recursion + memoisation

int matrixMult(int arr[], int i, int j, vector<vector<int>>& dp) {

	if (i >= j) return 0;
	if (dp[i][j] != -1) return dp[i][j];

	int mn = INT_MAX;

	for (int k = i; k < j; ++k) {

		int left = dp[i][k];
		if (left == -1) left = dp[i][k] = matrixMult(arr, i, k, dp);

		int right = dp[k + 1][j];
		if (right == -1) right = dp[k + 1][j] = matrixMult(arr, k + 1, j, dp);

		mn = min(left + right + arr[i - 1] * arr[k] * arr[j], mn);
	}
	return dp[i][j] = mn;
}

public:
int matrixMultiplication(int N, int arr[])
{

	vector<vector<int>> dp(N + 1, vector<int>(N + 1, -1));

	return matrixMult(arr, 1, N - 1, dp);
}

