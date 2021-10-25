//search in sorted 2d array

//go to top most right index

bool searchMatrix(vector<vector<int>>& matrix, int target) {

	int n = matrix.size();
	int m = matrix[0].size();
	int i = 0, j = m - 1;

	while (i < n && j >= 0) {

		if (matrix[i][j] == target) return true;
		else if (matrix[i][j] > target) --j;
		else ++i;
	}
	return false;
}

//do binary search
//time O(log(n*m)) and space O(1)

bool searchMatrix(vector<vector<int>>& matrix, int target) {

	int n = matrix.size();
	int m = matrix[0].size();
	int low = 0, high = n * m - 1;

	while (low <= high) {

		int mid = (low + high) / 2;
		if (matrix[mid / m][mid % m] == target) return true;
		else if (matrix[mid / m][mid % m] > target) {
			high = mid - 1;
		}
		else low = mid + 1;
	}
	return false;
}

// power(x,n)

//iterate from 1 to n and multiply x in every iteration
//time O(n) and space O(1)

//if power is odd power-- and multiply by x
//else power/2 and ans * ans

double myPow(double x, int n) {

	long nn = abs(n);
	if (n < 0) x = 1 / x;

	double ans = 1;

	while (nn > 0) {

		if (nn % 2) {
			nn--;
			ans *= x;
		}
		nn /= 2;
		x = x * x;

	}
	return ans;
}

//majority elements(n/2 times)

//for every element check if it is a majority element
//time O(N^2) and space O(1)

//create a hashmap of numbers and their frequency
//time O(n) and space O(n)

//moore voting algorithm
//time O(n) space O(1)

int majorityElement(vector<int>& nums) {

	int cand, cnt = 0;
	if (!nums.size()) return 0;

	for (int i = 0; i < nums.size(); ++i) {

		if (cnt == 0) cand = nums[i];
		if (nums[i] == cand) cnt++;
		else cnt--;
	}

	return cand;
}

//majority element(n/3 times)

vector<int> majorityElement(vector<int>& nums) {

	int cand1, cand2, c1 = 0, c2 = 0;
	int n = nums.size();

	for (auto k : nums) {

		if (k == cand1) c1++;
		else if (k == cand2) c2++;
		else if (c1 == 0) {
			cand1 = k;
			c1 = 1;
		}
		else if (c2 == 0) {
			cand2 = k;
			c2 = 1;
		}
		else c1--, c2--;
	}

	vector<int> ans;

	c1 = 0, c2 = 0;
	for (auto k : nums) {
		if (k == cand1) c1++;
		else if (k == cand2) c2++;
	}

	if (c1 > n / 3) ans.push_back(cand1);
	if (c2 > n / 3) ans.push_back(cand2);

	return ans;
}

//grid unique path

//recursive solution

int path(int i, int j, int n, int m) {

	if (i >= n || j >= m) return 0;
	if (i == n - 1 && j == m - 1) return 1;
	return path(i + 1, j, n, m) + path(i, j + 1, n, m);
}


public:
int uniquePaths(int m, int n) {

	return path(0, 0, n, m);

}

//memoised the code for dp solution

int path(int i, int j, int n, int m, vector<vector<int>>& dp) {

	if (i >= n || j >= m) return 0;
	if (i == n - 1 && j == m - 1) return 1;
	if (dp[i][j] != -1) return dp[i][j];
	return dp[i][j] = path(i + 1, j, n, m, dp) + path(i, j + 1, n, m, dp);
}


public:
int uniquePaths(int m, int n) {

	vector<vector<int>> dp(n, vector<int>(m, -1));
	return path(0, 0, n, m, dp);

}

//using permutation
//we need to move right m-1 times and down n-1 times
//so we can say and is n+m-2Cn-1 or n+m-2Cm-1

int uniquePaths(int m, int n) {

	int N = m + n - 2;
	n = min(n, m);
	long long ans = 1;

	for (int i = 1; i < n; ++i) {

		ans = (ans * (N - i + 1)) / i;
	}
	return (int)ans;
}

//find reversed pair

//first say the brute force approach for every element we will count reversed pair
//time O(n^2) and space O(1)

//use the merge sort approach
//time O(nlogn) and space O(n)

int merge(vector<int>& nums, int s, int e) {

	int m = (s + e) / 2;
	int a[e - s + 1];
	int c = 0;

	int i = s, j = m + 1, k = 0;

	while (i <= m && j <= e) {

		if ((long)nums[i] <= (long)2 * nums[j]) i++;
		else {
			c += m - i + 1;
			j++;
		}
	}

	i = s, j = m + 1;

	while (i <= m && j <= e) {

		if (nums[i] < nums[j]) a[k++] = nums[i++];
		else a[k++] = nums[j++];
	}

	while (i <= m) a[k++] = nums[i++];
	while (j <= e) a[k++] = nums[j++];

	for (i = s; i <= e; ++i) nums[i] = a[i - s];

	return c;

}

int countReverse(vector<int>& nums, int s, int e) {

	int c = 0;
	if (s < e) {
		int m = (s + e) / 2;
		c += countReverse(nums, s, m);
		c += countReverse(nums, m + 1, e);
		c += merge(nums, s, e);
	}

	return c;
}

public:
int reversePairs(vector<int>& nums) {

	return countReverse(nums, 0, nums.size() - 1);
}

