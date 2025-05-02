#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        int n = s.size();
        vector<string> ans;
        vector<string> t;

        // Helper function for backtracking
        function<void(int)> dfs = [&](int i) {
            if (i >= n && t.size() == 4) {
                ans.push_back(t[0] + "." + t[1] + "." + t[2] + "." + t[3]);
                return;
            }
            if (i >= n || t.size() >= 4) {
                return;
            }
            int x = 0;
            for (int j = i; j < min(n, i + 3); ++j) {
                x = x * 10 + s[j] - '0';
                if (x > 255 || (j > i && s[i] == '0')) {
                    break;
                }
                t.push_back(s.substr(i, j - i + 1));
                dfs(j + 1);
                t.pop_back();
            }
        };

        dfs(0);
        return ans;
    }
};

// Helper function to print the result
void printResult(const vector<string>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "\"" << result[i] << "\"";
        if (i + 1 < result.size()) {
            cout << ",";
        }
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // Example 1
    string s1 = "25525511135";
    cout << "Input: s = \"" << s1 << "\"" << endl;
    vector<string> result1 = solution.restoreIpAddresses(s1);
    cout << "Output: ";
    printResult(result1);

    // Example 2
    string s2 = "0000";
    cout << "Input: s = \"" << s2 << "\"" << endl;
    vector<string> result2 = solution.restoreIpAddresses(s2);
    cout << "Output: ";
    printResult(result2);

    // Example 3
    string s3 = "101023";
    cout << "Input: s = \"" << s3 << "\"" << endl;
    vector<string> result3 = solution.restoreIpAddresses(s3);
    cout << "Output: ";
    printResult(result3);

    return 0;
}
