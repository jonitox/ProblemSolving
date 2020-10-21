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
typedef vector<bool> vb;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;

int n ,ans;
vb fin; // i번 노드의 dfs종료 여부 저장.
vi dis, toStop; // dis: dfs시 방문여부저장(+사이클 크기계산위해 거리저장) // toStop: i에서 출발시 멈추기위한 이동수 저장.
vi nextPos; // 현재칸에서 이동 시 도착하는 다음칸

// 전처리 // nextPos계산
void pre() {
	for (int i = 1; i <= n; ++i) {
		int next=0;
		int tempt = i;
		while (tempt > 0) {
			next += tempt % 10;
			tempt /= 10;
		}
		nextPos[i] = (i+next-1)%n+1;
	}
	
}

// dfs 순회
int dfs(int here, int d) {
	// 이미 방문한 노드면 종료
	if (toStop[here] != -1) return toStop[here];
	dis[here] = d;
	int next = nextPos[here];

	// next가 미방문 노드이면 방문
	if (dis[next] == -1)
		dfs(next,d+1);
	// 방문한 노드지만 함수가 종료하지않은 노드면, cycle을 발견했다. // cycle위에 here, next 존재.
	else if (!fin[next]) {
		// cycle크기 계산
		int cycleSize = dis[here] - dis[next] + 1;
		// cycle위 노드들에서 출발시 멈추기위한 이동수(= 사이클 크기) 저장.
		toStop[here] = cycleSize;
		for (int i = next; i != here; i = nextPos[i]) {
			toStop[i] = cycleSize;
		}
	}
	
	// here가 사이클 위에 있지 않았으면, here에서 출발시 멈추기위한 이동수 = next에서 출발시 멈추기위한 이동수 +1
	if (toStop[here] == -1)
		toStop[here] = toStop[next] + 1;
	fin[here] = true;
	return toStop[here];
}



void solve() {
	cin >> n;
	dis = vi(n+1, -1);
	toStop = vi(n + 1, -1);
	fin = vb(n+1, false);
	toStop.resize(n+1);
	nextPos.resize(n+1);
	pre(); //전처리

	// 방문하지 않은 노드에서 dfs 후, 그 노드에서 멈추기위한 이동수 갱신.
	// i번 노드에서 호출시, i번에서 출발해서 멈출때까지 방문하는 노드들은 모두 toStop이 계산되며, 전부 toStop[i] 이하이다.
	for (int i = 1; i <= n; ++i) {
		if (dis[i] == -1)
			ans=max(dfs(i, 0),ans);
	}
	

	cout << ans << "\n";
}

int main() {
	cin.sync_with_stdio(false);
	cin.tie(0);
	cout.sync_with_stdio(false);
	cout.tie(0);
	solve();
	return 0;
}