//number power of two or not

if (ceil(log2(n)) == floor(log2(n))) return true;
else return false;

//count the set bits
//O(n)

int countSetBits(int n)
{
	int i = 0, ans = 0;

	while ((1 << i) <= n) {

		int change = (1 << i);
		int k = 0;

		for (int j = 0; j <= n; ++j) {

			ans += k;
			if (change == 1) {
				k = !k;
				change = 1 << i;
			}
			else change--;
		}
		i++;
	}
	return ans;
}

//count set bits
//O(logn)

int largestPower(int n) {

	int x = 0;
	while (1 << x <= n) x++;
	return x - 1;
}

int countBits(int n) {

	if (n <= 1) return n;

	int x = largestPower(n);
	return x * pow(2, x - 1) + n - pow(2, x) + 1 + countBits(n - pow(2, x));
}

//divide two integers without / operator

//find the msb such that (divisor << i) <= dividend, run loop from i=31 till i>= 0.

int divide(int dividend, int divisor) {

	long long q = 0, t = 0;
	int sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;

	long long d = abs(divisor);
	long long div = abs(dividend);

	for (int i = 31; i >= 0; --i) {

		if (t + (d << i) <= (long long)div) {
			t += (d << i);
			q |= 1LL << i;
		}
	}
	q *= sign;
	return q > INT_MAX ? INT_MAX : q;

}

//power set

//using bit manipulation

vector<string> AllPossibleStrings(string s) {

	vector<string> ans;
	int n = s.size();

	for (int i = 1; i < (1 << n); ++i) {

		string sub;
		for (int j = 0; j < n; ++j) {

			if (i & (1 << j)) sub += s[j];
		}

		ans.push_back(sub);
	}
	sort(ans.begin(), ans.end());
	return ans;
}

//find msb in O(1) time

#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;

	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;

	n++;
	cout << (n >> 1);
	return 0;
}


int setBits(int n) {

	int c;
	for (int i = 31; i >= 0; --i) {

		if ((1 << i)&n) {
			int c = i;
			break;
		}
	}

	return 1 << c;
}

//square of a number without *, pow()

//using recursion

#include <iostream>
using namespace std;

long long square(long long n) {

	if (n <= 1) return n;

	if (n % 2) return 4 * square(n / 2) + 4 * (n / 2) + 1;
	else return 4 * square(n / 2);
}

int main() {
	int n;
	cin >> n;
	n = abs(n);
	cout << square(n);
	return 0;
}

//using bit manipulation

long long square(long long n) {

	long long ans = 0;

	for (int i = 31; i >= 0; --i) {

		int x = (1 << i);
		if (x <= n && n & x) {
			ans += n * x;
		}
	}

	return ans;
}