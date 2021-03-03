#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person_t{
	char* name;
	unsigned int age;
} person_t;

person_t _default_person = {
	.name = "tunapro1234",
	.age = 16
};

void person_change_name(person_t *self, char *new_name){
	self->name = (char*)malloc(strlen(new_name) + 1);
	strcpy(self->name, new_name);
}

person_t* person_init(char *name, int age){
	person_t *new_person = (person_t*)malloc(sizeof(person_t));
	person_change_name(new_person, name);
	new_person->age = age;
	
	return new_person;
}

person_t* person_copy(person_t* self) {
	return person_init(self->name, self->age);
}

person_t* person_move(person_t* self) {
	person_t *new_person = (person_t*)malloc(sizeof(person_t));
	new_person->name = self->name;
	new_person->age = self->age;
	
	self->name = NULL;
	self->age = 0;
	
	return new_person;
}

int main(){
	person_t mali = *person_init("mali", 16);
	
	person_t tuna = *person_copy(&mali);
	person_change_name(&tuna, "tunapro");
	
	mali = *person_move(&tuna);
	printf("%s %d\n", mali.name, mali.age);
	printf("%s %d\n", tuna.name, tuna.age);
	
	return 0;
}
