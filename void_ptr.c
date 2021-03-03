#include <stdlib.h>

int main(){
	int a[] = {1, 2, 3, 4};
	void *p = a;
	
	printf("%d\n", *(p+8));
	return 0;
}
