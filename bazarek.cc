#include <iostream>
#include <stdio.h>

using namespace std;

const int N = 1000000;
int cenyProduktow[ N ];
long long sufix[ N ];
int mniejszyParzysty[ N ];
int mniejszyNieparzysty[ N ];
int wiekszyParzysty[ N ];
int wiekszyNieparzysty[ N ];


void policzMniejszeIWiekszeOrazSufixy( int rozmiar ) {

    sufix[ rozmiar -1 ] = cenyProduktow[ rozmiar -1 ];

    mniejszyNieparzysty[ 0 ] = -1;
    mniejszyParzysty[ 0 ] = -1;
    wiekszyNieparzysty[ rozmiar - 1 ] = -1;
    wiekszyParzysty[ rozmiar - 1 ] = -1;

    for( int i = 1; i < rozmiar; i++ ){
        if( cenyProduktow[ i - 1 ] % 2 == 1 ){
            mniejszyNieparzysty[ i ] = cenyProduktow[ i - 1 ];
            mniejszyParzysty[ i ] = mniejszyParzysty[ i - 1 ];
        }else{
            mniejszyNieparzysty[ i ] = mniejszyNieparzysty[ i - 1 ];
            mniejszyParzysty[ i ] = cenyProduktow[ i - 1 ];
        }
    }

    for(int i = rozmiar - 2; i > -1; i-- ){
        sufix[ i ] = sufix[ i + 1 ] + cenyProduktow[ i ];
        if( cenyProduktow[ i + 1 ] % 2 == 1 ){
            wiekszyNieparzysty[ i ] = cenyProduktow[ i + 1 ];
            wiekszyParzysty[ i ] = wiekszyParzysty[ i + 1 ];
        }else{
            wiekszyNieparzysty[ i ] = wiekszyNieparzysty[ i + 1 ];
            wiekszyParzysty[ i ] = cenyProduktow[ i + 1 ];
        }
    }
}

long long policzIleWystarczy( int k, int & n ){

    if( sufix[ n - k ] % 2 == 1 ){
        return sufix[ n - k ];
    }else{
        if( k == 1 ){
            return mniejszyNieparzysty[ n - k ];
        }else{
            long long kandydat1 = -1;
            long long kandydat2 = -1;
            long long kandydat3 = -1;
            if( wiekszyNieparzysty[ n - k] != -1 && mniejszyParzysty[ n - k ] != -1 ){
                kandydat1 = sufix[ n - k ] - wiekszyNieparzysty[ n - k ] + mniejszyParzysty[ n - k ];
            }
            if( wiekszyParzysty[ n - k ] != -1 && mniejszyNieparzysty[ n - k ] != -1 ){
                kandydat2 = sufix[ n - k ] - wiekszyParzysty[ n - k ] + mniejszyNieparzysty[ n - k ];
            }
            if( cenyProduktow[ n - k ] % 2 == 0 ){
                if( mniejszyNieparzysty[ n - k ] != -1){
                    kandydat3 = sufix[ n - k ] - cenyProduktow[ n - k ] + mniejszyNieparzysty[ n - k ];
                }else{
                    return max( kandydat1, kandydat2 );
                }
            }else{
                if( mniejszyParzysty[ n - k ] != -1){
                    kandydat3 = sufix[ n - k ] - cenyProduktow[ n - k ] + mniejszyParzysty[ n - k ];
                }else{
                    return max( kandydat1, kandydat2 );
                }
            }
            return max( max( kandydat1, kandydat2 ), kandydat3 );
        }
    }
}

int main(){
    int produkty;
    int dni;
    long long wystarczy;

    //cin >> produkty;
    scanf ("%d", &produkty);

    for( int i = 0; i < produkty; i++ ){
       //cin >> cenyProduktow[ i ];
       scanf ("%d", &cenyProduktow[ i ]);
    }

    policzMniejszeIWiekszeOrazSufixy(produkty);

    //cin >> dni;
    scanf("%d", &dni);
    int ile[ dni ];
    for( int j = 0; j < dni; j++ ){
        //cin >> ile[ j ];
        scanf("%d", &ile[ j ]);
    }

    for( int k = 0; k < dni; k++ ){
        wystarczy = policzIleWystarczy( ile[ k ], produkty  );
        printf( "%lld\n", wystarczy);
        //cout << wystarczy << endl;
    }
    return 0;
}
