class Solution {
private:
    int lengthOfLastWordHelper(string s) {
        int n = s.size();
        int len = 0;

        int i = n - 1;
        while (i >= 0 && s[i] == ' ')
            i--;

        while (i >= 0 && s[i] != ' ') {
            len++;
            i--;
        }

        return len;
    }
public:
    int lengthOfLastWord (string s) {
        return lengthOfLastWordHelper(s);
    }
};