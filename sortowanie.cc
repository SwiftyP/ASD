#include <iostream>

const int mod = 1000000000;
int ciag[1000];
long long podciagi[1000][1000][2];

long long policz(int pocz, int kon, int rodzaj){
  if( pocz == kon ){
    podciagi[pocz][kon][rodzaj] = rodzaj;
  }else{
    if(rodzaj == 1){
        if(ciag[ kon ] > ciag[ kon - 1 ])
            podciagi[pocz][kon][rodzaj] += podciagi[pocz][kon-1][1];
        if(ciag[ kon ] > ciag[ pocz ])
            podciagi[pocz][kon][rodzaj] += podciagi[pocz][kon-1][0];
    }else{
        if(ciag[ pocz ] < ciag[ pocz + 1 ])
            podciagi[pocz][kon][rodzaj] += podciagi[pocz + 1][kon][0];
        if(ciag[ pocz ] < ciag[ kon ])
            podciagi[pocz][kon][rodzaj] += podciagi[pocz + 1][kon][1];
    }
  }
  podciagi[pocz][kon][rodzaj] = podciagi[pocz][kon][rodzaj] % mod;
  return podciagi[pocz][kon][rodzaj];
}

int main(){
    int dlugosc;
    std::cin >> dlugosc;
    for(int i = 0; i < dlugosc; i++){
      std::cin >> ciag[ i ];
    }

    int x ;
    int y;

    long long wynik = 0;
    for( int i = 0; i < dlugosc; i++ ){
      for( int j = 0; j < ( dlugosc - i ); j++ ){
        x = policz( j, j + i, 0 );
        y = policz( j, j + i, 1 );
        wynik = x + y;
        //std::cout << x << " " << y << "- ciagi od "<< j <<" do "<< j + i << " = " << wynik<<std::endl;
      }
    }
    std::cout << ( wynik % mod );

    return 0;
}