#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct test_t {
	uint32_t c;
	uint8_t a;
	uint8_t b;
} test_t;

int main(){
	printf("%d", sizeof(test_t));
	return 0;
}
