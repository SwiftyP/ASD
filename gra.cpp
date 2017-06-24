#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define pii pair< int, int >
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)


struct comp 
{
    bool operator() (const pii &a, const pii &b) 
    {
        return a.second > b.second;
    }
};

const int MAX_N = 500001;
const int MAX_INT = 500001;

vector<pii> graf[MAX_N];
priority_queue< pii, vector< pii >, comp > Q;

int n, m;
int main()
{
	scanf("%d %d", &n, &m);
	int i, a, b, c;
	for(i = 0; i < m; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		graf[a].pb(mp(b,c));
		graf[b].pb(mp(a,c));
	}

	//init
	int ile_krokow[n + 1];
	int jaki_ostatni[n + 1];
	bool czy_odwiedzony[n + 1];

	for(i = 1; i < n + 1; i++) 
	{
		ile_krokow[i] = MAX_INT;
		jaki_ostatni[i] = -1;
		czy_odwiedzony[i] = false;
	}

	int starting = 1;
	ile_krokow[starting] = 0;
	jaki_ostatni[starting] = -1;

    Q.push(pii(starting, 0));

    int ja, sz, sasiad, kolor;
    // Dijkstra
    while(!Q.empty()) 
    {
        ja = Q.top().first;
        Q.pop();
        if(czy_odwiedzony[ja]) continue;
        sz = graf[ja].size();
        printf("licze teraz %d\n", ja);
        for(i = 0; i < sz; i++) {
            sasiad = graf[ja][i].first;
            kolor = graf[ja][i].second;
            if(!czy_odwiedzony[sasiad] && 
            	ile_krokow[ja] + 1 < ile_krokow[sasiad] && 
            	kolor != jaki_ostatni[ja]) 
            {
                ile_krokow[sasiad] = ile_krokow[ja] + 1;
                printf("sasiad=%d wartosc=%d\n",sasiad, ile_krokow[sasiad] );
                jaki_ostatni[sasiad] = kolor;
                Q.push(pii(sasiad, ile_krokow[sasiad]));
            }
        }
        czy_odwiedzony[ja] = 1; // done with u
    }

    for(i = 2; i <= n; i++)
    {
    	if(ile_krokow[i] == MAX_INT)
    		printf("%d\n", -1);
    	else
    		printf("%d\n", ile_krokow[i]);
    }



	return 0;
}