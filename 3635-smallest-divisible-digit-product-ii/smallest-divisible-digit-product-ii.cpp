#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string smallestNumber(string num, long long t) {
        long long c2 = 0, c3 = 0, c5 = 0, c7 = 0;
        while (t % 2 == 0) { c2++; t /= 2; }
        while (t % 3 == 0) { c3++; t /= 3; }
        while (t % 5 == 0) { c5++; t /= 5; }
        while (t % 7 == 0) { c7++; t /= 7; }

        if (t > 1) return "-1";

        auto get_min_digits = [](long long req2, long long req3, long long req5, long long req7) {
            string res = "";
            res.append(req7, '7');
            res.append(req5, '5');

            long long k8 = req2 / 3, r2 = req2 % 3;
            long long k9 = req3 / 2, r3 = req3 % 2;

            res.append(k8, '8');
            res.append(k9, '9');

            if (r2 == 0 && r3 == 1) res.push_back('3');
            else if (r2 == 1 && r3 == 0) res.push_back('2');
            else if (r2 == 1 && r3 == 1) res.push_back('6');
            else if (r2 == 2 && r3 == 0) res.push_back('4');
            else if (r2 == 2 && r3 == 1) { res.push_back('2'); res.push_back('6'); }

            sort(res.begin(), res.end());
            return res;
        };

        const vector<vector<int>> digit_factors = {
            {0,0,0,0}, {0,0,0,0}, {1,0,0,0}, {0,1,0,0}, {2,0,0,0},
            {0,0,1,0}, {1,1,0,0}, {0,0,0,1}, {3,0,0,0}, {0,2,0,0}
        };

        int N = num.length();
        int first_zero = num.find('0');

        if (first_zero == string::npos) {
            long long n2 = 0, n3 = 0, n5 = 0, n7 = 0;
            for (char ch : num) {
                int d = ch - '0';
                n2 += digit_factors[d][0]; n3 += digit_factors[d][1];
                n5 += digit_factors[d][2]; n7 += digit_factors[d][3];
            }
            if (n2 >= c2 && n3 >= c3 && n5 >= c5 && n7 >= c7) return num;
        }

        vector<long long> pref2(N + 1, 0), pref3(N + 1, 0), pref5(N + 1, 0), pref7(N + 1, 0);
        for (int idx = 0; idx < N; ++idx) {
            int d = num[idx] - '0';
            pref2[idx + 1] = pref2[idx] + digit_factors[d][0];
            pref3[idx + 1] = pref3[idx] + digit_factors[d][1];
            pref5[idx + 1] = pref5[idx] + digit_factors[d][2];
            pref7[idx + 1] = pref7[idx] + digit_factors[d][3];
        }

        int max_prefix_idx = (first_zero == string::npos) ? N - 1 : first_zero;
        for (int i = max_prefix_idx; i >= 0; --i) {
            int start_digit = (num[i] - '0') + 1;
            for (int d = start_digit; d <= 9; ++d) {
                long long tot2 = pref2[i] + digit_factors[d][0];
                long long tot3 = pref3[i] + digit_factors[d][1];
                long long tot5 = pref5[i] + digit_factors[d][2];
                long long tot7 = pref7[i] + digit_factors[d][3];

                long long rem2 = max(0LL, c2 - tot2);
                long long rem3 = max(0LL, c3 - tot3);
                long long rem5 = max(0LL, c5 - tot5);
                long long rem7 = max(0LL, c7 - tot7);

                string req_digits = get_min_digits(rem2, rem3, rem5, rem7);
                int rem_len = N - 1 - i;

                if ((int)req_digits.length() <= rem_len) {
                    string ones(rem_len - req_digits.length(), '1');
                    return num.substr(0, i) + to_string(d) + ones + req_digits;
                }
            }
        }

        string req_t = get_min_digits(c2, c3, c5, c7);
        int L = max(N + 1, (int)req_t.length());
        string ones(L - req_t.length(), '1');
        return ones + req_t;
    }
};