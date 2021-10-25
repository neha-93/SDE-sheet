//nth root of a number

//use binary search as the roots would be monotonically increasing

#include <bits/stdc++.h>
using namespace std;

double multiply(double num, int n) {

	double ans = 1.0;
	for (int i = 0; i < n; ++i) {
		ans *= num;
	}
	return ans;
}

double nthRoot(int n, int m) {

	double low = 1.0;
	double high = m;
	double mid;
	double diff = 1e-6;

	while ((high - low) > diff) {
		mid = (low + high) / 2.0;

		if (multiply(mid, n) > m) high = mid;
		else low = mid;
	}

	//cout << low << " " << high << endl;
	//cout << pow(low,n) << endl;

	return low;
}

int main() {

	int n, m;
	cin >> n >> m;

	cout << nthRoot(n, m) << endl;
	return 0;
}

//Median of a Matrix

int Solution::findMedian(vector<vector<int> > &A) {

	int s = 1;
	int e = 1e9;
	int m;
	int cnt;
	int low, high, mid;
	int cc;

	int r = A.size(), c = A[0].size();
	int d = (1 + r * c) / 2;

	while (s <= e) {
		m = (s + e) / 2;
		//cout << s << " " << e << " " << m << endl;
		cnt = 0;
		for (int i = 0; i < A.size(); ++i) {
			low = 0;
			high = A[0].size();
			cc = 0;
			while (low <= high) {
				mid = (low + high) / 2;
				if (A[i][mid] <= m) low = mid + 1;
				else {
					cc = mid;
					high = mid - 1;
				}
			}
			if (A[i][c - 1] <= m) cc = c;
			cnt += cc;
		}
		if (cnt < d) s = m + 1;
		else e = m - 1;

		//cout << cnt << endl;
	}
	return s;
}

//sorted array find the element which appears only once

//say u will iterate through the array and xor the elements and the result would be the required answer

//use binary search
//left half 1st instance -> even
//2nd instance -> odd
//find the index when left half ends


int singleNonDuplicate(vector<int>& nums) {

	int low = 0, high = nums.size() - 2;
	int mid;

	while (low <= high) {
		mid = (low + high) >> 1;
		if (nums[mid] == nums[mid ^ 1]) low = mid + 1;
		else high = mid - 1;
	}
	return nums[low];
}

//find the index of an element in a rotated sorted array

//first tell the linear search approach
//then tell the binary seacrch approach

int search(vector<int>& nums, int target) {

	int low = 0, high = nums.size() - 1;
	int mid;

	while (low <= high) {

		mid = (low + high) >> 1;
		if (nums[mid] == target) return mid;
		if (nums[mid] >= nums[low]) {
			if (nums[low] <= target && nums[mid] >= target) high = mid - 1;
			else low = mid + 1;
		}
		else {
			if (nums[mid] <= target && nums[high] >= target) low = mid + 1;
			else high = mid - 1;
		}
	}

	return -1;
}

//find median of two sorted array

//use binary search to find the appropiate partioning


double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

	if (nums1.size() > nums2.size()) findMedianSortedArrays(nums2, nums1);

	int n1 = nums1.size();
	int n2 = nums2.size();

	int d = (n1 + n2 + 1) / 2;

	int low = 0;
	int high = n1;
	long long l1, l2, r1, r2;

	while (low <= high) {

		int cut1 = (low + high) / 2;
		int cut2 = d - cut1;

		l1 = cut1 ? nums1[cut1 - 1] : INT_MIN;
		l2 = cut2 ? nums2[cut2 - 1] : INT_MIN;

		r1 = (cut1 == n1) ? INT_MAX : nums1[cut1];
		r2 = (cut2 == n2) ? INT_MAX : nums2[cut2];

		if (l1 <= r2 && l2 <= r1) {
			if ((n1 + n2) % 2) return max(l1, l2);
			else {
				return (max(l1, l2) + min(r1, r2)) / 2.0;
			}
		}
		else if (l1 > r2) high = cut1 - 1;
		else low = cut1 + 1;
	}

	return 0.0;
}

//kth element of two sorted array

//divide into two groups(first group of size k) and if the group is valid return the maximum of the
// first group


int kthElement(int arr1[], int arr2[], int n, int m, int k)
{
	if (m < n) return kthElement(arr2, arr1, m, n, k);

	int low = max(0, k - m), high = min(k, n);
	int l1, l2, r1, r2;

	while (low <= high) {

		int cut1 = (low + high) >> 1;
		int cut2 = k - cut1;

		l1 = cut1 ? arr1[cut1 - 1] : INT_MIN;
		l2 = cut2 ? arr2[cut2 - 1] : INT_MIN;

		r1 = cut1 == n ? INT_MAX : arr1[cut1];
		r2 = cut2 == m ? INT_MAX : arr2[cut2];

		if (l1 <= r2 && l2 <= r1) {
			return max(l1, l2);
		}
		else if (l1 > r2) high = cut1 - 1;
		else low = cut1 + 1;

		// cout << l1 << " " << l2 << " " << r1 << " " << r2 << endl;
	}

	return -1;
}

//book allocation problem

//have the initial search space as maximum book size and total book size
//and shrink the search space

int Solution::books(vector<int> &A, int B) {

	int mini = 0, maxi = 0;
	if (B > A.size()) return -1;

	for (auto k : A) {
		mini = max(k, mini);
		maxi += k;
	}

	int low = mini, high = maxi;

	while (low <= high) {

		int mid = (low + high) >> 1;

		int cur = 0, cnt = 0;
		for (int i = 0; i < A.size(); ++i) {

			if (cur + A[i] <= mid) {
				cur += A[i];
			}
			else {
				if (cur == 0) break;
				cur = A[i];
				cnt++;
			}
		}
		if (cur == 0) low = mid + 1;
		else if (cnt >= B) low = mid + 1;
		else high = mid - 1;
	}
	return low;
}



