/*
dp[i][j] = min(0 <= k <= j) dp[i - 1][k - 1] + cost(k, j); 
when opt(i, j) <= opt(i, j + 1) (QI is one of sufficient conditions)
dp[i][j] = 0 when j < 0
target: dp[m][n], TC: O(mn*log(n)*O(cost)) 
may require amortized tricks for cost 
*/

int m, n; 
vector<ll> dp, new_dp; 
ll cost(int i, int j);
void compute(int l, int r, int opt_l, int opt_r)
{
    if(l > r) return; 
    int mid = (l + r) / 2; 
    pair<ll, int> best = {LLONG_MAX, -1}; 
    for(int k = opt_l; k <= min(mid, opt_r); ++k) 
        best = min(best, {(k ? dp[k - 1] : 0) + cost(k, mid), k});  
    new_dp[mid] = best.first; 
    int opt = best.second; 
    compute(l, mid - 1, opt_l, opt); 
    compute(mid + 1, r, opt, opt_r); 
}
