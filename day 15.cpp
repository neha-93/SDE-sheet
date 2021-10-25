//Reverse words in a string

//used stack
//time O(N) and space O(N)

string reverseWords(string S)
{
	stack<string> st;
	int prev = 0;

	for (int i = 0; i < S.size(); ++i) {

		if (S[i] == '.') {
			st.push(S.substr(prev, i - prev));
			prev = i + 1;
		}
	}

	st.push(S.substr(prev, S.size() - prev));

	string rev;

	while (!st.empty()) {
		rev += st.top();
		rev += '.';
		st.pop();
	}
	rev.pop_back();
	return rev;
}

//Longest palindromic string

//first tell the brute force approach that we will generate all possible substrings
//and for each substring check if it is a prlidrome or not

//time O(n^3)


//tell the dp approach that all substring of size 1 is palindrome and all substring of size 2
//are palindrome if adjacent elements are same
//for larger size of end elements are equal and the substring is a palidrome then the string
//is also a palindrome

string longestPalin (string S) {
	// code here

	int n = S.size();
	int dp[n + 1][n + 1];
	memset(dp, 0, sizeof(dp));

	int start = 0, maxlength = 1;

	for (int i = 0; i < n; ++i) dp[i][i] = 1;
	for (int i = 0; i < n - 1; ++i) {
		if (S[i] == S[i + 1]) {
			dp[i][i + 1] = 1;
			if (maxlength < 2) {
				maxlength = 2;
				start = i;
			}
		}
	}
	for (int k = 3; k <= n; ++k) {
		for (int i = 0; i <= n - k; ++i) {
			int j = i + k - 1;

			if (S[i] == S[j] && dp[i + 1][j - 1]) {
				dp[i][j] = 1;
				if (maxlength < k) {
					maxlength = k;
					start = i;
				}
			}
		}
	}

	return S.substr(start, maxlength);

}


//roman to integer

int romanToInt(string s) {

	int n = s.size();
	int ans = 0;
	int i;

	for (i = 0; i < n - 1; ++i) {

		if (s[i] == 'I') {
			if (s[i + 1] == 'V') ans += 4, i++;
			else if (s[i + 1] == 'X') ans += 9, i++;
			else ans += 1;
		}
		else if (s[i] == 'X') {
			if (s[i + 1] == 'C') ans += 90, i++;
			else if (s[i + 1] == 'L') ans += 40, i++;
			else ans += 10;
		}
		else if (s[i] == 'C') {
			if (s[i + 1] == 'D') ans += 400, i++;
			else if (s[i + 1] == 'M') ans += 900, i++;
			else ans += 100;
		}
		else if (s[i] == 'V') ans += 5;
		else if (s[i] == 'L') ans += 50;
		else if (s[i] == 'D') ans += 500;
		else ans += 1000;
	}

	if (i == n - 1) {
		if (s[n - 1] == 'I') ans += 1;
		else if (s[n - 1] == 'V') ans += 5;
		else if (s[n - 1] == 'X') ans += 10;
		else if (s[n - 1] == 'L') ans += 50;
		else if (s[n - 1] == 'C') ans += 100;
		else if (s[n - 1] == 'D') ans += 500;
		else ans += 1000;
	}

	return ans;

}

//integer to roman

string intToRoman(int num) {

	string M[] = {"", "M", "MM", "MMM"};
	string C[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
	string X[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
	string I[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

	string s = M[num / 1000] + C[(num % 1000) / 100] + X[(num % 100) / 10] + I[num % 10];

	return s;
}

//implement strstr (find a string is present in another string)

//first tell brute forces that for each index i->0 to m-n we will check if the pattern matches
//time O(n*m)

//use the kmp algorithm for the pattern to match make a lps array (here find the longest proper
//prefix which is also a suffix) and using this lps array match the pattern to the string

int strStr(string haystack, string needle) {

	int n = haystack.size(), m = needle.size();

	if (m == 0) return 0;

	int lps[m];
	lps[0] = 0;
	int len = 0, i = 1;

	while (i < m) {

		if (needle[i] == needle[len]) lps[i++] = ++len;
		else if (len != 0) len = lps[len - 1];
		else lps[i++] = 0;
	}

	int j = 0;
	i = 0;

	while (i < n) {

		if (haystack[i] == needle[j]) i++, j++;
		else if (j != 0) j = lps[j - 1];
		else i++;
		if (j == m) return i - j;
	}

	return -1;
}

//using rabin karp
//rolling hash function

int strStr(string haystack, string needle) {

	int q = 1e6 + 7;
	int n = haystack.size();
	int m = needle.size();

	int h = 1;
	int d = 256;

	for (int i = 0; i < m - 1; ++i) h = (d * h) % q;

	long long pat = 0, str = 0;

	for (int i = 0; i < m; ++i) {

		pat = (pat * d + needle[i]) % q;
		str = (str * d + haystack[i]) % q;
	}

	for (int i = 0; i <= n - m; ++i) {

		if (pat == str) {

			bool f = true;
			for (int j = 0; j < m; ++j) {
				if (haystack[i + j] != needle[j]) {
					f = false;
					break;
				}
			}
			if (f) return i;
		}
		if (i < n - m) {

			str = (d * (str - h * haystack[i]) + haystack[i + m]) % q;
			if (str < 0) str += q;
		}
	}
	return -1;
}

//implementation of stoi

int myAtoi(string s) {

	int i = 0;
	int n = s.size();
	long long ans = 0;
	const long long cmp = 1e11;
	int f = 0;

	int sign = 1;
	while (i < n) {

		if (s[i] == ' ') {
			if (f) break;
			i++;
			continue;
		}
		else if ((s[i] == '+' || s[i] == '-') && f) break;
		else if (s[i] == '+') sign = 1, f = 1;
		else if (s[i] == '-') sign = -1, f = 1;
		else if (s[i] >= '0' && s[i] <= '9') ans = ans * 10 + s[i] - '0', f = 1;
		else break;
		//cout << ans << " " << sign << endl;

		ans = min(ans, cmp);

		i++;
	}
	ans *= sign;

	if (ans > INT_MAX) ans = INT_MAX;
	if (ans < INT_MIN) ans = INT_MIN;
	return ans;
}

//Longest common prefix

//sort all the string and find the lcp of first and last string

string longestCommonPrefix(vector<string>& strs) {

	sort(strs.begin(), strs.end());

	int n = strs.size();

	int i = 0;
	while (i < strs[0].size() && i < strs[n - 1].size()) {

		if (strs[0][i] != strs[n - 1][i]) return strs[0].substr(0, i);
		i++;
	}
	return strs[0].substr(0, i);
}

//find the smallest and the largest string and the find the longest common prefix

string longestCommonPrefix(vector<string>& strs) {

	string small, large;

	small = large = strs[0];

	for (int i = 1; i < strs.size(); ++i) {
		if (strs[i].compare(small) < 0) small = strs[i];
		if (strs[i].compare(large) > 0) large = strs[i];
	}

	int i = 0;
	while (i < small.size() && i < large.size()) {

		if (small[i] != large[i]) return small.substr(0, i);
		i++;
	}
	return small.substr(0, i);
}


