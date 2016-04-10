#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <cmath>
#include <map>
#include <sstream>
#include <set>
#include <cassert>
#include <ctime>
#define MOD 1e9 + 7
#define eps 1e-9
#define pb push_back
#define mp make_pair
#define ft first
#define sd second
#define sz(a) a.size()
#define loop(i, n) for(int (i) = 0; (i) < (n) ; ++ (i))
#define pii pair<int,int>
#define pll pair<long long,long long>
#define vii vector<int>
#define vll vector<long long>  
typedef long long ll;
typedef long double ld;

using namespace std;

/*@Sergey_Miller*/

#define SIZE 100010

int a[SIZE];
int t[SIZE];

void modify(int i, int d) {
    while(i < SIZE) {
        t[i] += d;
        i = (i | (i+1));
    }
}

void build() {
    loop(i,SIZE) {
        modify(i,a[i]);
    }
}

int _sum(int i) {
    int res = 0;
    while(i >= 0) {
        res += t[i];
        i = (i & (i+1)) - 1;
    }
    return res;
}

void solve() {
    build();

    int n,m;
    cin >> n >> m;
    vector <int> q(2*m);
    set <pair<pii,pii> > sq;
    vector <pii> pos(n);
    int di;
    loop(i,n) {
        cin >> di;
        pos[i] = mp(di,i + 1);
    }


    int l,r,x,y;
    loop(i,m) {
        cin >> l >> r >> x >> y;
        --l;
        sq.insert(mp(mp(x,2*i),mp(l,r)));
        sq.insert(mp(mp(y+1,2*i + 1),mp(l,r)));
    }

    sort(pos.begin(),pos.end());

    auto qit = sq.begin();
    int eit = 0;

    while(qit != sq.end()) {
        //cout <<qit->ft << " " << qit->sd.ft << " " << qit->sd.sd << endl;
        pair <pii,pii> curq = *qit;
        while(eit != n && pos[eit].first < curq.ft.ft) {
            //cout << eit->first << endl;
            modify(pos[eit].second, 1);
            ++eit;
        }

        q[curq.ft.sd] = _sum(curq.sd.sd) - _sum(curq.sd.ft);
        ++qit;
    }

    loop(i,m) {
        cout << q[2*i + 1] - q[2*i] << "\n"; 
    }
}

int main () {
    ios::sync_with_stdio(false);
    // srand(time(NULL));
    // freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    //double tmr = clock();
    solve();
    //cout << (clock() - tmr)/ CLOCKS_PER_SEC << endl;
 
    return 0;
}
