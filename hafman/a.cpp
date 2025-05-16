#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<map>
#include<stack>

using namespace std;


struct Node {
    int frequency;
    char value;
    Node *left, *right;
    Node(int v, int c) : frequency(v), value(c), left(nullptr), right(nullptr) {}
};

struct CompareNode {
    bool operator()(const Node* a, const Node* b) const {
        return a->frequency > b->frequency;
    }
};

int main() {
    int n;
    char c;
    priority_queue<Node*, vector<Node*>, CompareNode> pq;
    while(cin >> c >> n) {
        pq.push(new Node(n, c));
    }
    while(pq.size() > 1) {
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();
        Node* c = new Node(a->frequency + b->frequency, '\0');
        c->left = a;
        c->right = b;
        pq.push(c);
    }
    
    map<char, string> code;
    Node* root = pq.top(); pq.pop();
    stack<pair<Node*, string>> s; s.push({root, ""});

    while(!s.empty()) {
        auto [node, str] = s.top(); s.pop();
        if(node->left == nullptr && node->right == nullptr) {
            code[node->value] = str;
        }
        if(node->left) {
            s.push({node->left, str + "0"});
        }
        if(node->right) {
            s.push({node->right, str + "1"});
        }
    }

    for(auto [c, str] : code) {
        cout << c << ": " << str << endl;
    }
    return 0;
}