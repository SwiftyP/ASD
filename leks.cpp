#include <cstdio>
#include <algorithm> //min

const int MAX_N = 300007;
const long long MOD = 1000000007;
const int x = 37LL;

int n, m;

long long h[MAX_N];
long long potega[MAX_N];
char a[MAX_N];

bool rowne(int p1, int k1, int p2, int k2)
{
	long long w1, w2;
	w1 = (h[p1] - (h[k1 + 1]*potega[k1 - p1 + 1]) % MOD) % MOD;
	w2 = (h[p2] - (h[k2 + 1]*potega[k2 - p2 + 1]) % MOD) % MOD;
	if(w1 < 0)
    	w1 += MOD;
    if(w2 < 0)
    	w2 += MOD;
    
	return w1 == w2;
}

char zapytanie(int p1, int k1, int p2, int k2)
{
	if(k1 - p1 == k2 - p2 && rowne(p1, k1, p2, k2))
		return '=';
	if(k1 - p1 < k2 - p2 && rowne(p1, k1, p2, p2 + k1 - p1))
		return '<';
	if(k1 - p1 > k2 - p2 && rowne(p1, p1 + k2 - p2, p2, k2))
		return '>';

	int maxlen = std::min(k1 - p1, k2 - p2);
    int p = 0, q = maxlen, mid = (maxlen)/2;
    
    while(p != q) { 
    
        if(rowne(p1, p1 + mid, p2, p2 + mid)) {
            p = mid + 1;
        } else {
            q = mid;
        }
        mid = (p+q)/2;
    }
    
    if(a[p1 + p] < a[p2 + p])
        return '<';
    else
        return '>';
}


int main()
{
	int i;

	scanf("%d %d\n", &n, &m);

	potega[0] = 1;
	for(i = 1; i <= n; i++)
	{
		potega[i] = (potega[i - 1] * x) % MOD;
		scanf("%c", &a[i]);
	}
	potega[n + 1] = (potega[n] * x) % MOD;

	h[n + 1] = 0;
	for(i = n; i > 0; i--)
	{
		h[i] = (a[i] + (x * h[i + 1]) % MOD) % MOD;
	}
	

	
	int p1, k1, p2, k2; 
	for(i = 0; i < m; i++)
	{
		scanf("%d %d %d %d", &p1, &k1, &p2, &k2);
		printf("%c\n", zapytanie(p1, k1, p2, k2));
	}
	return 0;
}
