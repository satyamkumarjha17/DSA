class Solution {
public:
    struct Node {
        int prod;
        long long pref[5];
        long long suff[5];
        long long all[5];

        Node() {
            prod = 0;
            for (int i = 0; i < 5; i++) {
                pref[i] = 0;
                suff[i] = 0;
                all[i] = 0;
            }
        }
    };

    int k;

    Node mergeNode(const Node& A, const Node& B) {
        Node C;

        C.prod = (A.prod * B.prod) % k;

        for (int r = 0; r < k; r++) {
            C.pref[r] = A.pref[r];
            C.suff[r] = B.suff[r];
            C.all[r] = A.all[r] + B.all[r];
        }

        for (int b = 0; b < k; b++) {
            int r = (A.prod * b) % k;
            C.pref[r] += B.pref[b];
        }

        for (int a = 0; a < k; a++) {
            int r = (a * B.prod) % k;
            C.suff[r] += A.suff[a];
        }

        for (int a = 0; a < k; a++) {
            for (int b = 0; b < k; b++) {
                int r = (a * b) % k;
                C.all[r] += A.suff[a] * B.pref[b];
            }
        }

        return C;
    }

    Node makeNode(int x) {
        Node res;
        int r = x % k;

        res.prod = r;
        res.pref[r] = 1;
        res.suff[r] = 1;
        res.all[r] = 1;

        return res;
    }

    vector<int> resultArray(vector<int>& nums,
                            int kInput,
                            vector<vector<int>>& queries) {
        k = kInput;

        int n = nums.size();
        int size = 1;

        while (size < n)
            size <<= 1;

        vector<Node> seg(2 * size);

        for (int i = 0; i < n; i++)
            seg[size + i] = makeNode(nums[i]);

        for (int i = size - 1; i >= 1; i--)
            seg[i] = mergeNode(seg[i << 1], seg[i << 1 | 1]);

        auto update = [&](int pos, int value) {
            int p = size + pos;

            seg[p] = makeNode(value);

            p >>= 1;

            while (p) {
                seg[p] = mergeNode(seg[p << 1], seg[p << 1 | 1]);
                p >>= 1;
            }
        };

        auto query = [&](int l, int r) {
            Node leftRes;
            Node rightRes;

            bool hasLeft = false;
            bool hasRight = false;

            l += size;
            r += size;

            while (l < r) {
                if (l & 1) {
                    if (!hasLeft) {
                        leftRes = seg[l];
                        hasLeft = true;
                    } else {
                        leftRes = mergeNode(leftRes, seg[l]);
                    }
                    l++;
                }

                if (r & 1) {
                    --r;

                    if (!hasRight) {
                        rightRes = seg[r];
                        hasRight = true;
                    } else {
                        rightRes = mergeNode(seg[r], rightRes);
                    }
                }

                l >>= 1;
                r >>= 1;
            }

            if (!hasLeft)
                return rightRes;

            if (!hasRight)
                return leftRes;

            return mergeNode(leftRes, rightRes);
        };

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            nums[index] = value;
            update(index, value);

            Node res = query(start, n);

            ans.push_back((int)res.pref[x]);
        }

        return ans;
    }
};