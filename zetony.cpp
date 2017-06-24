#include <cstdio>

const int MAX_N = 1000001;

int n, z;
int ile_jakich[MAX_N];
int max_wysokosc, ile_roznych;

void wypisz()
{
	for(int j = 1; j <= max_wysokosc; j++)
	{
		if(ile_jakich[j]!=0)
			printf("%d => %d\n", j, ile_jakich[j]);
	}
	printf("\n");
}


void zrobPodzial(int w)
{
	int klucz = max_wysokosc;
	if(ile_jakich[klucz] > w){
		ile_jakich[klucz] -= w;


    int p;

    p = klucz/2 + (klucz % 2);
    if(ile_jakich[p] == 0)
    	ile_roznych++;
    ile_jakich[p] += w;

	p = klucz/2;
	if(ile_jakich[p] == 0)
    	ile_roznych++;
	ile_jakich[p] += w;



	}else if(ile_jakich[klucz] == w){
		ile_jakich[klucz] = 0;
		ile_roznych--;
		while(max_wysokosc > -1 && ile_jakich[max_wysokosc] == 0)
			max_wysokosc--;


    int p;

    p = klucz/2 + (klucz % 2);
    if(ile_jakich[p] == 0)
    	ile_roznych++;
    ile_jakich[p] += w;

	p = klucz/2;
	if(ile_jakich[p] == 0)
    	ile_roznych++;
	ile_jakich[p] += w;


	}else{
		int t = ile_jakich[klucz];
		w = w - t;
		ile_jakich[klucz] = 0;
		ile_roznych--;
		while(max_wysokosc > -1 && ile_jakich[max_wysokosc] == 0)
			max_wysokosc--;


    int p;

    p = klucz/2 + (klucz % 2);
    if(ile_jakich[p] == 0)
    	ile_roznych++;
    ile_jakich[p] += t;

	p = klucz/2;
	if(ile_jakich[p] == 0)
    	ile_roznych++;
	ile_jakich[p] += t;


		//zrob jeszcze 
		zrobPodzial(w);
	}
	//wypisz();
}

int main()
{
	int i;
	scanf("%d\n", &n);
	int w;
	max_wysokosc = -1;
	ile_roznych = 0;
	for(i = 0; i < n; i++)
	{
		scanf("%d", &w);
		if(w > max_wysokosc)
			max_wysokosc = w;
		if(ile_jakich[w] == 0)
			ile_roznych++;
		ile_jakich[w]++;
	}

	scanf("%d", &z);
	for(i = 0; i < z; i++)
	{
		scanf("%d", &w);
		zrobPodzial(w);
		printf("%d\n", ile_roznych);
	}	
	return 0;
}