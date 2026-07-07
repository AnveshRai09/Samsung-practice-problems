#include <bits/stdc++.h>
using namespace std;
using ll = long long ; 

struct pace{
    int t ;
    int e ; 
};



void solve() {
    
    int dis, energy ;
    cin >> dis >> energy ;
    vector<pace> p(5) ;
    int maxE = INT_MIN ;
    for(int i = 0 ; i < 5 ; i++){
        int tm ,ts , e ;
        cin >> tm >> ts >> e ;
        p[i] = pace{tm*60 + ts , e} ;
        maxE = max( maxE , e) ; 
    }
    
    vector<vector<int>> dp ( dis+1 ,vector<int>( energy +1, 1e9  )) ;
    
    for( int i = 0 ; i < energy + 1; i++){
        dp[0][i] = 0 ; 
    }
    
    
    for ( int d = 1 ; d <= dis  ; d++){
        for( int en = energy ; en >= 0 ; en-- ){
            for( int i = 0 ; i < 5 ; i++){
            
                if( en + p[i].e <= energy )
                dp[d][en] = min(dp[d][en] , p[i].t + dp[d-1][en+p[i].e]) ;
            }
        }
    }
    
    int ans = INT_MAX  ; 
    
    for( int i = 0 ; i < energy+1; i++  ){
        ans = min( ans , dp[dis][i]) ;
    }
    cout << ans/60 << " " << ans%60  << endl ; 
}


int main() {
	
	int t ;
	if( cin >> t){
	    while(t--){
	        solve () ;
	    }
	}
	else solve() ;
	
	return 0 ;

}

// 5
// 30 130
// 4 50 7
// 5 0 5
// 5 10 4
// 5 20 3
// 5 30 2

// 10 50
// 4 0 10
// 4 30 8
// 5 0 5
// 5 30 3
// 6 0 2

// 15 100
// 3 45 12
// 4 15 9
// 5 0 6
// 5 45 4
// 6 30 2

// 5 15
// 5 0 4
// 5 30 3
// 6 0 2
// 6 30 1
// 7 0 0

// 20 80
// 4 10 5
// 4 20 4
// 4 30 3
// 4 40 2
// 4 50 1

// #1 153 20
// #2 46 0
// #3 68 0
// #4 29 0
// #5 85 0
