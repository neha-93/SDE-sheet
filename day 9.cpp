//subset sum

//use backtracking algorithm
//time O(2^n) space O(2^nlog(2^n))

void subset(vector<int> &arr, int s, int n, vector<int> &ans, int sum) {

	if (s == n) {
		ans.push_back(sum);
		return;
	}

	subset(arr, s + 1, n, ans, sum + arr[s]);
	subset(arr, s + 1, n, ans, sum);
}


public:
vector<int> subsetSums(vector<int> arr, int N)
{

	vector<int> ans;

	subset(arr, 0, N, ans, 0);
	sort(ans.begin(), ans.end());

	return ans;
}

//subset sum avoiding duplicates

void findSubsets(vector<int>& nums, int s, vector<int>& seq, vector<vector<int>>& ans) {

	ans.push_back(seq);

	for (int i = s; i < nums.size(); ++i) {

		if (i != s && nums[i] == nums[i - 1]) continue;
		seq.push_back(nums[i]);
		findSubsets(nums, i + 1, seq, ans);
		seq.pop_back();
	}
}

public:
vector<vector<int>> subsetsWithDup(vector<int>& nums) {

	vector<vector<int>> ans;

	vector<int> seq;
	sort(nums.begin(), nums.end());
	findSubsets(nums, 0, seq, ans);
	return ans;
}

//combination sum

void findcombination(vector<int>& candidates, int s, int t, vector<int>& st, vector<vector<int>>& ans) {
	if (s == candidates.size()) {
		if (t == 0) ans.push_back(st);
		return;
	}
	if (candidates[s] <= t) {
		st.push_back(candidates[s]);
		findcombination(candidates, s, t - candidates[s], st, ans);
		st.pop_back();
	}

	findcombination(candidates, s + 1, t, st, ans);
}

public:
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {

	vector<vector<int>> ans;
	vector<int> st;

	findcombination(candidates, 0, target, st, ans);

	return ans;
}

//combination sum avoiding duplicates

void combination(vector<int>& candidates, int s, int t, vector<int>& seq, vector<vector<int>>& ans) {
	if (t == 0) ans.push_back(seq);
	if (t < 0) return;

	for (int i = s; i < candidates.size(); ++i) {

		if (i != s && candidates[i] == candidates[i - 1]) continue;
		seq.push_back(candidates[i]);
		combination(candidates, i + 1, t - candidates[i], seq, ans);
		seq.pop_back();
	}
}

public:
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {

	vector<vector<int>> ans;
	vector<int> seq;

	sort(candidates.begin(), candidates.end());

	combination(candidates, 0, target, seq, ans);

	return ans;
}

//palidromic partitioning
//check for if a substring is palindrome or not and if it is palindrome then recursively check for the rest
//of the string if it is palidrome or not and if we reach end of the string and then all the substrings
//would be palidrome and we could add this seq to our answer.

bool isPalindrome(string s) {

	int n = s.size();
	for (int i = 0; i < n / 2; ++i) {
		if (s[i] != s[n - i - 1]) return false;
	}
	return true;
}

void findPartitions(string s, int st, vector<string>& pat, vector<vector<string>>& ans) {

	if (st == s.size()) {
		ans.push_back(pat);
		return;
	}
	string sub;

	for (int i = st; i < s.size(); ++i) {

		sub = s.substr(st, i - st + 1);

		if (isPalindrome(sub)) {
			pat.push_back(sub);
			findPartitions(s, i + 1, pat, ans);
			pat.pop_back();
		}

	}
}

public:
vector<vector<string>> partition(string s) {

	vector<vector<string>> ans;
	vector<string> pat;

	findPartitions(s, 0, pat, ans);

	return ans;
}

//Permutation sequence

//generate all the permutations and sort all the permutations and return the kth permutation

void allPermutations(string& per, int s, int e, vector<string>& allPer) {

	if (s == e) allPer.push_back(per);

	for (int i = s; i <= e; ++i) {
		swap(per[s], per[i]);
		allPermutations(per, s + 1, e, allPer);
		swap(per[s], per[i]);
	}
}
public:
string getPermutation(int n, int k) {

	string permutation;
	vector<string> allPer;

	for (int i = 1; i <= n; ++i) {
		permutation += to_string(i);
	}

	allPermutations(permutation, 0, n - 1, allPer);

	sort(allPer.begin(), allPer.end());

	return allPer[k - 1];
}

//second method
//time O(N^2) space O(N)

string getPermutation(int n, int k) {

	string nums;
	int fact = 1;

	for (int i = 1; i < n; ++i) {
		fact *= i;
		nums += to_string(i);
	}

	nums += to_string(n);
	string ans;

	int id = k - 1;

	while (1) {

		ans.push_back(nums[id / fact]);
		nums.erase(nums.begin() + id / fact);

		if (nums.size() == 0) break;
		id = id % fact;
		fact = fact / nums.size();

	}
	return ans;
}