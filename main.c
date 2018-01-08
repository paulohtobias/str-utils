#include "str-utils.h"

#define t 5

int main(){
	char *s1, *s2;
	int i, j, r;
	char nomes[t][30] = {
		"foo1bla2",
		"foo01bla2",
		"foo1bla02",
		"foo1bla10",
		"foo01bla10",
	};
	
    for(i = 0; i < t; i++){
		s1 = nomes[i];
		for(j = 0; j < t; j++){
			s2 = nomes[j];
			r = strcmpn(s1, s2);
			if(r < 0){
				printf("%s < %s\n", s1, s2);
			}else if(r == 0){
				printf("%s == %s\n", s1, s2);
			}else{
				printf("%s > %s\n", s1, s2);
			}
		}
		getchar();
    }
	return 0;
}