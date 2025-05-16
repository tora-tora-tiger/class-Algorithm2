#include<iostream>
#include<vector>
#include<string>

using namespace std;
#define rep(i, n) for(int i = 0 ; i < (n); i++)

int main() {
    int n; cin >> n;
    vector<int> a(n), dp(n, 1001001001);
    rep(i, n) {
        cin >> a[i];
    }

    for(int i = 0; i < n; i++) {
        auto it = lower_bound(dp.begin(), dp.end(), a[i]);
        if(it == dp.end()) {
            dp.push_back(a[i]);
        } else {
            *it = a[i];
        }
    }

    rep(i, dp.size()) {
        cout << i << ": " << dp[i] << endl;
    }
}