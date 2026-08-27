class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> freq(26);

        for (char c : s) {
            freq[c - 'a']++;
        }

        vector<vector<int>> states(n + 1, vector<int>(26));
        states[0] = freq;

        int matched = 0;

        while (matched < n) {
            int idx = target[matched] - 'a';

            if (freq[idx] == 0) {
                break;
            }

            freq[idx]--;
            matched++;
            states[matched] = freq;
        }

        for (int i = matched; i >= 0; i--) {
            vector<int> available = states[i];

            if (i < n) {
                int t = target[i] - 'a';

                for (int c = t + 1; c < 26; c++) {
                    if (available[c] > 0) {
                        string result = target.substr(0, i);
                        result += char('a' + c);
                        available[c]--;

                        for (int j = 0; j < 26; j++) {
                            result += string(available[j], char('a' + j));
                        }

                        return result;
                    }
                }
            }
        }

        return "";
    }
};