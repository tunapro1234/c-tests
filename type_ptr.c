#include <stdlib.h>
#include <stdio.h>

typedef struct test_t {
	int *a;
} test_t;

typedef struct test_ro_t {
	const int *a;
} test_ro_t;

test_t* init() {
	test_t *new_element = (test_t *)malloc(sizeof(*new_element));
	new_element->a = (int *)malloc(sizeof(int));
	*new_element->a = 20;
	return new_element;
}

int read(const test_ro_t *self){
	return *self->a;
}

int main() {
	int a[] = {1, 2, 3, 4, 5};
	printf("%p %p %d %d\n", a, &a[4], &a[4] - a, (char *)&a[4] - (char *)a);
	
	test_ro_t *b = (test_ro_t*)init();
	test_t *c = init();
	
	printf("%d, %d", read(b), read(c));
	
	return 0;
}
