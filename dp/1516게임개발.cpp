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

	#define INF 1000000000
	#define mod 1000000007

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
	#define MAXN 500000
	
    // 위상정렬 + dp
    
	int n;
	int need[501]; // i번 건물을 짓는데 걸리는 시간.
	vi g[501];
	bool vis[501];
	vi topo; // 위상정렬 배열.
	int dp[501]; // i번 건물의 건설을 완료할수 있는 최소시간.

	// 위상정렬을 위한 dfs
	void dfs(int h){
		vis[h] =true;
		for(auto t: g[h]){
			if(!vis[t])
				dfs(t);
		}
		topo.push_back(h); // 위상정렬
	}

	void solve() {
		// 입력
		cin>>n;
		for(int i=1; i<=n; ++i){
			cin>> need[i];
			while(true){
				int a;
				cin>>a;
				if(a==-1)
					break;
				g[a].push_back(i); // 그래프 생성. 먼저 건설되는 노드 -> 나중 건설되는 노드
			}
		}
		// dfs // 위상정렬
		for(int i=1; i<=n; ++i){
			if(!vis[i])
				dfs(i);
		}
		reverse(topo.begin(),topo.end()); // dfs역순으로 위상정렬
		// 위상정렬된 노드 앞쪽부터 해당 건물 뒷건물이 건설되는 시간을 갱신한다.
		for(int i=0; i<n; ++i){
			int t = topo[i];
			// 이 건물을 짓는데는 전제되는 다른 건물도 지어져야하지만 필요건물이 없더라도 이건물을 짓는 시간은 필요하다.
			dp[t] =max(dp[t], need[t]); 
			// 이 건물을 필요로하는 건물들의 건설완료시간 갱신.
			for(auto h: g[t]){
				dp[h] = max(dp[h], dp[t]+need[h]); 
			}
		}

		for(int i=1; i<=n; ++i)
			cout<<dp[i]<<"\n";
	}

	int main() {
		cin.sync_with_stdio(false);
		cin.tie(0);
		cout.sync_with_stdio(false);
		cout.tie(0);
		solve();

		return 0;
	}