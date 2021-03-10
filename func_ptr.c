#include <stdlib.h>
#include <stdio.h>

typedef struct test_t {
	void (*foo)();
} test_t;

test_t *test_init(void (*func)()){
	test_t* new_test = (test_t*)malloc(sizeof(test_t));
	new_test->foo = func;
	return new_test;
}

void test_foo(){
	printf("tunapro1234");
}

int main(){
	test_t* new_test = test_init(test_foo);
	printf("%p %p", new_test->foo, test_foo);
	new_test->foo();
	return 0;
}

