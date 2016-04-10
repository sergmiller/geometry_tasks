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
#define MOD (int)1073741824
#define eps 1e-12
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

struct point{
    int x,y;
    point() {
        x = y = 0;
    }
    point(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

bool cmp_ft(const pair <point, int>& a, const pair <point, int>& b) {
    return a.ft.x < b.ft.x || (a.ft.x == b.ft.x && a.ft.y < b.ft.y);
}

bool cmp_sd(const pair <point, int>& a, const pair <point, int>& b) {
    return a.ft.y < b.ft.y || (a.ft.y == b.ft.y && a.ft.x < b.ft.x);
}

struct dtree {
    dtree* L;
    dtree* R;
    int sz;
    int dim;
    point low;
    point up;
    int minn;
    int promise;
    point bnd;
    dtree(vector <pair <point, int> >& d, int _dim = 0) {
        promise = -1;
        low = point(MOD,MOD);
        up = point(-MOD,-MOD);
        dim = _dim;
        sz = sz(d);
        sort(d.begin(),d.end(), (_dim ? cmp_sd : cmp_ft));

        vector <pair <point,int> > l(sz/2);
        vector <pair <point,int> > r((sz + 1)/2);
        minn = MOD;
        loop(i,sz/2) {
            l[i] = d[i];
            r[i] = d[sz/2 +i];
        }

        r[sz(r) - 1] = d[sz - 1];

        loop(i,sz) {
            minn = min(minn, d[i].second);
            low.x = min(low.x, d[i].ft.x);
            low.y = min(low.y, d[i].ft.y);
            up.x = max(up.x, d[i].ft.x);
            up.y = max(up.y, d[i].ft.y);
        }

        bnd = d[sz/2].first;
        if(sz == 1) {
            L = R = NULL;
            return;
        }

        L = new dtree(l, dim ^ 1);
        R = new dtree(r, dim ^ 1);
    }

    void print() {
        cout << dim << " " << bnd.x << " " << bnd.y << endl;
        if(L && L->sz > 1) {
            L->print();
        }

        if(R && R->sz > 1) {
            R->print();
        }
    }

    void push() {
        if(promise == -1) {
            return;
        }

        if(L) {
            L->promise = promise;
        }

        if(R){
            R->promise = promise;
        }


        minn = promise;
        promise = -1;
    }

    void set(point lb, point rb, int val) {
        push();
        if(lb.x > up.x || lb.y > up.y || rb.x < low.x || rb.y < low.y) {
            return;
        }

        if(lb.x <= low.x && lb.y <= low.y && rb.x >= up.x && rb.y >= up.y) {
            promise = val;
            return;
        }

        minn = MOD;

        if(L) {
            L->set(lb,rb,val);
            L->push();
            minn = min(L->minn, minn);
        }

        if(R) {
            R->set(lb,rb,val);
            R->push();
            minn = min(R->minn, minn);
        }
    }

    int get_min(point lb, point rb) {
        push();
        if(lb.x > up.x || lb.y > up.y || rb.x < low.x || rb.y < low.y) {
            return MOD;
        }

        if(lb.x <= low.x && lb.y <= low.y && rb.x >= up.x && rb.y >= up.y) {
            return minn;
        }

        int _minn = MOD;

        if(L) {
            _minn = min(_minn, L->get_min(lb,rb));
        }

        if(R) {
            _minn = min(_minn, R->get_min(lb,rb));
        }

        return _minn;
    }
};

void solve() {
    int n;
    cin >> n;
    vector <pair <point,int> > d(n);
    // set <pii> st;
    loop(i,n) {
        cin >> d[i].ft.x >> d[i].ft.y >> d[i].second;
        // assert(st.find(mp(d[i].ft.x, d[i].ft.y)) == st.end());
        // st.insert(mp(d[i].ft.x, d[i].ft.y));
    }

    dtree V(d);
    //V.print();
    int m;
    vector <int> ans;
    cin >> m;
    char ch;
    point lb,rb;
    int val;
    loop(i,m) {
        cin >> ch;
        if(ch == '=') {
            cin >> lb.x >> lb.y >> rb.x >> rb.y >> val;
            V.set(lb,rb,val);
        } else {
            cin >> lb.x >> lb.y >> rb.x >> rb.y;
            ans.pb(V.get_min(lb,rb));
        }
    }

    loop(i,sz(ans)) {
        if(ans[i] == MOD) {
            cout << "NO\n";
        } else {
            cout << ans[i] << "\n";
        }
    }
}

int main () {
    ios::sync_with_stdio(false);
    // srand(time(NULL));
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    freopen("rectmin.in", "r", stdin);
    freopen("rectmin.out", "w", stdout);
    //double tmr = clock();
    solve();
    // cout << (int)(((ll)MOD + (ll)MOD)/2);
    //cout << (clock() - tmr)/ CLOCKS_PER_SEC << endl;
}
