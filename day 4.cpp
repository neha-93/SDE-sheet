//two sum

//brute force for every number check if target-number is there in the array if it is there
//return the index

//use hashmap for every number push it in the hash map untill we find target - number in the hash map

vector<int> twoSum(vector<int>& nums, int target) {

	unordered_map<int, int> mp;

	for (int i = 0; i < nums.size(); ++i) {

		if (mp.find(target - nums[i]) != mp.end()) return {i, mp[target - nums[i]]};
		mp[nums[i]] = i;

	}
	return {};
}

//4 sum

//use 2 nested loops and a 2 pointer to find all the subsquence which sums to target value

vector<vector<int>> fourSum(vector<int>& nums, int target) {

	vector<vector<int>> res;
	int n = nums.size();
	sort(nums.begin(), nums.end());

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {

			int l = j + 1;
			int h = n - 1;

			while (l < h) {

				long long sum = (long long)nums[i] + nums[j] + nums[l] + nums[h];

				if (sum == target) {
					res.push_back({nums[i], nums[j], nums[l], nums[h]});
					while (l < h && nums[l] == nums[l + 1]) l++;
					while (l < h && nums[h] == nums[h - 1]) h--;
					l++;
					h--;
				}
				else if (sum > target) h--;
				else l++;

			}
			while (j < n - 1 && nums[j] == nums[j + 1]) j++;
		}
		while (i < n - 1 && nums[i] == nums[i + 1]) i++;
	}
	return res;
}

//longest consecutive sequence

//first sort the array and find the longest consecutive sequence
//timeO(nlogn) and space O(N)

int longestConsecutive(vector<int>& nums) {


	sort(nums.begin(), nums.end());
	if (!nums.size()) return 0;

	int cnt = 1;
	int maxlength = 1;

	for (int i = 1; i < nums.size(); ++i) {

		if (nums[i] == nums[i - 1]) continue;
		if (nums[i] == nums[i - 1] + 1) cnt++;
		else cnt = 1;
		maxlength = max(maxlength, cnt);
	}

	return maxlength;
}

//for every element check if its smaller element is in hashset or not if not then find maximum sequence
//length and if smaller element present the continue
//time O(N) and space O(N)

int longestConsecutive(vector<int>& nums) {

	unordered_map<int, int> mp;
	for (auto k : nums) {
		mp[k]++;
	}

	int cnt = 0;
	int maxlength = 0;

	for (auto k : nums) {
		if (mp.find(k - 1) == mp.end()) {
			cnt = 1;
			while (mp.find(k + 1) != mp.end()) {
				cnt++;
				k++;
			}
			maxlength = max(cnt, maxlength);
		}
	}
	return maxlength;
}

//largest subarray with zero sum

//generate all subarray and if sum is zero find the maximum length of such subarrays
//time O(n^2) and space O(1)

//use hashmap find the prefix sum and store the prefix sum with the first index where that prefix sum
//occurs if we have sum which is already in prefix sum then that array-prefix sum index is zero subarray
//and if sum == 0 then also we get zero sub array find the largest length of such sub arrays

int maxLen(int A[], int n)
{
	int sum = 0;
	int maxlength = 0;

	unordered_map<int, int> mp;

	for (int i = 0; i < n; ++i) {

		sum += A[i];
		if (sum == 0) maxlength = max(maxlength, i + 1);
		else if (mp.find(sum) != mp.end()) {
			maxlength = max(maxlength, i - mp[sum]);
		}
		else mp[sum] = i;
	}
	return maxlength;
}


//count number of subarray with xor equal to k

//generate all the subarray and check if its xor is k or not and increase the couter accordingly

//create a prefix or array and if xor is k cnt++ also y = xr^k and count the frequency of y and add it to counter

int Solution::solve(vector<int> &A, int B) {

	unordered_map<int, int> mp;

	int xr = 0, y;
	int cnt = 0;

	for (int i = 0; i < A.size(); ++i) {

		xr = xr ^ A[i];
		y = xr ^ B;

		if (xr == B) cnt++;
		if (mp.find(y) != mp.end()) {
			cnt += mp[y];
		}
		mp[xr]++;
	}
	return cnt;
}


//longest substring with non-reapeating characters

//brute force generate all the substring and check if they contain repeating characters or not
//time O(N^2 log N) and space O(N)

//use two pointers left and right and if the character at right already in hash set shift the left pointer
//time O(nlog n) and space O(n)

int lengthOfLongestSubstring(string s) {

	unordered_map<char, int> mp;

	int left = 0, right = 0;
	int n = s.size();
	int len = 0;


	while (right < n) {

		if (mp.find(s[right]) != mp.end() && mp[s[right]] >= 1) {
			mp[s[left]]--;
			left++;
		}
		else {
			mp[s[right]]++;
			right++;
			len = max(len, right - left);
		}
	}
	return len;
}
