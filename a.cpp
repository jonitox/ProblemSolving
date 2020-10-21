	#include <iostream>
	#include <string>
	#include <cstring>
	#include <set>
	#include <vector>
	#include<map> 
	#include <stack>
	#include <queue>
	#include <algorithm>
	#include <typeinfo>
	#include <iomanip>
	#include <cmath>
//////  #include <bits/stdc++.h>


	using namespace std;
	typedef long long ll;
	typedef vector<int> vi;
	typedef vector<bool> vb;
	typedef vector<long long> vll;
	typedef vector<vector<int>> vvi;
	typedef pair<int, int> pii;
	typedef pair<ll, ll> pll;
	typedef vector<pii> vpii;
	typedef vector<pll> vpll;
		
	#define INF 1000000000
	#define mod 1000000007
	#define MAXN 100001

	ll x,y;
	ll c[6], cc[6];
	void solve() {
		cin>>x>>y;
		for(int i=0; i<6; ++i)
			cin>>c[i];
		
		ll ret=0;

		for(int i=0; i<6; ++i){
			cc[i] = min(c[i], c[(i+5)%6]+c[(i+1)%6]);
		}

		if((x>=0) == (y>=0)){
			ll k = x>=0 ? cc[0]: cc[3];
			ret += k * min(abs(x),abs(y));
			if(abs(x)>abs(y)){
				ll dif = abs(x)-abs(y);
				ret += x>=0? cc[5]*dif : cc[2]*dif;
			}
			else{
				ll dif = abs(y)-abs(x);
				ret += y>=0? cc[1]*dif: cc[4]*dif;
			}
		}
		else{
			ret += abs(x)* (x>=0? cc[5]:cc[2]);
			ret += abs(y)* (y>=0? cc[1]:cc[4]);
		}
		cout<<ret<<"\n";	
	}

	int main() {
		cin.sync_with_stdio(false);
		cin.tie(0);
		cout.sync_with_stdio(false);
		cout.tie(0);

		int t;
		cin>>t;
		while(t--)
		solve();

		return 0;
	}