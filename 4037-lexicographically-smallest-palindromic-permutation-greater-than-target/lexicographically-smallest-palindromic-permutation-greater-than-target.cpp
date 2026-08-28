class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        int odd = 0;
        char mid = '\0';

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }

        if (odd > 1) {
            return "";
        }

        int n = s.size();
        int m = n / 2;

        vector<int> cnt(26, 0);

        for (int i = 0; i < 26; i++) {
            cnt[i] = freq[i] / 2;
        }

        auto build = [&](const string& half) {
            string ans = half;

            if (n % 2) {
                ans += mid;
            }

            for (int i = m - 1; i >= 0; i--) {
                ans += half[i];
            }

            return ans;
        };

        string prefix = target.substr(0, m);
        string half;
        bool found = false;

        for (int i = 0; i < m; i++) {
            int x = prefix[i] - 'a';

            if (cnt[x] > 0) {
                half += prefix[i];
                cnt[x]--;
            } else {
                int larger = -1;

                for (int c = x + 1; c < 26; c++) {
                    if (cnt[c] > 0) {
                        larger = c;
                        break;
                    }
                }

                if (larger != -1) {
                    half += char('a' + larger);
                    cnt[larger]--;

                    for (int c = 0; c < 26; c++) {
                        half.append(cnt[c], char('a' + c));
                    }

                    found = true;
                    break;
                }

                while (!half.empty()) {
                    int last = half.back() - 'a';
                    half.pop_back();
                    cnt[last]++;

                    int largerChar = -1;

                    for (int c = last + 1; c < 26; c++) {
                        if (cnt[c] > 0) {
                            largerChar = c;
                            break;
                        }
                    }

                    if (largerChar != -1) {
                        half += char('a' + largerChar);
                        cnt[largerChar]--;

                        for (int c = 0; c < 26; c++) {
                            half.append(cnt[c], char('a' + c));
                        }

                        found = true;
                        break;
                    }
                }

                break;
            }
        }

        if (!found && (int)half.size() != m) {
            return "";
        }

        string ans = build(half);

        if (ans > target) {
            return ans;
        }

        if (next_permutation(half.begin(), half.end())) {
            return build(half);
        }

        return "";
    }
};