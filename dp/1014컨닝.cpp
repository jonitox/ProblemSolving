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

	int n,m;
	char room[10][10];
	int dp[11][1<<10]; // i번째 줄의 의자 배치가 j(bitMask)이면서 1~i번줄에 놓을 수 있는 최대 의자수.

	// k번째 행의 자리배치가 line(bitMask)가 가능한지 확인.
	bool chk(int line, int k){
		for(int i=0; i<m; ++i){
			if(line&(1<<i)&&room[k][i] =='x') // 의자를 못놓는곳에 있는 경우
				return false;
			if(i<m-1 && line&(1<<i) && line&(1<<(i+1))) // 두 의자가 붙어있는 경우(컨닝)
				return false;
			}
		return true;
	}
	// 윗 행의 배치가 up, 아랫행의 배치가 down일때, 컨닝이 일어나지않는지 확인
	bool can(int up, int down){
		for(int i=0; i<m; ++i){
			if((up&1<<i)){
				if(i<m-1 && down&(1<<(i+1)))
					return false;
				else if(i>0 && down&(1<<(i-1)))
					return false;
			}
		}
		return true;
	}
	// 한 줄(bitMask)의 의자수 계산
	int bitCnt(int s){
		int ret=0;
		for(int i=0; i<m; ++i)
			if(s& 1<<i)
				ret++;
		return ret;		
	}
	void solve() {
		cin>>n>>m;
		int ans=0;
		// 반복적 dp
		for(int i=0; i<n; ++i){
			//입력
			for(int j=0; j<m; ++j)
				cin>>room[i][j];
			// i번째 줄의 의자 배치 모든 부분집합 순회.
			for(int s =0 ; s< 1<<m; ++s){
				dp[i][s] = -INF; // 초기화
				if(!chk(s,i)) continue; // i번쨰 줄에서 s의 배치가 불가능한경우
				// 첫번쨰 줄 계산시 현재 줄의 배치상태(s)가 가능하면 그때의 의자수가 dp값.
				if(i==0){
					dp[i][s] = bitCnt(s);
					ans = max(ans,dp[i][s]); //** n=1인 경우를 위해 ans갱신 필요
					continue;
				}
				// 그게 아니면, 윗줄과의 모든 상태를 고려하여, 최댓값을 계산.
				// dp[i][s] = max(  dp[i-1][ss]  ) (ss,s의 배치가 컨닝이 일어나지않는 경우)
				for(int ss =0; ss< 1<<m; ++ss){
					if(!chk(ss,i-1)) continue; // i-1번 줄이 ss의 배치가 불가능하면 무시.
					// 윗줄(ss)과 아랫줄(s)이 컨닝이 발생하지 않는다면
					if(can(ss,s)) 
						dp[i][s] = max(dp[i][s], dp[i-1][ss]+bitCnt(s)); // dp값갱신 
				}
				ans = max(ans,dp[i][s]); // ans갱신
			}
		}
		cout<<ans<<"\n";
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