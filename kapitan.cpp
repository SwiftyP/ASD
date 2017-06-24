#include <cstdio>
#include <cmath> //abs
#include <algorithm>
#include <vector>
#include <queue>

#define pii pair< int, int >
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)

using namespace std;

const int MAX_INT = 1000000001;
const int MAX_N = 200001;

struct comp 
{
    bool operator() (const pii &a, const pii &b) 
    {
        return a.second > b.second;
    }
};

struct wezel
{
	int id;
	pii wsp;
};

int n;
vector<wezel> W;
vector<pii> N[MAX_N + 1]; //kto i ile; numerowanie od 1
priority_queue< pii, vector< pii >, comp > Q;

bool por_id (wezel w1, wezel w2) 
{ 
	return (w1.id < w2.id); 
}

bool por_x (wezel w1, wezel w2) 
{ 
	return (w1.wsp.first < w2.wsp.first); 
}

bool por_y (wezel w1, wezel w2) 
{ 
	return (w1.wsp.second < w2.wsp.second); 
}

int odl(pii  p1, pii  p2)
{
	int x = abs(p1.first - p2.first);
	int y = abs(p1.second - p2.second);
	return min(x, y);
}

void znajdz()
{
	wezel pop, akt, nast;
	int akt_id;
	for(int i = 1; i < n - 1; i++)
	{
		pop = W.at(i - 1);
		akt = W.at(i);
		akt_id = akt.id;
		nast = W.at(i + 1);
		pii p1 = mp(pop.id, odl(pop.wsp, akt.wsp));
		if(find(N[akt_id].begin(), N[akt_id].end(), p1) == N[akt_id].end())
			N[akt_id].pb(p1);
		
		pii p2 = mp(nast.id, odl(nast.wsp, akt.wsp));
		if(find(N[akt_id].begin(), N[akt_id].end(), p2) == N[akt_id].end())
			N[akt_id].pb(p2);
	}

	//pierwszy
	int i = 0;
	akt = W.at(i);
	akt_id = akt.id;
	nast = W.at(i + 1);
	pii pp = mp(nast.id, odl(nast.wsp, akt.wsp));
	if(find(N[akt_id].begin(), N[akt_id].end(), pp) == N[akt_id].end())
		N[akt_id].pb(pp);

	//ostatni
	i = n - 1;
	pop = W.at(i - 1);
	akt = W.at(i);
	akt_id = akt.id;
	pii po = mp(pop.id, odl(pop.wsp, akt.wsp));
	if(find(N[akt_id].begin(), N[akt_id].end(), po) == N[akt_id].end())
		N[akt_id].pb(po);
	
}

int main()
{
	scanf("%d", &n);

	int x, y, i;
	for(i = 1; i <= n; i++)
	{
		scanf("%d %d", &x, &y);		
		wezel v;
		v.id = i;
		v.wsp = mp(x, y);
		W.pb(v);
	}
	
	sort(W.begin(), W.end(), por_x);
	znajdz();
	sort(W.begin(), W.end(), por_y);
	znajdz();

	//init
	int D[n + 1];
	bool F[n + 1];

	for(i = 1; i < n + 1; i++) 
	{
		D[i] = MAX_INT;
		F[i] = false;
	}
	int starting = 1;
    D[starting] = 0;
    Q.push(pii(starting, 0));

    int u, sz, v, w;
    // Dijkstra
    while(!Q.empty()) 
    {
        u = Q.top().first;
        Q.pop();
        if(F[u]) continue;
        sz = N[u].size();
        for(i = 0; i < sz; i++) {
            v = N[u][i].first;
            w = N[u][i].second;
            if(!F[v] && D[u] + w < D[v]) 
            {
                D[v] = D[u] + w;
                Q.push(pii(v, D[v]));
            }
        }
        F[u] = 1; // done with u
    }
  	printf("%d\n", D[n]);
	return 0;
}