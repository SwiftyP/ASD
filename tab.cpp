#include <cstdio>
#include <map>
#include <string>


using namespace std;

const int MAX_N = 1001;

int n, m;
int t[MAX_N][MAX_N];
map<int, int> col[MAX_N];
map<int, int> row[MAX_N];
int count_r, count_c;

void pokaz_wynik()
{
	if(count_r == 0)
		printf("NIE ");
	else
		printf("TAK ");

	if(count_c == 0)
		printf("NIE\n");
	else
		printf("TAK\n");
}

void dodaj(int i, int j, int w)
{
	row[i][w]++;
	if(row[i][w] == 2)
		count_r++;

	col[j][w]++;
	if(col[j][w] == 2)
		count_c++;
}

void zdejmij(int i, int j, int w)
{
	row[i][w]--;
	if(row[i][w] == 1)
		count_r--;

	col[j][w]--;
	if(col[j][w] == 1)
		count_c--;
}



int main()
{
	int i, j, w;
	count_c = 0;
	count_r = 0;
	scanf("%d\n", &n);
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			scanf("%d",&t[i][j]);
			dodaj(i, j, t[i][j]);
		}
	}
	
	pokaz_wynik();

	scanf("%d\n", &m);
	for(int k = 0; k < m; k++)
	{
		scanf("%d %d %d\n", &i, &j, &w);
		zdejmij(i, j, t[i][j]);
		t[i][j] = w;
		dodaj(i, j, t[i][j]);
		pokaz_wynik();
	}


	return 0;
}