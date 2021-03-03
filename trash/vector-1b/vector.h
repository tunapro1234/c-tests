#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include "main.h"

/*
** vector_t içinde bulunan slaves degiskeni vector_copy_ro ile üretilen
** vectorlerin yerlerini tutacak çok saðlýklý degil ozellikle yer acisindan
** 
** ama linked list tarzinda yapmayi dusunuyorum
*/

typedef struct vector_t {
	void *start, *end, *capacity;
	u32 stride;
	struct vector_t *slave;
} vector_t;

vector_t *vector_init(u32 size, u32 capacity);

/* Bunu yapabilirsem çok inanilmaz olur */
/* void *vector_init(...); */

void *vector_destroy(vector_t *self);

u32 vector_capacity(const vector_t *self);
u32 vector_length(const vector_t *self);

vector_t *vector_move(vector_t *self);
vector_t *vector_copy(const vector_t *self);
const vector_t *vector_copy_ro(vector_t *self);
void vector_free_slaves(vector_t *self);

u8 vector_extend_capacity(vector_t *self);
u8 vector_push_back(vector_t *self, void *data);
u8 vector_append(vector_t *self, void *data);


#endif
