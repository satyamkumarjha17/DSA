class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        int i = 0;

        function<set<string>()> parseExpr = [&]() {
            set<string> res;
            set<string> cur = {""};

            while (i < expression.size() && expression[i] != '}') {
                if (expression[i] == ',') {
                    res.insert(cur.begin(), cur.end());
                    cur = {""};
                    i++;
                } else {
                    set<string> part;

                    if (expression[i] == '{') {
                        i++;
                        part = parseExpr();
                        i++;
                    } else {
                        part.insert(string(1, expression[i]));
                        i++;
                    }

                    set<string> next;
                    for (auto &a : cur)
                        for (auto &b : part)
                            next.insert(a + b);

                    cur = next;
                }
            }

            res.insert(cur.begin(), cur.end());
            return res;
        };

        set<string> ans = parseExpr();
        return vector<string>(ans.begin(), ans.end());
    }
};