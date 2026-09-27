class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        string cur;

        for (char c : s) {
            if (c == '(') {
                st.push(cur);
                cur.clear();
            } else if (c == ')') {
                reverse(cur.begin(), cur.end());
                cur = st.top() + cur;
                st.pop();
            } else {
                cur += c;
            }
        }

        return cur;
    }
};