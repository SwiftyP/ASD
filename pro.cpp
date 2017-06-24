#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <utility>

const int MAX_N = 100010;

using namespace std;

struct Wezel
{
	int stopien, ile_p;
	vector<int> sasiedzi;
};

Wezel T[MAX_N];
set<pair<int, int> > Q;

int main()
{

	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i<=n; i++)
		scanf("%d",&T[i].ile_p);
	
	int a, b;
	for(int i = 1; i<=m; i++) 
	{
		scanf("%d %d", &a, &b);
		T[b].sasiedzi.push_back(a);
		T[a].stopien++;
	}

	for (int i = 1; i <=n; i++)
	{
		if(T[i].stopien == 0)
			Q.insert(make_pair(T[i].ile_p, i));
	}

	int result = 0;
	while(k > 0)
	{
		auto it = Q.begin();
		pair<int, int> v = *it;
		Q.erase(it);
		result = max(result, v.first);
		for(auto ite = T[v.second].sasiedzi.begin(); ite != T[v.second].sasiedzi.end(); ite++)
		{
			T[*ite].stopien--;
			if(T[*ite].stopien == 0)
				Q.insert(make_pair(T[*ite].ile_p, *ite));
		}
		k--;
	}

	printf("%d\n", result);

	return 0;
}