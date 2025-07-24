// https://atcoder.jp/contests/past17-open/tasks/past17_l

#include <iostream>
#include <vector>
using namespace std;

template<typename T> using vv = vector<vector<T>>;
template<typename T> using vvv = vector<vector<vector<T>>>;

#define rep(i, n) for (int i = 0; i < (n); ++i)

int main() {
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n, 0));
    vector<vector<int>> b(n, vector<int>(n, 0));
    rep(i, n) {
        for(int j = i + 1; j < n; j++) {
            cin >> a[i][j];
        }
    }
    rep(i, n) {
        for(int j = i + 1; j < n; j++) {
            cin >> b[i][j];
        }
    }


    vvv<int> dp(n+1, vv<int>(n, vector<int>(n)));

    rep(i, n) {
        for(int j = i+1; j < n; j++) {
            dp[i][j][0] = dp[j][i][0] = a[i][j];
            dp[i][j][1] = dp[j][i][1] = b[i][j];
        }
    }

    for(int k = 0 ; k < n; k++) {
        rep(i, n) {
            rep(j, n) {
                dp[i][j][0] = min(dp[i][j][0], dp[i][k][0] + dp[k][j][0]);
                dp[i][j][1] = min(dp[i][j][1], min(
                    dp[i][k][1] + dp[k][j][0],
                    dp[i][k][0] + dp[k][j][1]
                ));
            }
        }
    }

    rep(i, n) {
        for(int j = i+1 ; j < n ; j++)
            cout << min(dp[i][j][0], dp[i][j][1]) << " \n"[j == n - 1];
    }
}