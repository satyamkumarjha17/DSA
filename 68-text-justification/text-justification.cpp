class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int n = words.size();
        int i = 0;

        while (i < n) {
            int j = i;
            int letters = 0;

            while (j < n &&
                   letters + words[j].size() + (j - i) <= maxWidth) {
                letters += words[j].size();
                j++;
            }

            int gaps = j - i - 1;
            int spaces = maxWidth - letters;
            string line;

            if (j == n || gaps == 0) {
                for (int k = i; k < j; k++) {
                    if (k > i)
                        line += " ";

                    line += words[k];
                }

                line += string(maxWidth - line.size(), ' ');
            }
            else {
                int spacesPerGap = spaces / gaps;
                int extraSpaces = spaces % gaps;

                for (int k = i; k < j; k++) {
                    line += words[k];

                    if (k < j - 1) {
                        int currentSpaces = spacesPerGap;

                        if (k - i < extraSpaces)
                            currentSpaces++;

                        line += string(currentSpaces, ' ');
                    }
                }
            }

            result.push_back(line);
            i = j;
        }

        return result;
    }
};