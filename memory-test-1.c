#include <stdio.h>

int main(){
	unsigned int a[10], i;
	for (i = 1; i <= 10; i++){
		printf("%u ", i);
		a[i] = 0;
	}
	
	return 0;
}
