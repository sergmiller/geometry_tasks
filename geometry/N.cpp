nclude <iostream>
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
#define MAX_LONG (unsigned long long)1e19
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
typedef unsigned long long ll;
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
    int num_bnd;
    point bnd;
    dtree(vector <pair <point, int> >& d, int _dim = 0) {
        low = point(MOD,MOD);
        up = point(-MOD,-MOD);
        dim = _dim;
        sz = sz(d);
        sort(d.begin(),d.end(), (_dim ? cmp_sd : cmp_ft));

        vector <pair <point,int> > l(sz/2);
        vector <pair <point,int> > r((sz + 1)/2);

        loop(i,sz/2) {
            l[i] = d[i];
            r[i] = d[sz/2 +i];
        }

        r[sz(r) - 1] = d[sz - 1];

        loop(i,sz) {
            //cout << d[i].second << " ";
            low.x = min(low.x, d[i].ft.x);
            low.y = min(low.y, d[i].ft.y);
            up.x = max(up.x, d[i].ft.x);
            up.y = max(up.y, d[i].ft.y);
        }
        //cout << endl;

        bnd = d[sz/2].first;
        num_bnd = d[sz/2].second;

        if(sz == 1) {
            L = R = NULL;
            return;
        }

        L = new dtree(l, dim ^ 1);
        R = new dtree(r, dim ^ 1);
    }

    void print() {
        cout << dim << " " << bnd.x << " " << bnd.y << " " << num_bnd<< endl;
        if(L && L->sz > 1) {
            L->print();
        }

        if(R && R->sz > 1) {
            R->print();
        }
    }

    bool is_out(point p, ll best2) {
        if(best2 == MAX_LONG) {
            return false;
        }
        if(p.x >= low.x && p.x <= up.x && p.y >= low.y && p.y <= up.y) {
            return false;
        }

        ll minn = MAX_LONG;

        if(p.x >= low.x && p.x <= up.x) {
            minn = (ll)min(abs(p.y - low.y), abs(p.y - up.y));
            return minn*minn > best2;
        }

        if(p.y >= low.y && p.y <= up.y) {
            minn = (ll)min(abs(p.x - low.x), abs(p.x - up.x));
            return minn*minn > best2;
        }

        minn = min(dist2(low,p), dist2(up,p));
        point t1(low.x, up.y);
        point t2(up.x ,low.y);
        ll minn2 = min(dist2(t1, p), dist2(t2, p));
        minn = min(minn, minn2);
        return minn > best2;
    }

    ll dist2(point& a, point& b) {
        ll x = abs(a.x - b.x);
        ll y = abs(a.y - b.y);
        return x*x + y*y;
    }

    void get_neig_numb(point p, ll& best2, int& num_best) {
        if(is_out(p, best2)) {
            return;
        }
        ll dist2_bnd = dist2(bnd, p);
        if((num_best == -1 || dist2_bnd < best2 || (dist2_bnd == best2 && num_bnd < num_best)) && (p.x != bnd.x || p.y != bnd.y)) {
            
            best2 = dist2_bnd;
            //cout << p.x << " " << p.y << " " << bnd.x << " " << bnd.y << " " << num_bnd << " " << num_best<< " " << rn << endl;
            num_best = num_bnd;
        }

        if(R) {
            R->get_neig_numb(p, best2, num_best);
            L->get_neig_numb(p, best2, num_best);
        }
    }
};


void solve() {
    int n;
    cin >> n;
    vector <pair <point,int> > d(n);
    vector <pair <point,int> > dc(n);
    // set <pii> st;
    loop(i,n) {
        cin >> d[i].ft.x >> d[i].ft.y;
        d[i].sd = i;
        dc[i] = d[i];
        // assert(st.find(mp(d[i].ft.x, d[i].ft.y)) == st.end());
        // st.insert(mp(d[i].ft.x, d[i].ft.y));
    }

    dtree V(dc);

    //V.print();

    vector <vector <int> > ans(n);

    loop(i,n) {
        ll best2 = MAX_LONG;
        int best_num = -1;
        V.get_neig_numb(d[i].ft, best2, best_num);
        //cout << best_num << " " << i << endl;
        ans[best_num].pb(i);
    }
    //V.print();
    loop(i,n) {
        cout << i + 1 << ": ";
        loop(j,sz(ans[i])) {
            cout << ans[i][j] + 1 << " ";
        }
        cout << "\n";
    }

}

int main () {
    ios::sync_with_stdio(false);
    // srand(time(NULL));
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    freopen("k.in", "r", stdin);
    freopen("k.out", "w", stdout);
    //double tmr = clock();
    solve();
    // cout << (int)(((ll)MOD + (ll)MOD)/2);
    //cout << (clock() - tmr)/ CLOCKS_PER_SEC << endl;
}
