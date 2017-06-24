#include <cstdio>
#include <set>

using namespace std;

int n;
set<int> v;

int main()
{
	int i, w;
	int licznik = 0;
	scanf("%d\n", &n);
	for(int i=0; i <n; i++)
	{
		scanf("%d",&w);
		if(v.count(w)){
			licznik++;
			v.clear();
		}else{
			v.insert(w);
		}
	}
		
	printf("%d\n", licznik);
	return 0;
}