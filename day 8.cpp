//Meeting room problem

//sort the meetings along the endtime and for each meeting check if the start time of next meeting is greater
//the endtime of current meeting if it is greater the increase cnt and update the endtime of the meeting


static bool comp(pair<int, int>& a, pair<int, int>& b) {
	return a.second < b.second;
}
public:
//Function to find the maximum number of meetings that can
//be performed in a meeting room.
int maxMeetings(int start[], int end[], int n)
{

	if (!n) return 0;

	vector<pair<int, int>> t(n);
	for (int i = 0; i < n; ++i) {
		t[i] = {start[i], end[i]};
	}
	sort(t.begin(), t.end(), comp);

	int endtime = t[0].second;
	int cnt = 1;

	for (int i = 1; i < n; ++i) {
		if (t[i].first > endtime) {
			cnt++;
			endtime = t[i].second;
		}
	}
	return cnt;
}

//platform required for train arrival

//sort the trains according to the arrival time and then maintain a priority queue for the endtime and if the
//start time of the train is greater than the smallest endtime then extend the endtime else add platform count
//and the end time to the priority queue

int findPlatform(int arr[], int dep[], int n)
{
	if (!n) return 0;
	vector<pair<int, int>> t(n);

	for (int i = 0; i < n; ++i) {
		t[i] = {arr[i], dep[i]};
	}

	sort(t.begin(), t.end());

	priority_queue<int, vector<int>, greater<int>> pq;

	int platform = 1;
	pq.push(t[0].second);

	for (int i = 1; i < n; ++i) {

		if (t[i].first > pq.top()) {
			pq.pop();
		}
		else platform++;
		pq.push(t[i].second);
	}
	return platform;
}

//Job Scheduling

//sort the job in decreasing order of profit
//for each job check for and empty slot and fill that slot with the job and add the profit

struct Job
{
	int id;	 // Job Id
	int dead; // Deadline of job
	int profit; // Profit if job is over before or on deadline
};

vector<int> JobScheduling(Job arr[], int n)
{

	sort(arr, arr + n, compare);

	bool slot[n];
	memset(slot, 0, sizeof slot);
	int task = 0, profit = 0;

	for (int i = 0; i < n; ++i) {

		for (int j = min(n, arr[i].dead) - 1; j >= 0; --j) {
			if (!slot[j]) {
				task++;
				profit += arr[i].profit;
				slot[j] = 1;
				break;
			}
		}
	}
	return {task, profit};
}

//Fractional Knapsack

//sort the items according to their decreasing profit by weight ratio value to weight and add the profit
//till the bag becomes full

struct Item {
	int value;
	int weight;
};


class Solution
{

	static bool comp(pair<double, Item>& a, pair<double, Item>& b) {
		return a.first > b.first;
	}
public:
	//Function to get the maximum total value in the knapsack.
	double fractionalKnapsack(int W, Item arr[], int n)
	{
		vector<pair<double, Item>> v(n);

		double r;
		for (int i = 0; i < n; ++i) {
			r = (double)arr[i].value / arr[i].weight;
			v[i] = {r, arr[i]};
		}

		sort(v.begin(), v.end(), comp);

		int w = 0, i = 0;
		double ans = 0;
		int weightToAdd;

		while (w < W && i < n) {

			if (w + v[i].second.weight > W) {
				ans += (W - w) * v[i].first;
				w = W;
			}
			else {
				ans += v[i].second.value;
				w += v[i].second.weight;
			}
			i++;
		}
		return ans;
	}