#include <stdio.h>
#include <math.h>

int main(){
	/* int n, i, j;
	scanf("%d", &n);
	for (i = n-1; abs(i) < n; i--){
		for (j = 0; j < n - abs(i); j++)
			printf("*");
	printf("\n");
	}*/
	
	int i, j;	
	for (i=8; i>=0; i--){
		for (j=4; j>=abs(4-i);j--)
			printf("%d", j);
		printf("\n");
	}

	return 0;
}
