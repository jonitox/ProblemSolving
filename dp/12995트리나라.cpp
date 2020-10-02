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
#define mod 100
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;

int n,k;
vector<bool> vis;
vvi adj;
vvi child;
ll ans;

// i번 노드의 subtree에서 연결된 j개 정점을 선택할때(i번 노드는 항상포함), 
//i번 노드의 child 중 k번째 이후의 child subtree들만 이용해서 선택하는 경우의 수. 
ll cache[50][50][50]; 

ll dp(int here, int num, int idx) {
	ll &ret = cache[here][num][idx];
	if (ret != -1) return ret;

	
	//기저사례:
	// 리프노드인 경우, 선택해야하는 점이 1개 이하여야한다. 
	//** 이 조건문은 없어도 된다. 리프노드인 경우 num<=1이면 1개 세어지고, 그 외의 경우는 밑에서 ret=0으로 계산되어 반환된다.
	if (child[here].size() == 0)
		return (num <= 1) ? 1 : 0;
	// 이용할수 있는 child idx가 here의 child범위 밖인 경우. here만 선택할수 있다.
	if (idx == child[here].size())
		return (num<=1) ? 1: 0;
	// 앞으로 선택해야 할 점이 1개 이하인 경우. here 선택하는 방법만 존재.
	if (num <= 1)
		return 1;
	
	ret = 0;


	// here의 subtree에서 idx번 이후 child만 사용하여 num개 노드를 선택하는 경우의 수는,
	// idx번 child의 subtree에서 j개 선택하고, 
    // here의 subtree에서는 idx+1번 이후 child만 이용해서 num-j를 선택하는 경우의 수를 곱한 값을, 
    // 각 j들에 계산후 더한다.
	for(int j=0; j<num; ++j){
		ret += dp(child[here][idx],j,0)*dp(here, num-j, idx+1);
		ret %= 1000000007;
	}

	
	return ret;
}

// 트리구조 파악. dfs순회.
void dfs(int here) {
	vis[here] = true;
	for (int there : adj[here]) {
		if (!vis[there]) {
			dfs(there);
			child[here].push_back(there); // 각 노드의 child저장.
		}
	}
	return;
}

void solve() {
	cin >> n>> k;
	
	adj.resize(n);
	child.resize(n);
	memset(cache, -1, sizeof(cache));
	vis = vector<bool>(n, false);

	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		adj[a - 1].push_back(b - 1);
		adj[b - 1].push_back(a - 1);
	}
	dfs(0);
	
	// 답 계산.
	for (int i = 0; i < n; ++i) {
        // 각 노드들이 최상위노드인 subtree에서 k개를 선택하는 경우의 수를 모두 더한다. 
        // 모든 k개 도시선택방법은 최상위노드가 존재하므로, 원하는 경우의 수 전부 세어짐.
		ans += dp(i, k, 0);
		ans %= 1000000007;
	}
	cout<<ans<< "\n";
}

int main() {
	cin.sync_with_stdio(false);
	cin.tie(0);
	cout.sync_with_stdio(false);
	cout.tie(0);
	solve();
	return 0;
}