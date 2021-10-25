//sort 0, 1, 2

//first tell we could just sort the array time O(Nlog N)
//use count sort we will traverse the array twice

void sort012(int a[], int n)
{
	int cnt0 = 0, cnt1 = 0, cnt2 = 0;

	for (int i = 0; i < n; ++i) {
		if (a[i] == 0) cnt0++;
		if (a[i] == 1) cnt1++;
		if (a[i] == 2) cnt2++;
	}

	int i = 0;
	for (int j = 0; j < cnt0; ++j) a[i++] = 0;
	for (int j = 0; j < cnt1; ++j) a[i++] = 1;
	for (int j = 0; j < cnt2; ++j) a[i++] = 2;

}

//use pointers

void sort012(int a[], int n)
{

	int low = 0, mid = 0, high = n - 1;

	while (mid <= high) {

		if (a[mid] == 0) swap(a[low++], a[mid++]);
		else if (a[mid] == 1) mid++;
		else swap(a[mid], a[high--]);
	}
}


//Repeating and missing number

//we can use hash map to count the number of the appearing numbers
//during the second iteration if the count is 2 then its repeating number and if count is 0 then it is a
//missing number.

//using sum and square of sum approach

vector<int> Solution::repeatedNumber(const vector<int> &A) {
	int n = A.size();

	long long sum = 0;
	long long squareSum = 0;

	long long s = 0, ss = 0;

	for (int i = 0; i < n; ++i) {
		sum += A[i];
		squareSum += (long long)A[i] * A[i];
		s += (i + 1);
		ss += ((long long) (i + 1)) * (i + 1);
	}

	long long diff = sum - s;
	long long squareDiff = squareSum - ss;

	long long twoSum = squareDiff / diff;

	int x = (diff + twoSum) / 2;
	int y = twoSum - x;

	return {x, y};
}

//by modifying the array

//by using the xor approach


//merge two sorted array

//using extra space
void merge(int arr1[], int arr2[], int n, int m)
{
	int arr[n + m];

	int i = 0, j = 0, k = 0;

	while (i < n && j < m) {
		if (arr1[i] <= arr2[j]) arr[k++] = arr1[i++];
		else arr[k++] = arr2[j++];
	}

	while (i < n) arr[k++] = arr1[i++];
	while (j < m) arr[k++] = arr2[j++];

	for (i = 0; i < n; ++i) {
		arr1[i] = arr[i];
	}
	for (i = 0; i < m; ++i) {
		arr2[i] = arr[n + i];
	}
}

//using insertion sort technique
//O(n^2) time O(1) space

void merge(long long arr1[], long long arr2[], int n, int m)
{

	for (int i = 0; i < n; ++i) {

		if (arr1[i] > arr2[0]) {
			swap(arr1[i], arr2[0]);

			int p = arr2[0], j;
			for (j = 1; j < m; ++j) {
				if (arr2[j] < p) arr2[j - 1] = arr2[j];
				else break;
			}
			arr2[j - 1] = p;
		}
	}

}


//using gap method
// time O(nlog n) space O(1)

void merge(long long arr1[], long long arr2[], int n, int m)
{

	int gap = ceil((float)(n + m) / 2);

	while (gap > 0) {

		for (int i = 0; i < n + m - gap; ++i) {

			if (i < n && i + gap < n) {
				if (arr1[i] > arr1[i + gap]) swap(arr1[i], arr1[i + gap]);
			}
			else if (i < n && i + gap >= n) {
				if (arr1[i] > arr2[i + gap - n]) swap(arr1[i], arr2[i + gap - n]);
			}
			else {
				if (arr2[i - n] > arr2[i + gap - n]) swap(arr2[i - n], arr2[i + gap - n]);
			}
		}
		if (gap <= 1) gap = 0;
		else gap = gap / 2 + gap % 2;
	}

}


//kadane's algorithm

//first tell the brute force approch that you will consider all the sub array and find the sum and
//take the maximum sum

//the optimise that brute force to n^2 time

//then tell the kadane solution

int maxSubArray(vector<int>& nums) {

	if (!nums.size()) return 0;

	int maxi = nums[0], gmax = nums[0];

	for (int i = 1; i < nums.size(); ++i) {
		maxi = max(nums[i], maxi + nums[i]);
		gmax = max(gmax, maxi);
	}
	return gmax;
}

//merge intervals

//first tell the brute force that for each interval we will find the merged interval and if we don't have
//the merged interval we will push that interval in our data structure

//the other approach is that we will sort the array and will find the merged interval and if an interval
//doesn't merge we will push that interval in our data structure and take that interval and we will merge
//that.

vector<vector<int>> merge(vector<vector<int>>& intervals) {

	vector<vector<int>> mergedInterval;

	int n = intervals.size();
	if (n == 0) return mergedInterval;

	sort(intervals.begin(), intervals.end());

	auto interval = intervals[0];

	for (int i = 1; i < n; ++i) {
		if (intervals[i][0] <= interval[1]) {
			interval[1] = max(intervals[i][1], interval[1]);
		}
		else {
			mergedInterval.push_back(interval);
			interval = intervals[i];
		}
	}
	mergedInterval.push_back(interval);
	return mergedInterval;
}

//find the duplicate element in an n+1 array

//first tell the hashing approach and then move on to the linked list approach tortoise method

int findDuplicate(vector<int>& nums) {

	int n = nums.size();
	if (n == 0) return 0;

	int fast = nums[0];
	int slow = nums[0];

	do {
		fast = nums[nums[fast]];
		slow = nums[slow];
	} while (fast != slow);

	fast = nums[0];
	while (fast != slow) {
		fast = nums[fast];
		slow = nums[slow];
	}
	return fast;
}






