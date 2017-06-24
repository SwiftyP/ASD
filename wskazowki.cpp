#include <stdio.h>
#include <math.h>

const int MAX_N = 100001;

struct Wezel
{
	int przed_wsk, klucz, ost_msc;
	char kierunek;
};

struct Punkt
{
	int x, y, kierunek;
	int poczatek, koniec;
};

using namespace std;

Wezel dane[MAX_N];
int n;

Punkt daj_wynik(Punkt pierwszy, Punkt drugi)
{
	int x = 0;
	int y = 0;
		switch(pierwszy.kierunek) {
		case 0: // N
			x = drugi.x;
			y = drugi.y; 
			pierwszy.kierunek = drugi.kierunek;
			break;
		case 1: // S
			x = -drugi.x;
			y = -drugi.y;
			switch(drugi.kierunek){
				case 0:
					pierwszy.kierunek = 1;
				break;
				case 1:
					pierwszy.kierunek = 0;
				break;
				case 2:
					pierwszy.kierunek = 3;
				break;
				case 3:
					pierwszy.kierunek = 2;
				break;
				default:
				break;
			}
			break;
		case 2: // E
			x = drugi.y; 
			y = -drugi.x; 
			switch(drugi.kierunek){
				case 0:
					pierwszy.kierunek = 2;
				break;
				case 1:
					pierwszy.kierunek = 3;
				break;
				case 2:
					pierwszy.kierunek = 1;
				break;
				case 3:
					pierwszy.kierunek = 0;
				break;
				default:
				break;
			}
			break;
		case 3: // W
			x = -drugi.y; 
			y = drugi.x; 
			switch(drugi.kierunek){
				case 0:
					pierwszy.kierunek = 3;
				break;
				case 1:
					pierwszy.kierunek = 2;
				break;
				case 2:
					pierwszy.kierunek = 0;
				break;
				case 3:
					pierwszy.kierunek = 1;
				break;
				default:
				break;
			}
			break; 
		default: 
			printf("nie powinno Cie tu byc\n");
    		break;
	}

	pierwszy.x += x;
	pierwszy.y += y;
	return pierwszy;


}

void dodaj(Punkt &pierwszy, Punkt drugi)
{
	int x = 0;
	int y = 0;
		switch(pierwszy.kierunek) {
		case 0: // N
			x = drugi.x;
			y = drugi.y; 
			pierwszy.kierunek = drugi.kierunek;
			break;
		case 1: // S
			x = -drugi.x;
			y = -drugi.y;
			switch(drugi.kierunek){
				case 0:
					pierwszy.kierunek = 1;
				break;
				case 1:
					pierwszy.kierunek = 0;
				break;
				case 2:
					pierwszy.kierunek = 3;
				break;
				case 3:
					pierwszy.kierunek = 2;
				break;
				default:
				break;
			}
			break;
		case 2: // E
			x = drugi.y;
			y = -drugi.x;
			switch(drugi.kierunek){
				case 0:
					pierwszy.kierunek = 2;
				break;
				case 1:
					pierwszy.kierunek = 3;
				break;
				case 2:
					pierwszy.kierunek = 1;
				break;
				case 3:
					pierwszy.kierunek = 0;
				break;
				default:
				break;
			}
			break;
		case 3: // W
			x = -drugi.y;
			y = drugi.x; 
			switch(drugi.kierunek){
				case 0:
					pierwszy.kierunek = 3;
				break;
				case 1:
					pierwszy.kierunek = 2;
				break;
				case 2:
					pierwszy.kierunek = 0;
				break;
				case 3:
					pierwszy.kierunek = 1;
				break;
				default:
				break;
			}
			break; 
		default: // jakis blad
			printf("nie powinno Cie tu byc\n");
    		break;
	}

	pierwszy.x += x;
	pierwszy.y += y;
}

int main ()
{

  	int k, d, i;
  	char c;

  	scanf("%d", &n);

  	for(i = 1; i <= n; i++) { 
    	scanf("%d %c %d", &k, &c, &d); 
    	dane[i].przed_wsk = k;
    	dane[i].klucz = d;
    	dane[i].kierunek = c;
    }

    int t = pow(2,ceil(log2(n))); //tyle lisci
    int pomocna[2*t - 1]; //pomocne drzewo przedzialowe
    int tmp = 1;

    for(i = t - 1; i < (2*t - 1); i++) { //inicjacja lisci
    	if(tmp <= n)
    		pomocna[i] = 1;
    	else
    		pomocna[i] = 0;
    	tmp++;
    }

    for(i = t - 2; i > -1; i--) { //inicjacja pozostalych
    	pomocna[i] = pomocna[i*2 + 1] + pomocna[i*2 + 2];
    }

 	int v, lewy, prawy;
    for(i = n; i > -1; i--) {
    	tmp = dane[i].przed_wsk;
    	v = 0;

    	while(v <= t - 2) {
    		//printf("--- %d\n", v);
    		pomocna[v]--;
    		lewy = 2*v + 1;
    		prawy = 2*v + 2;
    		if(pomocna[lewy] >= tmp) { // wstaw w lewym
    			v = lewy;
    		} else { //wstaw w prawym
    			v = prawy;
    			tmp = tmp - pomocna[lewy];
    		}
    	}
    	pomocna[v]--;
    	dane[i].ost_msc = v - (t - 2);
    }

    Punkt odpowiedzi[2*t - 1];
	//zainicjuj liscie
    for(i = t - 1; i < (2*t - 1); i++) {
    	odpowiedzi[i].x = 0;
    	odpowiedzi[i].y = 0;
    	odpowiedzi[i].kierunek = 0;
    	odpowiedzi[i].poczatek = i - (t - 2);
    	odpowiedzi[i].koniec = i - (t - 2);
    }

    //zainicjuj rodzicow
    for(i = t - 2; i > - 1; i--) {
    	odpowiedzi[i].x = 0;
    	odpowiedzi[i].y = 0;
    	odpowiedzi[i].kierunek = 0;
    	odpowiedzi[i].poczatek = odpowiedzi[2*i + 1].poczatek;
    	odpowiedzi[i].koniec =  odpowiedzi[2*i + 2].koniec;
    }

    int rodzic;

    for(i = 1; i <= n ; i++) {
    	v = dane[i].ost_msc + (t - printf);
    	//2("%d\n", v);

    	if(dane[i].kierunek == 'L') {
			odpowiedzi[v].x -= dane[i].klucz;
			odpowiedzi[v].kierunek = 3;
		} else if(dane[i].kierunek == 'R') {
			odpowiedzi[v].x += dane[i].klucz;
			odpowiedzi[v].kierunek = 2;
		} else {
			odpowiedzi[v].y -= dane[i].klucz;
			odpowiedzi[v].kierunek = 1;
		}

    	while(v != 0) { //update rodzica
    		rodzic = (v - 1)/2;
    		if(v%2 == 0) { // jestem prawym synem
    			odpowiedzi[rodzic].x = odpowiedzi[v - 1].x;
    			odpowiedzi[rodzic].y = odpowiedzi[v - 1].y;
    			odpowiedzi[rodzic].kierunek = odpowiedzi[v - 1].kierunek;
    			//dodaj v do wyniku
    			dodaj(odpowiedzi[rodzic], odpowiedzi[v]);    			
    		} else { // jestem lewym synem
    			odpowiedzi[rodzic].x = odpowiedzi[v].x;
    			odpowiedzi[rodzic].y = odpowiedzi[v].y;
    			odpowiedzi[rodzic].kierunek = odpowiedzi[v].kierunek;
    			//dodaj v + 1 do wyniku
				dodaj(odpowiedzi[rodzic], odpowiedzi[v + 1]);    			
    		}
    		
    		v = rodzic;
    		//printf("v=%d\n", v);
    	}

    	//wypisz od 1 do dane[i].ost_msc
    	lewy = 1 + (t - 2);
    	prawy = dane[i].ost_msc + (t - 2);
    	//printf("lewy=%d prawy=%d\n", lewy, prawy);

    	bool koniec = false;
    	Punkt wynik;
    	int policz_do = odpowiedzi[prawy].koniec;

    	wynik.x = 0;
    	wynik.y = 0;
    	wynik.kierunek = 0;

    	v = 0;



    	while(!koniec){
    		if(odpowiedzi[v].koniec == policz_do){
    			wynik = daj_wynik(wynik, odpowiedzi[v]); 
    			koniec = true;
    		}else{
    			if(odpowiedzi[2*v + 1].koniec < policz_do){
    				wynik = daj_wynik(wynik, odpowiedzi[2*v + 1]);
    				v = 2*v + 2; 
    			}else if(odpowiedzi[2*v + 1].koniec > policz_do){
    				v = 2*v + 1;
    			}else{
    				wynik = daj_wynik(wynik, odpowiedzi[2*v + 1]);
    				koniec = true;
    			}
    		}
    	}

    	printf("%d %d\n", wynik.x, wynik.y);
    }


  return 0;
}