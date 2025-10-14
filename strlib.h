struct strlib
{
    vector<int> compute_lps(const string &s)
    {
        int n = s.size(); vector<int> lps(n); 
        for(int i = 1, j = 0; i < n; ++i)
        {
            while(j && s[i] != s[j]) j = lps[j - 1];
            j += (s[i] == s[j]);  
            lps[i] = j;  
        }
        return lps; 
    }

    vector<int> compute_z(const string &s) 
    {
        int n = s.size(); vector<int> z(n); 
        for(int i = 1, l = 0, r = 0; i < n; ++i) // [l, r) 
        {
            if(i < r) z[i] = min(r - i, z[i - l]);
            while(i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
            if(i + z[i] > r) l = i, r = i + z[i];  
        }
    }

    vector<int> manacher(const string &s)
    {
        int n = (s.size() << 1) | 1; 
        vector<int> p(n, 1);
        auto is_same = [&](int i, int j) {
            return (i & 1) == (j & 1) && (!(i & 1) || s[i >> 1] == s[j >> 1]);
        } ; 
        for(int i = 1, l = 0, r = 0; i < n; ++i)
        {
            if(i < r) p[i] = min(r - i, p[l + r - i - 1]);
            while(i + p[i] < n && i - p[i] >= 0 && is_same(i + p[i], i - p[i])) ++p[i]; 
            if(i + p[i] > r) r = i + p[i], l = i - p[i] + 1; 
        }
        return p; 
    }
 
    int kmp(const string &pat, const string &s)
    {
        auto lps = compute_lps(pat); 
        int cnt = 0, n = pat.size(), prev = -1; 
        for(int i = 0, j = 0; i < s.size(); i++)
        {
            while(j && s[i] != pat[j]) j = lps[j - 1]; 
            j += (s[i] == pat[j]); 
            if(j == n)
            {
                j = lps[j - 1]; 
                cnt += (i - n >= prev); 
                // prev = i; // disjoint kmp 
            }
        }
        return cnt; 
    }
};
