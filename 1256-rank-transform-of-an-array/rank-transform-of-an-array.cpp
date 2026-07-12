class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> temp = arr;

        sort(temp.begin(), temp.end());

        unordered_map<int, int> rank;
        int r = 1;

    for (int i = 0; i < temp.size(); i++) {
    int x = temp[i];

    if (rank.find(x) == rank.end()) {
        rank[x] = r;
        r++;
    }
}
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = rank[arr[i]];
        }
        return arr;
    }
};