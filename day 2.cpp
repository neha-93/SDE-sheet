//set matrix zero

//traverse through the matrix and for all zeroes encountered set all non zeroes row and column element to
//-1 later traverse through matrix and change all -1 to zero.
//time O(n^3)

//we can take row and col array and change it to zero if any element is zero

//instead of taking addition array we can use the first row and the first column as row and col array and
//for first row and first column we can maintain a zerorow and zerocolumn variable
//time O(n*m) space O(1)


void setZeroes(vector<vector<int>>& matrix) {

	bool zeroRow = false, zeroCol = false;

	int n = matrix.size();
	int m = matrix[0].size();

	for (int i = 0; i < n; ++i) {
		if (matrix[i][0] == 0) zeroRow = true;
	}
	for (int j = 0; j < m; ++j) {
		if (matrix[0][j] == 0) zeroCol = true;
	}

	for (int i = 1; i < n; ++i) {
		for (int j = 1; j < m; ++j) {

			if (matrix[i][j] == 0) {
				matrix[i][0] = 0;
				matrix[0][j] = 0;
			}
		}
	}

	for (int i = 1; i < n; ++i) {
		for (int j = 1; j < m; ++j) {
			if (matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;
		}
	}

	if (zeroRow) {
		for (int i = 0; i < n; ++i) matrix[i][0] = 0;
	}
	if (zeroCol) {
		for (int j = 0; j < m; ++j) matrix[0][j] = 0;
	}

}


//pascals triangle
//value at row n column m is n-1Cm-1
//code for all rows till numRows

vector<vector<int>> generate(int numRows) {

	vector<vector<int>> r(numRows, vector<int>(numRows));

	for (int i = 0; i < numRows; ++i) {

		r[i].resize(i + 1);
		r[i][0] = r[i][i] = 1;

		for (int j = 1; j < i; ++j) r[i][j] = r[i - 1][j - 1] + r[i - 1][j];
	}
	return r;

}

//a particular row of the pascal triangle

vector<int> getRow(int rowIndex) {

	vector<int> r(rowIndex + 1);

	r[0] = 1, r[rowIndex] = 1;
	long long a;

	for (int i = 1; i < rowIndex; ++i) {

		a = (long long)r[i - 1] * (rowIndex - i + 1);
		a = a / i;
		r[i] = a;
	}
	return r;
}


//next permutation

//find the right most number which is less than its adjacent right number
//swap this number with the number which is the right most number which is greater than this.
//and then reverse the numbers from i+1 the index till the end of the array.

class Solution {

	void reverse(vector<int>& nums, int s, int e) {

		while (s < e) {
			swap(nums[s], nums[e]);
			s++;
			e--;
		}
	}

	int bsearch(vector<int>& nums, int s, int e, int key) {

		int ind;

		while (s <= e) {

			int m = (s + e) / 2;
			if (nums[m] > key) {
				ind = m;
				s = m + 1;
			}
			else e = m - 1;
		}
		return ind;
	}

public:
	void nextPermutation(vector<int>& nums) {

		int n = nums.size();
		int i;

		for (i = n - 2; i >= 0; --i) {
			if (nums[i] < nums[i + 1]) break;
		}

		if (i == -1) {
			reverse(nums, 0, n - 1);
			return;
		}

		int j = bsearch(nums, i + 1, n - 1, nums[i]);
		swap(nums[j], nums[i]);
		reverse(nums, i + 1, n - 1);
	}
};


//inversion count
//for every element check number on right which is smaller add the count to the total inversion count
//time O(n^2) and space O(1)

//use the merge sort algorithm and in the merge step if arr[i] > arr[j] the increase count by m-i+1

long long merge(long long arr[], int s, int e, int m) {

	long long a[e - s + 1];
	int i = s, j = m + 1, k = 0;
	long long c = 0;

	while (i <= m && j <= e) {

		if (arr[i] <= arr[j]) {
			a[k++] = arr[i++];
		}
		else {
			a[k++] = arr[j++];
			c += m - i + 1;
		}
	}

	while (i <= m) a[k++] = arr[i++];
	while (j <= e) a[k++] = arr[j++];

	for (i = s; i <= e; ++i) arr[i] = a[i - s];
	return c;
}

long long count(long long arr[], int s, int e) {

	long long c = 0;
	if (s < e) {
		int m = (s + e) / 2;
		c += count(arr, s, m);
		c += count(arr, m + 1, e);
		c += merge(arr, s, e, m);
	}
	return c;
}


public:
// arr[]: Input Array
// N : Size of the Array arr[]
// Function to count inversions in the array.
long long int inversionCount(long long arr[], long long N)
{
	// Your Code Here
	long long invCnt = 0;
	invCnt = count(arr, 0, N - 1);
	return invCnt;
}

//best time to buy and sell a stock

//only one stock
int maxProfit(vector<int>& prices) {

	int n = prices.size();
	if (n == 0) return 0;

	int mini = prices[0];
	int profit = 0;

	for (int i = 1; i < n; ++i) {
		mini = min(mini, prices[i]);
		profit = max(profit, prices[i] - mini);
	}
	return profit;
}

//more than one stock

int maxProfit(vector<int>& price) {

	int profit = 0;
	int n = price.size();

	for (int i = 1; i < n; ++i) {
		if (price[i] > price[i - 1]) profit += price[i] - price[i - 1];
	}
	return profit;
}


//rotate a matrix

//take another matrix and make the first row its last column and so on
//time O(N^2) and space O(N^2)

//first transpose the matrix and then reverse the matrix row wise
//time O(N^2) and space O(1)

void rotate(vector<vector<int>>& matrix) {

	int n = matrix.size();

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {

			swap(matrix[i][j], matrix[j][i]);
		}
	}

	for (int i = 0; i < n; ++i) {
		reverse(matrix[i].begin(), matrix[i].end());
	}

}




