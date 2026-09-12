class Solution {
public:
    struct State {
        long long score = 0;
        array<int, 4> ids = {-1, -1, -1, -1};
        int cnt = 0;
    };

    int n;
    vector<vector<int>> a;
    vector<int> nxt;
    vector<array<State, 5>> dp;
    vector<array<bool, 5>> vis;

    bool better(const State& x, const State& y) {
        if (x.score != y.score)
            return x.score > y.score;

        for (int i = 0; i < min(x.cnt, y.cnt); i++) {
            if (x.ids[i] != y.ids[i])
                return x.ids[i] < y.ids[i];
        }

        return x.cnt < y.cnt;
    }

    State solve(int i, int k) {
        if (i >= n || k == 0)
            return State();

        if (vis[i][k])
            return dp[i][k];

        vis[i][k] = true;

        State skip = solve(i + 1, k);
        State take = solve(nxt[i], k - 1);

        State cur;
        cur.score = a[i][2] + take.score;
        cur.cnt = take.cnt + 1;

        cur.ids[0] = a[i][3];

        for (int j = 0; j < take.cnt; j++)
            cur.ids[j + 1] = take.ids[j];

        sort(cur.ids.begin(), cur.ids.begin() + cur.cnt);

        dp[i][k] = better(cur, skip) ? cur : skip;

        return dp[i][k];
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        n = intervals.size();

        vector<pair<vector<int>, int>> v;

        for (int i = 0; i < n; i++)
            v.push_back({intervals[i], i});

        sort(v.begin(), v.end());

        a.resize(n);

        for (int i = 0; i < n; i++) {
            a[i] = v[i].first;
            a[i].push_back(v[i].second);
        }

        nxt.resize(n);

        for (int i = 0; i < n; i++) {
            int lo = i + 1;
            int hi = n;

            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;

                if (a[mid][0] > a[i][1])
                    hi = mid;
                else
                    lo = mid + 1;
            }

            nxt[i] = lo;
        }

        dp.resize(n);
        vis.resize(n);

        State res = solve(0, 4);

        return vector<int>(res.ids.begin(), res.ids.begin() + res.cnt);
    }
};