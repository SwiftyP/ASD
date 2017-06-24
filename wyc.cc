#include <stdio.h>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    int k;

    scanf ("%d", &n);
    scanf ("%d", &k);

    int prze = min(n + 2, k + 2); //prze - przesiadki
    long ile[2][n/2 + 2][prze];


    int pociag[n + 1]; // ile kosztowala podroz do miasta do miasta i
    int taxi[n + 1]; //ile kosztuje taxi w miescie i
    int samolot[n + 1]; // ile kosztowala podroz do miasta do miasta i

    pociag[0] = 0;
    scanf ("%d", &taxi[0]);
    samolot[0] = 0;

    for( int i = 1; i < n + 1; i++ ){
        scanf ("%d", &pociag[i]);
        scanf ("%d", &taxi[i]);
        scanf ("%d", &samolot[i]);
    }

    //zainicjowac ile
    for(int p = 0; p < 2; p++){
        for(int s = 0; s < n/2 + 2; s++){
            for(int t = 0; t < prze; t++){
                ile[p][s][t] = -1;
            }
        }
    }
    ile[0][0][0] = 0;

    int act = 0;
    int next;
    for(int i = 0; i < n; i++){
        next = (act + 1) % 2;
        for(int p = 0; p < min(i + 1, n/2 + 1); p++){ 
            for(int t = 0; t < min(i + 1, prze - 1); t++){
                if(ile[act][p][t] != -1){
                    if( t % 2 == 0 ){
                        if(ile[next][p + 1][t] == -1){
                            ile[next][p + 1][t] = ile[act][p][t] + pociag[i + 1];
                        }else{
                            ile[next][p + 1][t] = min(ile[act][p][t] + pociag[i + 1], ile[next][p + 1][t]);
                        }
                        if(ile[next][p][t + 1] == -1){ 
                            ile[next][p][t + 1] = ile[act][p][t] + taxi[i] + samolot[i + 1];
                        }else{
                            ile[next][p][t + 1] = min(ile[act][p][t] + taxi[i] + samolot[i + 1], ile[next][p][t + 1]);
                        }
                    }else{
                        if(ile[next][p][t] == -1){
                            ile[next][p][t] = ile[act][p][t] + samolot[i + 1];   
                        }else{
                            ile[next][p][t] = min(ile[act][p][t] + samolot[i + 1] , ile[next][p][t]);
                        }
                        if(ile[next][p + 1][t + 1] == -1){
                            ile[next][p + 1][t + 1] = ile[act][p][t] + taxi[i] + pociag[i + 1];
                        }else{
                            ile[next][p + 1][t + 1] = min(ile[act][p][t] + taxi[i] + pociag[i + 1], ile[next][p + 1][t + 1]);
                        }
                    }
                    ile[act][p][t] = -1;
                }
            }
        }
        act = next;
    }
    
    //znalezc ostateczne minimum
    int i = 3;
    long wynikNP = ile[act][n/2][1];

    while(i < min(n + 1, k + 1)){
        //printf("i = %d\n", i); 
        if(ile[act][n/2][i] < wynikNP){
            wynikNP = ile[act][n/2][i];
        }
        i += 2;
    }

    //jeszcze przypadek, ze koncze na dworcu i w ostatnim miescie taxi 

    if(k > 2){
        i = 4;
        long wynikP = ile[act][n/2][2] + taxi[n];
        while(i < min(n + 1, k)){
            if(ile[act][n/2][i] != -1 && ile[act][n/2][i] + taxi[n] < wynikP){
                wynikP = ile[act][n/2][i] + taxi[n];
            }
            i += 2;
        }
        long wynik = min(wynikNP, wynikP);
        printf( "%ld\n", wynik);
    }else{
        printf( "%ld\n", wynikNP);
    }
    return 0;
}    