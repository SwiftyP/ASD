#include <string>
#include <iostream>
#include <algorithm>

int main(){
    std::string dane;
    std::cin >> dane;

    size_t i = 0;
    while( dane[ i ] == '*' && i < dane.size() ){
       i++;
    }
    if( i == dane.size() ){
        std::cout << 1 << std::endl;
        return 0;
    }else{
        char poprzedni = dane[ i ];
        int minOdl = 0;
        int krok = 0;
        for ( size_t j = i + 1; j < dane.size(); j++ ){
            if( poprzedni != dane[ j ] ){
                krok++;
                if( dane[ j ] != '*' ){
                    if( minOdl == 0 ){
                        minOdl = krok;
                    }else{
                        minOdl = std::min( minOdl, krok );
                    }
                    krok = 0;
                    poprzedni = dane[ j ];
                }
            }else{
                krok = 0;
            }
        }
        if ( minOdl == 0 ){
            std::cout << 1 << std::endl;
            return 0;
        }else{
            std::cout << dane.size() - minOdl + 1 << std::endl;
            return 0;
        }
    }
}
