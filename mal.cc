#include <stdio.h>
#include <map>

using namespace std;

void wlozBialy(int & p, int & k, map<int,int> & bialeKonce, int & s){
    int temp;
    map<int,int>::iterator it;
    it = bialeKonce.lower_bound(p);
    map<int,int>::iterator it2;
    while(it != bialeKonce.end() && it->second <= k){
        s -= (it->second - it->first + 1);
        bialeKonce.erase(it);
        it = bialeKonce.lower_bound(p);
    }
    it = bialeKonce.lower_bound(p);
    it2 = it;
    if(it != bialeKonce.begin()){
        it--;
        if(it->second < p ){
            if(it2 == bialeKonce.end()){
                s += (k-p+1);
                bialeKonce.insert(pair<int,int> (p,k));
            }else{
                if(it2->first > k){
                    s += (k-p+1);
                    bialeKonce.insert(pair<int,int> (p,k));
                }else{
                    temp = it2->second;
                    s -= (it2->second-it2->first+1);
                    bialeKonce.erase(it2);
                    s += (temp-p+1);
                    bialeKonce.insert(pair<int,int> (p,temp));
                }
            }
        }else{
            if(it->second < k){
                if(it2 == bialeKonce.end()){
                    temp = it->first;
                    s -= (it->second-it->first+1);
                    bialeKonce.erase(it);
                    s += (k-temp+1);
                    bialeKonce.insert(pair<int,int> (temp,k));
                }else{
                    if(it2->first > k){
                        temp = it->first;
                        s -= (it->second-it->first+1);
                        bialeKonce.erase(it);
                        s += (k-temp+1);
                        bialeKonce.insert(pair<int,int> (temp,k));
                    }else{
                        temp = it->first;
                        int temp2= it2->second;
                        s -= (it->second-it->first+1);
                        bialeKonce.erase(it);
                        s -= (it2->second-it2->first+1);
                        bialeKonce.erase(it2);
                        s += (temp2-temp+1);
                        bialeKonce.insert(pair<int,int> (temp,temp2));
                    }
                }
            }
        }
    }else{
        if(it2 == bialeKonce.end()){
            s += (k-p+1);
            bialeKonce.insert(pair<int,int> (p,k));
        }else{
            if(it2->first > k){
                s += (k-p+1);
                bialeKonce.insert(pair<int,int> (p,k));
            }else{
                temp = it2->second;
                s -= (it2->second-it2->first+1);
                bialeKonce.erase(it2);
                s += (temp-p+1);
                bialeKonce.insert(pair<int,int> (p,temp));
            }
        }
    }
    printf("%d\n",s);
}

void wlozCzarny(int & p, int & k, map<int,int> & bialeKonce, int & s){
    int temp;
    map<int,int>::iterator it;
    it = bialeKonce.lower_bound(p);
    map<int,int>::iterator it2;
    while(it != bialeKonce.end() && it->second <= k){
        s -= (it->second-it->first+1);
        bialeKonce.erase(it);
        it = bialeKonce.lower_bound(p);
    }
    it = bialeKonce.lower_bound(p);
    it2 = it;
    if(it != bialeKonce.begin()){
        it--;
        if(it->second < p ){
            if(it2!=bialeKonce.end()){
                if(it2->first <= k){
                    temp = it2->second;
                    s -= (it2->second-it2->first+1);
                    bialeKonce.erase(it2);
                    s += (temp-(k+1)+1);
                    bialeKonce.insert(pair<int,int> (k+1,temp));
                }
            }
        }else{
            if(it->second < k){
                if(it2 == bialeKonce.end()){
                    temp = it->first;
                    s -= (it->second-it->first+1);
                    bialeKonce.erase(it);
                    s += ((p-1)-temp+1);
                    bialeKonce.insert(pair<int,int> (temp,p-1));
                }else{
                    if(it2->first > k){
                        temp = it->first;
                        s -= (it->second-it->first+1);
                        bialeKonce.erase(it);
                        s += ((p-1)-temp+1);
                        bialeKonce.insert(pair<int,int> (temp,p-1));
                    }else{
                        temp = it->first;
                        int temp2 = it2->second;
                        s -= (it->second-it->first+1);
                        bialeKonce.erase(it);
                        s -= (it2->second-it2->first+1);
                        bialeKonce.erase(it2);
                        s += (temp2-(k+1)+1);
                        bialeKonce.insert(pair<int,int> (k+1,temp2));
                        s += ((p-1)-temp+1);
                        bialeKonce.insert(pair<int,int> (temp,p-1));
                    }
                }
            }else{
                temp = it->first;
                int temp2 = it->second;
                s -= (it->second-it->first+1);
                bialeKonce.erase(it);
                if(temp2 != k){
                    s += (temp2-(k+1)+1);
                    bialeKonce.insert(pair<int,int> (k+1,temp2));
                }
                s += ((p-1)-temp+1);
                bialeKonce.insert(pair<int,int> (temp,p-1));
            }
        }
    }else{
        if(it2!=bialeKonce.end()){
            if(it2->first <= k){
                temp = it2->second;
                s -= (it2->second-it2->first+1);
                bialeKonce.erase(it2);
                s += (temp-(k+1)+1);
                bialeKonce.insert(pair<int,int> (k+1,temp));
            }
        }
    }
    printf("%d\n",s);
}

int main (){

  int n;
  scanf( "%d", &n );
  int m;
  scanf( "%d", &m );
  int p, k;
  char rodzaj[1];
  map<int,int> bialeKonce;

  int s = 0;
  for( int i = 0; i < m; i++ ){
    scanf( "%d %d %1s", &p, &k, &rodzaj[0]);
    if (rodzaj[0] == 'B'){
      wlozBialy(p,k,bialeKonce,s);
    }else{
      wlozCzarny(p,k,bialeKonce,s);
    }
    //ileJestBialego(bialeKonce);
  }
  return 0;
}
