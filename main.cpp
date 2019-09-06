#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <map>

using namespace std;

void printuUnordered_map(unordered_map<int, int>& myMap)
{
    unordered_map<int, int>::iterator it = myMap.begin();
    for (; it != myMap.end(); ++it){
        cout << "(" << it->first<<", " << it->second << ") ";
    }
}
void printVector(vector<pair<int, int>>& myVector)
{
    vector<pair<int, int>>::iterator it = myVector.begin();
    for (; it != myVector.end(); ++it){
        cout << "(" << it->first<<", " << it->second << ") ";
    }
}
void printVector(vector<int>& myVector)
{
    vector<int>::iterator it = myVector.begin();
    cout << "[";
    for (; it != myVector.end(); ++it){
        if((it + 1) == myVector.end()){
            cout << *(it);
        } else{
            cout << *(it) << ", ";
        }
    }
    cout << "]";
}
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
// 自定义比较器，从大到小排序
struct cmp{
    bool operator()(const ListNode* node1, const ListNode* node2){
        return node1->val > node2->val;
    }
};
// 自定义比较器，从大到小排序
struct cmp1{
    bool operator()(const pair<int, int> temp1, const pair<int, int> temp2){
        return temp1.second > temp2.second;
    }
};
// 自定义比较器，从大到小排序
struct cmp2{
    bool operator()(const pair<string, int>& a, const pair<string, int>& b){
        return a.second > b.second;
    }
};

// Definition for a binary tree node.
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
class Solution{
public:
    /*
     * 1114. 按序打印(多线程)
     */

    /*
     * 763. 划分字母区间
     *
     * 字符串 S 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一个字母只会出现在其中的一个片段。
     * 返回一个表示每个字符串片段的长度的列表。
     *
     * 输入: S = "ababcbacadefegdehijhklij"
     * 输出: [9,7,8]
     */
    vector<int> partitionLabels(string s) {
        // 标记每个字母最后出现的位置
        int lastIndex[26]{};
        vector<int> res;
        for(int i = s.size() - 1; i >= 0; --i){
            if(lastIndex[s[i] - 'a'] == 0){
                lastIndex[s[i] - 'a'] = i;
            }
        }

        // 找到每个片段的最大延伸
        int i = 0;
        while(i < s.size()) {
            int cur = i;
            int end = lastIndex[s[cur] - 'a'];
            while(cur <= end){
                end = max(end, lastIndex[s[cur++] - 'a']);
            }
            res.push_back(end - i + 1);
            i = end + 1;
        }
        return res;
    }
    /*
     * 239. 滑动窗口最大值
     *
     */
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if(k < 1 || k > nums.size() || nums.size() == 0)
            return res;
        queue<int> curQ;    // 存储index
        for(int i=0; i<nums.size(); ++i){
            while(!curQ.empty() && nums[i] >= nums[curQ.front()]){
                curQ.pop();
            }
            curQ.push(i);
            if(i >= k - 1){
                while(!curQ.empty() && i - curQ.front() >= k){
                    curQ.pop();
                }
                res.push_back(nums[curQ.front()]);
                if(i - curQ.front() >= k - 1)
                    curQ.pop();
            }

        }
        return res;
    }
     /*
      * 347. 前 K 个高频元素
      *
      * 给定一个非空的整数数组，返回其中出现频率前 k 高的元素。
      *
      * 思路： （使用堆）遍历一遍数组，使用一个unordered_map<int, int>，first 为 key，second 为 key 出现的次数
      *          遍历一遍 unordered_map ，将 unordered_map 中所有元素重新存在一个 vector<pair<int, int>> 中
      *          对 vector<pair<int, int>> 按照 second 从大到小排序
      *          输出 vector<pair<int, int>> 中前k个元素的 first
      */
    vector<int> topKFrequent1(vector<int>& nums, int k) {
        vector<int> res;
        // 统计频率
        unordered_map<int, int> myMap;
        for(int i=0; i<nums.size(); i++){
            auto it = myMap.find(nums[i]);
            if(it != myMap.end()){
                it->second++;
            }else{
                myMap.insert(make_pair(nums[i], 1));
            }
        }
        if(k > myMap.size())
            return res;
        priority_queue<pair<int, int>, vector<pair<int, int>>, cmp1> minHeap; // priority_queue 默认大根堆，传入大于比较器建立小根堆
        auto it = myMap.begin();
        for(int i=0; (i<k) && (it != myMap.end()); ++i, ++it){
            minHeap.push(make_pair(it->first, it->second));
        }
        while(it != myMap.end()){
            if(it->second > minHeap.top().second){
                minHeap.pop();
                minHeap.push(make_pair(it->first, it->second));
            }
            ++it;
        }
        while(!minHeap.empty()){
            res.push_back(minHeap.top().first);
            minHeap.pop();
        }
        return res;
    }
    /*
     * 347. 前 K 个高频元素
     *
     * 给定一个非空的整数数组，返回其中出现频率前 k 高的元素。
     *
     * 思路： 遍历一遍数组，使用一个unordered_map<int, int>，first 为 key，second 为 key 出现的次数
     *          遍历一遍 unordered_map ，将 unordered_map 中所有元素重新存在一个 vector<pair<int, int>> 中
     *          对 vector<pair<int, int>> 按照 second 从大到小排序
     *          输出 vector<pair<int, int>> 中前k个元素的 first
     */
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> res;
        // 统计频率
        unordered_map<int, int> myMap;
        for(int i=0; i<nums.size(); i++){
            auto it = myMap.find(nums[i]);
            if(it != myMap.end()){
                it->second++;
            }else{
                myMap.insert(make_pair(nums[i], 1));
            }
        }
        if(k > myMap.size())
            return res;
        vector<pair<int, int>> temp;
        for(auto it = myMap.begin(); it != myMap.end(); ++it){
            temp.push_back(make_pair(it->first, it->second));
        }
        sort(temp.begin(), temp.end(), cmp1());
        for(int i=0; i<k; ++i){
            res.push_back(temp[i].first);
        }
        return res;
    }

    /*
     * 236. 二叉树的最近公共祖先
     * （不太理解）
     * 在左、右子树中分别查找是否包含p或q，如果（两种情况：左子树包含p，右子树包含q/左子树包含q，右子树包含p），那么此时的根节点就是最近公共祖先
     * 如果左子树包含p和q，那么到root->left中查找，最近公共祖先在左子树里面
     * 如果右子树包含p和q，那么到root->right中查找，最近公共祖先在右子树里面
     */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL || root == p || root == q)
            return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        return left == NULL ? right : (right == NULL ? left : root);
    }
    /*
     * 124. 二叉树中的最大路径和
     *
     * 给定一个非空二叉树，返回其最大路径和。
     * 本题中，路径被定义为一条从树中任意节点出发，达到任意节点的序列。该路径至少包含一个节点，且不一定经过根节点。
     */
    int maxSum = INT8_MIN;
    int maxPathSum(TreeNode* root) {
        getMax(root);
        return maxSum;
    }
    int getMax(TreeNode* root) { // 得到从某根出发往下的最大的一条路径和
        if(root == NULL)
            return 0;
        int leftMax = max(getMax(root->left), 0); //左子树最大贡献值
        int rightMax = max(getMax(root->right), 0); //右子树最大贡献值
        int newPath = root->val + leftMax + rightMax; //新的路径，可以从当前节点的左子树到右子树
        maxSum = max(maxSum, newPath); //判断经过当前节点的新路径是否可以替代已经存在的最大路径值
        return max(leftMax, rightMax) + root->val; // 返回通过当前节点的最大路径
    }

    /*
     * 63.不同路径
     * （动态规划）
     */
    int uniquePaths2(int m, int n) {
        vector<int> dp(m * n, 1);
        for(int i=1; i<m; i++){
            for(int j=1; j<n; j++){
                dp[i * n + j] = dp[(i-1) * n + j] + dp[i * n + j - 1];
            }
        }
        return dp[m * n - 1];
    }
    /*
     * 63.不同路径
     * （递归）：超时
     */
    int uniquePaths(int m, int n) {
        int row = 0, col = 0;
        return uniquePaths(m, n, row, col);
    }
    int uniquePaths(int m, int n, int row, int col) {
        if(0 <= row && row < m && 0 <= col && col < n){
            if(row == m - 1 && col == n - 1){
                return 1;
            }
            // 向右
            int right = uniquePaths(m, n, row, col + 1);
            // 向下
            int down  = uniquePaths(m, n, row + 1, col);
            return right + down;
        }
        return 0;
    }
    /*
     * 43. 字符串相乘
     *
     * 给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。
     *
     * 说明：
     * num1 和 num2 的长度小于110。
     * num1 和 num2 只包含数字 0-9。
     * num1 和 num2 均不以零开头，除非是数字 0 本身。
     * 不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。
     */
    string multiply(string num1, string num2){

    }


    /*
     * 4. 寻找两个有序数组的中位数
     */
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        priority_queue<int, vector<int>, less<int>> maxHeap;
        int i=0, j=0;
        while(i < nums1.size() || j < nums2.size()){
            int cur;
            // 找到数
            if(i < nums1.size() && j < nums2.size())
                cur = nums1[i] < nums2[j] ? nums1[i++] : nums2[j++];
            else if(i < nums1.size())
                cur = nums1[i++];
            else if(j < nums2.size())
                cur = nums2[j++];
            if(!maxHeap.empty() && cur < maxHeap.top()){
                maxHeap.push(cur);
            }else{
                minHeap.push(cur);
            }
            maintainTwoHeap(minHeap, maxHeap);

        }
        double res = 0;

        if((nums1.size() + nums2.size()) % 2 == 0)
            res = (minHeap.top() + maxHeap.top()) / 2.0;
        else
            res = (minHeap.size() > maxHeap.size() ? minHeap.top() : maxHeap.top()) / 1.0;
        return res;
    }
    void maintainTwoHeap(priority_queue<int, vector<int>, greater<int>> &minHeap, priority_queue<int, vector<int>, less<int>> &maxHeap){
        int diff = minHeap.size() - maxHeap.size();
        if(abs(diff) > 1){
            if(minHeap.size() - maxHeap.size() > 0){
                int minTop = minHeap.top();
                minHeap.pop();
                maxHeap.push(minTop);
            }else{
                int maxTop = maxHeap.top();
                maxHeap.pop();
                minHeap.push(maxTop);
            }
            maintainTwoHeap(minHeap, maxHeap);
        }
    }
    /*
    * 使用数组创建单链表
    */
    ListNode* createList(vector<int> array){
        if(array.size() <= 0)
            return NULL;
        ListNode* pHead = new ListNode(array[0]);
        ListNode* pPreTemp = pHead;
        for(int i=1; i<array.size(); i++){
            ListNode* pTemp = new ListNode(array[i]);
            pPreTemp->next = pTemp;
            pPreTemp = pTemp;
        }
        return pHead;
    }
    /*
     * 打印链表
     */
    void PrintList(ListNode* pHead){
        ListNode* p = pHead;
        while (p){
            if(p->next)
                cout<<p->val<<"->";
            else
                cout<<p->val<<endl;
            p = p->next;
        }
    }
    bool isValid(string s) {
        if(s.length() == 0)
            return true;
        stack<char> mystack;
        char* pCh = &s[0];
        while(*pCh != '\0'){
            if(*pCh == '(' || *pCh == '{' || *pCh == '['){
                mystack.push(*pCh);
            }else if(*pCh == ')' || *pCh == '}' || *pCh == ']'){
                if(!mystack.empty() && isMatch(mystack.top(), *pCh)){
                    mystack.pop();
                }else{
                    return false;
                }
            }else{  // 非法字符
                return false;
            }
            pCh++;
        }
        if(mystack.empty())
            return true;
        return false;
    }
    bool isMatch(char a, char b){   // 判断是否匹配
        if((a == '(' && b == ')') || (a == '{' && b == '}') || (a == '[' && b == ']'))
            return true;
        return false;
    }
    /*
     * 合并K个排序链表
     */
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 注意：小根堆传入的比较器是greater，因此，自定义比较器时，也应该写成greater
        priority_queue < ListNode* , vector<ListNode*>, cmp> minHeap;
        for(int i=0; i<lists.size(); i++){
            minHeap.push(lists[i]);
        }
        ListNode* resHead = new ListNode(0);
        ListNode* tail = resHead;
        while (!minHeap.empty()){
            ListNode* cur = minHeap.top();
            minHeap.pop();
            ListNode* curNext = cur->next;
            cur->next = tail->next;
            tail->next = cur;
            tail = cur;
            if(curNext)
                minHeap.push(curNext);
        }
        return resHead->next;
    }
};
int main() {
    Solution solution;

    string str = "ababcbacadefegdehijhklij";
    vector<int> res = solution.partitionLabels(str);
    for(auto it : res){
        cout<<it<<" ";
    }

//    vector<int> nums = {7,2,4};
//    vector<int> res = solution.maxSlidingWindow(nums, 2);
//    for(auto it : res){
//        cout<<it<<" ";
//    }

//    vector<string> arr = {"i", "love", "leetcode", "i", "love", "coding"};
//    vector<string> res = solution.topKFrequent(arr, 2);
//    for(auto it : res){
//        cout<<it<<" ";
//    }


//    cout<<solution.uniquePaths2(23, 12);

//    vector<int> arr1 = {};
//    vector<int> arr2 = {3};
//
//    cout<<solution.findMedianSortedArrays(arr1, arr2);

//    vector<ListNode*> vec;
//    ListNode* l1 = solution.createList(arr1);
//    ListNode* l2 = solution.createList(arr2);
//    vec.push_back(l1);
//    vec.push_back(l2);
//    ListNode* res = solution.mergeKLists(vec);
//    solution.PrintList(res);


//    string str = "()";
//    vector<int> vec;
//    vec.pop_back();
//    cout<<solution.isValid(str);
    return 0;
}