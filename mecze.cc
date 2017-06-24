#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

int main(){
    int zawodnicy;
    int mecze;
    scanf ( "%d", &zawodnicy );
    scanf ( "%d", &mecze );
    vector< long long > sklad;
    vector< long long >::iterator it;

    for ( int i = 0; i < zawodnicy; i++ ){
        it = sklad.end();
        sklad.insert( it, 0 );
    }

    int nrZawodnika;
    for ( int i = 0; i < mecze; i++ ){
        for ( int j = 0; j < (zawodnicy/2); j++ ){
            scanf ( "%d", &nrZawodnika );
            sklad.at( nrZawodnika - 1 ) += pow (2, i);
        }
        for ( int j = (zawodnicy/2); j< zawodnicy; j++){
            scanf ( "%d", &nrZawodnika );
        }
    }

    std::sort(sklad.begin(), sklad.end());

    for( int i = 0; i < (zawodnicy - 1); i++ ){
        if( sklad.at( i ) == sklad.at( i + 1 )){
            printf("NIE\n");
            return 0;
        }
    }
    printf("TAK\n");
    return 0;
}