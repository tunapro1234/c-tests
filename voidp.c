#include <stdlib.h>

typedef struct test_t {
	void *start, *end;
} test_t;

unsigned int test_length(test_t* self){ return self->end - self->start; }

int main(){
	int a[10];
	test_t b = {.start = &a, .end = &a[9]};
	printf("%d\n", b.start + 10);
	return 0;
}
