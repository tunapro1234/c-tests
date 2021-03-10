#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void test(int first_arg, ...) {
	va_list args;
	va_start(args, first_arg);
	
	for (int i = 0; i < first_arg; i++)
		printf("%s", va_arg(args, char*));
	
	va_end(args);
}

int main() {
	test(2, "deneme\n", "deneme2");
	
	return 0;
}

