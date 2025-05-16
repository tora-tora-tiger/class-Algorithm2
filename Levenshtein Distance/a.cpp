#include<iostream>
#include<vector>
#include<string>

using namespace std;
template<typename T> using vv = vector<vector<T>>;

#define rep(i, n) for(int i = 0 ; i < (n); i++)
template<typename T> T min(T a, T b, T c) { return (a < b ? a : b) < c ? (a < b ? a : b) : c; }

int main() {
    string s, t; cin >> s >> t;
    int n = s.size(), m = t.size();
    vv<int> dp(n+1, vector<int>(m+1, -1));

    dp[0][0] = 0;
    rep(i, n+1) {
        rep(j, m+1) {
            if (i == 0 && j == 0) continue;
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else {
                dp[i][j] = min<int>(
                    dp[i-1][j] + 1,
                    dp[i][j-1] + 1,
                    dp[i-1][j-1] + (s[i-1] != t[j-1])
                );
            }
        }
    }
    // output
    cout << "    ";
    rep(j, m) cout << t[j] << " ";
    puts("");
    rep(i, n+1) {
        auto v = dp[i];

        if(i) cout << s[i-1] << " ";
        else cout << "  ";

        for(auto x : v) {
            cout << x << " ";
        }
        cout << endl;
    }
}