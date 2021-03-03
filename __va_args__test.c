#include <stdio.h>
#include <stdlib.h>

#define stringinize_m(...) \
	printf(#__VA_ARGS__)

#define call_attr_m(object, func, ...) \
	(*object->func)((object), ##__VA_ARGS__)
	
typedef struct person_t{
	unsigned int age;
	void (*foo)(struct person_t*);
	struct person_t* (*init)(unsigned int);
} person_t;

void person_foo(person_t* self){
	printf("%d\n", self->age);
}

person_t* person_init(unsigned int age){
	person_t* new_person = (person_t*)malloc(sizeof(person_t));
	new_person->init = &person_init;
	new_person->foo = &person_foo;
	new_person->age = age;
	
	return new_person;
}

int main(){
	person_t* tuna = person_init(16);
	(*tuna->foo)(tuna);
	call_attr_m(tuna, foo);
	
	return 0;
}
