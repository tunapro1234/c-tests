#include <stdio.h>

#define test1()		\
	printf("1");    \
#ifdef TEST			\
	printf("2");	\
#endif				\
    printf("3")		\
    
vector_t(int);

int main(){
	test1();
	return 0;
}
