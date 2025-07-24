#include <iostream>
#include <vector>
#include <set>
using namespace std;

using P = pair<char, char>;
template<typename T> using vv = vector<vector<T>>;
template<typename T> using vvv = vector<vector<vector<T>>>;


#define rep(i, n) for (int i = 0; i < (n); i++)

/*
 * CYK Algorithm
 * 入力
 * n: 非終端文字数
 * m: 終端文字数
 * p: 文法の規則数
 * s: 開始記号
 * ------------
 * n
 * a_1 a_2 ... a_n
 * m
 * b_1 b_2 ... b_m
 * p
 * r_1a r_1b r_2a r_2b ... r_pa r_pb
 * s
 * ------------
 * パース大変なのでハードコード
 */

int main() {
    string w = "abaabb";
    char s = 'S';
    vector<char> sigma = {'a', 'b'};
    int n = 6; // 非終端文字数
    vector<pair<char, P>> rule_cont = {
        {'S', {'Z', 'Y'}},
        {'X', {'A', 'B'}},
        {'Z', {'X', 'S'}},
        {'A', {'S', 'S'}}
    };
    vector<P> rule_finish = {
        {'S', 'a'},
        {'S', 'b'},
        {'X', 'a'},
        {'Y', 'b'},
        {'A', 'a'},
        {'B', 'b'}
    };

    vv<set<char>> dp(n + 1, vector<set<char>>(n+1));
    rep(j, n) {
        for (const auto& f : rule_finish) {
            if (f.second == w[j]) {
                dp[1][j].insert(f.first);
            }
        }
    }

    // 何文字か
    for(int i = 2; i <= n; i++) {
        // 何文字目からか
        for(int j = 0; j <= n-i; j++) {
            // cut
            for (int k = 1; k < i; k++) {
                auto left = dp[k][j];
                auto right = dp[i-k][j+k];
                for(auto & r : rule_cont) {
                    auto rule_left = r.second.first;
                    auto rule_right = r.second.second;
                    if (left.count(rule_left) && right.count(rule_right)) {
                        dp[i][j].insert(r.first);
                    }
                }
            }
        }
    }

    // 出力
    for(int i = 1; i <= n; i++) {
        rep(j, n-i+1) {
            cout << "dp[" << i << "][" << j << "]: ";
            for (const auto& c : dp[i][j]) {
                cout << c << " ";
            }
            cout << endl;
        }
    }
}