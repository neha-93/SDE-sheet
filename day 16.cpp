//Minimum number of characters to remove from front to make string palidrome

//brute force check if string is palidrome or not if not delete the last character and check
//if the rest of the string is palindrome or not at last return the number of deleted characters
//time n^2

//reverse the string and create a new string with string + $ + reverse string
//ans would be size of string - lps of the new string

int Solution::solve(string A) {

	string s = A;
	reverse(s.begin(), s.end());

	string pat = A + '$' + s;

	int n = pat.size();
	int i = 1, len = 0;
	int lps[n];
	lps[0] = 0;

	while (i < n) {

		if (pat[i] == pat[len]) lps[i++] = ++len;
		else if (len != 0) len = lps[len - 1];
		else lps[i++] = 0;
	}

	return A.size() - lps[n - 1];
}

//check if two strings are anagrams or not

//say we sort the two string and then compare them
//time O(nlogn)

//use maps
//time O(n) space O(n)

bool isAnagram(string a, string b) {

	// Your code here
	int n = a.size();
	int m = b.size();

	if (n != m) return false;

	unordered_map<char, int> mp;

	for (int i = 0; i < n; ++i) mp[a[i]]++;

	for (int i = 0; i < m; ++i)
		if (mp.find(b[i]) != mp.end() && mp[b[i]] >= 1) mp[b[i]]--;
		else return false;

	return true;

}


//count and say

string countAndSay(int n) {

	string res = "1";

	while (--n) {

		string ans;
		for (int i = 0; i < res.size(); ++i) {

			int cnt = 1;
			while (i < res.size() - 1 && res[i] == res[i + 1]) cnt++, i++;
			ans += to_string(cnt) + res[i];

		}
		res = ans;
	}
	return res;
}

//comparing versions

int compareVersion(string version1, string version2) {

	int n1 = 0, n2 = 0;

	int i = 0, j = 0;
	int m = version1.size();
	int n = version2.size();

	while (i < m && j < n) {

		while (i < m && version1[i] != '.') n1 = 10 * n1 + (version1[i] - '0'), i++;
		while (j < n && version2[j] != '.') n2 = 10 * n2 + (version2[j] - '0'), j++;

		//cout << n1 << " " << n2 << endl;
		if (n1 < n2) return -1;
		else if (n1 > n2) return 1;

		n1 = 0, n2 = 0;
		i++, j++;
	}
	while (i < m) {
		while (i < m && version1[i] != '.') n1 = 10 * n1 + (version1[i] - '0'), i++;

		if (n1) return 1;
		i++;
	}
	while (j < n) {
		while (j < n && version2[j] != '.') n2 = 10 * n2 + (version2[j] - '0'), j++;
		if (n2) return -1;
		j++;
	}
	return 0;
}

