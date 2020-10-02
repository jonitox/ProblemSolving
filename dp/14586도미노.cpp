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
	typedef vector<pii> vpii;

	int n;
	vector<pair<ll,ll>> domino;
	int goRight[300]; // i번 도미노를 오른쪽으로 넘어뜨렸을때, 닿을수 있는 최대 index의 도미노
	int goLeft[300]; // 왼쪽으로 넘어렸을때 닿을수있는 최소 index의 도미노
	int dp[300];

	void solve() {
		cin >> n;

		for (int i = 0; i < n; ++i) {
			int x, h;
			cin >> x >> h;
			domino.push_back({ x,h });
		}
		sort(domino.begin(), domino.end()); // 위치순으로 정렬.

		// goLeft계산.
		for (int i = 0; i < n; ++i) {
			ll x = domino[i].first;
			ll h = domino[i].second;
			goLeft[i] = i; // 자기자신은 반드시 갈수있다.
			for (int j = i - 1; j>=0; --j) { // i번 앞쪽의 도미노 중
				if (domino[j].first < x - h) break; // i번을 왼쪽으로 넘어뜨렸을때, 닿을수없다면 종료.
				goLeft[i] = min(goLeft[i], goLeft[j]); // 닿을수 있다면 연쇄적으로 넘어뜨릴수있다.
			}
		}
		// goRight계산.
		for (int i = n - 1; i >= 0; --i) {
			ll x = domino[i].first;
			ll h = domino[i].second;
			goRight[i] = i;
			for (int j = i + 1; j < n; ++j) {
				if (domino[j].first > x + h) break;
				goRight[i] = max(goRight[i], goRight[j]);
			}
		}
		//반복적 dp
		// dp[i] : 0~i번을 전부 넘어뜨리기위한 최소 횟수.
		for (int i = 0; i < n; ++i) {
			// i번을 왼쪽으로 넘어뜨리는 경우. i번에 의해 닿을수있는 모든 도미노(goLeft[i]~i)는 넘어지고, 그 앞쪽 도미노를 최소로 무너뜨려야한다.
			dp[i] = goLeft[i] > 0 ? dp[goLeft[i]-1] + 1 : 1;  
			// i번이 오른쪽으로 넘어가는 경우.
			for (int j = i - 1; j >= 0; --j) {
				if (goRight[j] >= i) // 앞쪽의 도미노중 오른쪽으로 넘겨 i번까지 닿을수있는 도미노(j)를 오른쪽으로 넘겨본다. 그 앞쪽 도미노(0~j-1)는 최소로 무너뜨린다.
					dp[i] = min(dp[i], dp[j - 1] + 1);
			}
		}
		cout << dp[n - 1] << "\n";
	}

	int main() {
		cin.sync_with_stdio(false);
		cin.tie(0);
		cout.sync_with_stdio(false);
		cout.tie(0);


		solve();

		return 0;
	}