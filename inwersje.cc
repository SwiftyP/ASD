#include <stdio.h>
#include <vector>
#include <math.h>

const long mod =  1000000000;

using namespace std;

void wstaw ( int id, int v, vector < int >  &drzewo ){
  int i = id;
  while (i != 0 ){
        drzewo.at( i ) += v;
        drzewo.at( i ) = drzewo.at( i )% mod;
        i = ( i - 1 ) / 2;
  }
  drzewo.at( i ) += v;
  drzewo.at( i ) = drzewo.at( i ) % mod;
}

int sumuj ( int id, vector < int > &drzewo ){
    int s = 0;
    int i = id;
    while( i != 0 ){
       if ( ( i % 2 ) == 1 ){
            s += drzewo.at( i + 1 ) ;
            s = s  % mod;
       }
       i = ( i - 1 ) / 2;
    }
    return s;
}

int policz( int n ){
    if ( n == 1 ){
        return 0;
    }else{
        double calkowita;
        calkowita = ceil( log2 ( n ) );
        return pow( 2, calkowita ) - 2;
    }
}

int przejdz( int n, int dane[] ,int k){
    int s[ n ];
    int c = policz( n );
    vector < int > drzewo ( ( c + 2 ) * 2, 0 );
    int wynik=0;
    for ( int j = 0; j < n - 1; j++ ){
        wstaw( dane[ j ] + c, 1, drzewo );
        s[ dane[ j + 1 ] ] = sumuj( dane[ j + 1 ] + c, drzewo );
        s[ dane[ j + 1 ] ] = s[ dane[ j + 1 ] ]  % mod;
    }
    drzewo.assign(( c + 2 ) * 2,0);

    for ( int i = 1; i < k; i++ ){
        wstaw( dane[ i ] + c, s[ dane[ i ] ], drzewo );
        for( int l = i + 1; l < n; l++ ){
            wstaw( dane[ l ] + c, s[ dane[ l ] ], drzewo );
            s[ dane[ l ] ] = sumuj( dane[ l ] + c, drzewo );
            s[ dane[ l ] ] = s[ dane[ l ] ] % mod;
        }
        wynik = drzewo.at(0);
        drzewo.assign(( c + 2 ) * 2,0);
    }
    return wynik;
}

int main(){
    int n;
    int k;
    scanf ( "%d", &n );
    scanf ( "%d", &k );
    int dane[ n ];
    for(int i = 0; i < n; i++ ){
        scanf ( "%d", &dane[ i ] );
    }
    printf("%d", przejdz(n,dane,k));
  return 0;
}

