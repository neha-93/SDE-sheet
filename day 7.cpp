//copying linked list with random pointers

//use hashmap to create new node
//and in the next iteration copy the pointers

Node* copyRandomList(Node* head) {
	unordered_map<Node*, Node*> mp;

	if (!head) return NULL;

	Node *clonedHead = new Node(head->val);
	mp[head] = clonedHead;

	Node *cur = head->next;

	while (cur) {
		Node *newNode = new Node(cur->val);
		mp[cur] = newNode;
		cur = cur->next;
	}

	cur = head;

	while (cur) {
		mp[cur]->next = mp[cur->next];
		mp[cur]->random = mp[cur->random];
		cur = cur->next;
	}

	return clonedHead;
}

//3 sum

//first use 3 loops and if sum is zero add to answer
//sort the array inside a loop use two pointer for the 2 sum

vector<vector<int>> threeSum(vector<int>& nums) {

	vector<vector<int>> ans;
	int n = nums.size();
	sort(nums.begin(), nums.end());
	for (int i = 0; i < n; ++i) {

		int low = i + 1;
		int high = n - 1;

		while (low < high) {
			int sum = nums[i] + nums[low] + nums[high];
			if (sum == 0) {
				ans.push_back({nums[i], nums[low], nums[high]});
				while (low < n - 1 && nums[low] == nums[low + 1]) low++;
				while (high > 0 && nums[high] == nums[high - 1]) high--;
				low++;
				high--;
			}

			else if (sum < 0) low++;
			else high--;
		}
		while (i < n - 1 && nums[i] == nums[i + 1]) i++;
	}
	return ans;
}


//Rain water trapping


//make the prefix and suffix array of the maximum building height and the add
//water += min(pre[i],suf[i]) - height[i]
//time O(N) space O(N)

int trap(vector<int>& height) {

	int n = height.size();
	int pre[n], suf[n];

	pre[0] = height[0];
	for (int i = 1; i < n; ++i) {
		pre[i] = max(pre[i - 1], height[i]);
	}
	suf[n - 1] = height[n - 1];
	for (int i = n - 2; i >= 0; --i) {
		suf[i] = max(suf[i + 1], height[i]);
	}

	int water = 0;
	for (int i = 0; i < n; ++i) {
		water += min(pre[i], suf[i]) - height[i];
	}
	return water;
}


//use two pointer approach
//time O(N) space O(1)

int trap(vector<int>& height) {

	int n = height.size();
	int left = 0, right = n - 1;
	int leftMax = height[left], rightMax = height[right];

	int water = 0;
	int trap;

	while (left <= right) {

		if (height[left] <= height[right]) {
			trap = min(leftMax, height[right]) - height[left];
			if (trap > 0) water += trap;
			leftMax = max(height[left], leftMax);
			left++;
		}
		else {
			trap = min(height[left], rightMax) - height[right];
			if (trap > 0) water += trap;
			rightMax = max(height[right], rightMax);
			right--;
		}
		//cout << left << " " << right << " " << trap << endl;
	}
	return water;
}

//remove duplicate elements from the array

//tell that we will use sets or maps to store the unique elements and return the size of the hashset

//tell the 2-pointer approach

int removeDuplicates(vector<int>& nums) {

	int n = nums.size();
	if (!n) return 0;

	int s = 0, c = 1;

	while (c < n) {
		if (nums[c] != nums[c - 1]) nums[++s] = nums[c];
		c++;

	}
	return s + 1;
}

//maximum consecutive ones

//maintain 2 pointers one count and other maximum

int findMaxConsecutiveOnes(vector<int>& nums) {

	int cnt = 0;
	int maxi = 0;

	for (auto i = 0; i < nums.size(); ++i) {

		if (nums[i] == 1) cnt++;
		else cnt = 0;

		maxi = max(cnt, maxi);
	}
	return maxi;
}