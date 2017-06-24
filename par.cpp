#include <cstdio>
#include <math.h>    // log2, pow, floor

//using namespace std;

//const int MAX_N = 500001;
//const int MAX_LOGN = 20;
const int LISC = -1;

struct Wezel {
	int lewy_syn, prawy_syn;
	int glebokosc;
	int max_w_moim, kto_w_moim;
	int max_nie_w_moim, kto_nie_w_moim;
};

int S[500001][20];
Wezel T[500001];
int logarytm;
//int n;

void wypelnij_w_dol(int v, int h)
{
	T[v].glebokosc = h;
	T[v].max_w_moim = 0;
	T[v].kto_w_moim = v;
	if(T[v].lewy_syn != LISC) {
		wypelnij_w_dol(T[v].lewy_syn, h + 1);
		T[v].max_w_moim = T[T[v].lewy_syn].max_w_moim + 1;
		T[v].kto_w_moim = T[T[v].lewy_syn].kto_w_moim;
	}
	if(T[v].prawy_syn != LISC) {
		wypelnij_w_dol(T[v].prawy_syn, h + 1);
		if(T[v].max_w_moim < T[T[v].prawy_syn].max_w_moim + 1) {
			T[v].max_w_moim = T[T[v].prawy_syn].max_w_moim + 1;
			T[v].kto_w_moim = T[T[v].prawy_syn].kto_w_moim;
		}
	}
}

void wypelnij_w_gore(int v) 
{
	int rodzic = S[v][0];
  	T[v].max_nie_w_moim = T[rodzic].max_nie_w_moim + 1;
  	T[v].kto_nie_w_moim = T[rodzic].kto_nie_w_moim;

  	int brat;
  	if(T[rodzic].lewy_syn == v)
		brat = T[rodzic].prawy_syn;
	else
		brat = T[rodzic].lewy_syn;

  	if(brat != LISC) {
		if(T[v].max_nie_w_moim < T[brat].max_w_moim + 2) { // <=
  			T[v].max_nie_w_moim = T[brat].max_w_moim + 2;
  			T[v].kto_nie_w_moim = T[brat].kto_w_moim;
  		}
  	}

  	if(T[v].lewy_syn != LISC)
		wypelnij_w_gore(T[v].lewy_syn);
	if(T[v].prawy_syn != LISC)
		wypelnij_w_gore(T[v].prawy_syn);
}


int up(int v, int h)
{
	int res = v;
	int k = logarytm;
	while(h > 0){
		if(pow(2,k) > h)
			k--;
		else{
			res = S[res][k];
			h = h - pow(2,k);
		}
	}
	return res;
}


int LCA(int v, int u) 
{

	if(T[u].glebokosc < T[v].glebokosc) {
    	v = up(v, T[v].glebokosc - T[u].glebokosc);
  	} else if (T[u].glebokosc > T[v].glebokosc) {
  		u = up(u, T[u].glebokosc - T[v].glebokosc);
  	}
	if(u == v)
    	  return u;
  	else {
  		int i = logarytm;
  		while(i >= 0) {
  			if(S[u][i] != S[v][i]){
  				u = S[u][i];
  				v = S[v][i];
  			}
  			i--;
  		}
  		return S[u][0];
  	}
}

int oblicz(int v, int d) 
{
	int d_max, v_max;

	if(T[v].max_w_moim < T[v].max_nie_w_moim) {
		d_max = T[v].max_nie_w_moim;
		v_max = T[v].kto_nie_w_moim;
	} else {
		d_max = T[v].max_w_moim;
		v_max = T[v].kto_w_moim;
	}

	if(d > d_max)
		return -1;
	else {
		int wspolny = LCA(v, v_max);
		int d1 = T[v].glebokosc - T[wspolny].glebokosc;
		if(d <= d1)
			return up(v, d);
		else
			return up(v_max, d_max - d);
	}
}

int main() {

	int n;
	scanf("%d", &n);
	
	for(int i = 0; i <= n; i++){
		for(int j = 0; 1 << j <= n; j++){
			S[i][j] = -1;
		}
	}

	int l, p;
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &l, &p);
		T[i].lewy_syn = l;
		T[i].prawy_syn = p;
		if(l != LISC) //korzen bedzie mial nie ustawione
			S[l][0] = i;
		if(p != LISC)
			S[p][0] = i;
	}

	for(int j = 1; 1 << j <= n; j++){
		for(int i = 1; i <= n; i++){
			if(S[i][j - 1] != -1)
				S[i][j] = S[S[i][j - 1]][j - 1];
		}
	}

	wypelnij_w_dol(1, 0);

	logarytm = floor(log2(T[1].max_w_moim)); 
	T[1].max_nie_w_moim = 0;
	T[1].kto_nie_w_moim = 1;

	if(T[1].lewy_syn != LISC)
		wypelnij_w_gore(T[1].lewy_syn);
	if(T[1].prawy_syn != LISC)
		wypelnij_w_gore(T[1].prawy_syn);

	int m, skad, d;
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &skad, &d);
		printf("%d\n", oblicz(skad, d));
	}
}