#include <cstdio>

const int MAX_N = 500001;
struct wezel
{
	int pop;
	int nast;
};

int n;
wezel zolnierze[MAX_N];

int main()
{
	scanf("%d\n", &n);
	int i, z;

	for(i = 2; i < n; i++)
	{
		zolnierze[i].pop = i - 1;
		zolnierze[i].nast = i + 1;
	}

	zolnierze[1].pop = -1;
	zolnierze[1].nast = 2;
	
	zolnierze[n].pop = n-1;
	zolnierze[n].nast = -1;

	int po, na;
	for(i = 1; i <= n; i++)
	{  
		scanf("%d", &z);
		po = zolnierze[z].pop;
		na = zolnierze[z].nast;
		printf("%d %d\n", po, na);
		if(po != -1)
			zolnierze[po].nast = na;
		if(na != -1)
			zolnierze[na].pop = po;
	}

	return 0;
}