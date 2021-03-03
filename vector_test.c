typedef signed char           s8;
typedef char                  u8;
typedef short                 s16;
typedef unsigned short        u16;
typedef int                   s32;
typedef unsigned int          u32;
/* typedef long long             s64;
** typedef unsigned long long    u64; */
typedef enum { False=0, True } bool;

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////

/*
** vector_t içinde bulunan slaves degiskeni vector_copy_ro ile üretilen
** vectorlerin yerlerini tutacak çok sağlıklı degil ozellikle yer acisindan
** 
** ama linked list tarzinda yapmayi dusunuyorum
*/

typedef struct vector_t {
	void *start, *end, *capacity;
	u32 stride;
	struct vector_t *slave;
} vector_t;

vector_t *vector_init(u32 size, u32 capacity);

/* Bunu yapabilirsem �ok inanilmaz olur */
/* void *vector_init(...); */

void *vector_destroy(vector_t *self);

u32 vector_capacity(const vector_t *self);
u32 vector_length(const vector_t *self);

vector_t *vector_move(vector_t *self);
vector_t *vector_copy(const vector_t *self);
const vector_t *vector_copy_ro(vector_t *self);
void vector_free_slaves(vector_t *self);

bool vector_extend_capacity(vector_t *self);
bool vector_push_back(vector_t *self, void *data);

void* vector_get(vector_t *self, s32 index);

/////////////////////////////////////////////////////////////////

vector_t *vector_init(u32 size, u32 capacity){
	vector_t *new_vector = (vector_t*)malloc(sizeof(vector_t));
	
	new_vector->slave 	 = NULL;
	new_vector->stride 	 = size;
	new_vector->start 	 = malloc(size * capacity);
	new_vector->capacity = (char*)new_vector->start + (size * capacity);
	new_vector->end		 = new_vector->start;
	
	return new_vector;
}

/* void *vector_init(...); */

void *vector_destroy(vector_t *self);

u32 vector_capacity(const vector_t *self){ return ((char*)self->capacity - (char*)self->start) / self->stride; }

u32 vector_length(const vector_t *self){ return ((char*)self->end - (char*)self->start) / self->stride; }

u32 vector_size(const vector_t *self){ return vector_length(self); }

vector_t *vector_move(vector_t *self){
	/* 
	** b�yle bir fonksiyonun nerde kullanilacagini hic bilmiyorum 
	** asiri gereksiz geldi 
	*/
	vector_t *new_vector = (vector_t*)malloc(sizeof(vector_t));
	
	/* eskidekileri yenisine tasi */
	new_vector->capacity	= self->capacity ;
	new_vector->stride		= self->stride	 ;
	new_vector->slave		= self->slave	 ;
	new_vector->start		= self->start	 ;
	new_vector->end			= self->end		 ;

	/* eskisini oldur */
	self->capacity			= NULL	;
	self->slave				= NULL	;
	self->start				= NULL	;
	self->end				= NULL	;
	
	return new_vector;
}

vector_t *vector_copy(const vector_t *self){
	vector_t *new_vector = vector_init( self->stride, vector_capacity(self) );
	memcpy(new_vector->start, self->start, ((char*)self->end - (char*)self->start));
	return new_vector;
}

const vector_t *vector_copy_ro(vector_t *self){
	vector_t *target, *new_vector = (vector_t*)malloc(sizeof(vector_t));

	/* eskidekileri yenisine tasi */
	new_vector->capacity	= self->capacity ;
	new_vector->stride		= self->stride	 ;
	new_vector->slave		= self->slave	 ;
	new_vector->start		= self->start	 ;
	new_vector->end			= self->end		 ;
	
	/* kolelere ekleniyor */
	while (target->slave != NULL)
		target = target->slave;
	target->slave = new_vector;
	
	return new_vector;
}

void vector_free_slaves(vector_t *head){
	/* verilen ilk vektorden baslayarak temizliyor */
	vector_t* tmp;
	while (head != NULL) {
		tmp = head;
		head = head->slave;
		free(tmp);
	}
}

bool vector_extend_capacity(vector_t *self){
	u32 length = vector_length(self), new_capacity = 2 * ((char*)self->capacity - (char*)self->start);
	// printf("New Capacity: %u\n", new_capacity/self->stride);
	
	/* exception handling */
	void *tmp = realloc(self->start, new_capacity);
	if (tmp == NULL) return False;
	
	self->start		= tmp;
	self->capacity	= (char*)self->start + new_capacity;
	self->end 		= (char*)self->start + length;
	
	return True;
}

bool vector_push_back(vector_t *self, void *data){
#ifdef _DEBUG
	/* bize verilen datanin bizim yazicagimiz yerle ayni olmamasi gerekiyor*/
	if (self->end < data && data < ((char*)self->end + self->stride)) return False;
#endif
	if (self->end == self->capacity){
		if (vector_extend_capacity(self) == False)
			return False;
	}
	
	memcpy(self->end, data, self->stride);
	self->end = (char*)self->end + self->stride;
	return True;
}

void* vector_get(vector_t *self, s32 index){ return (char*)self->start + (index * self->stride); }

////////////////////////////////////////////////////////////////

/*
** basit bir vector implementasyonu olmasini hedefliyorum
** cook basit
** 
** 
** 
*/

int main() {
	vector_t *v1 = vector_init(sizeof(s32), 10);
	
	printf("len: %d cap: %d\n", vector_length(v1), vector_capacity(v1));
	for (int i = 0; i < 2*vector_capacity(v1); i++)
		vector_push_back(v1, &(s32){1234});
	
	// u32 new_capacity = 2*((char*)v1->capacity - (char*)v1->start);
	// printf("new_cap: %d\n", new_capacity/sizeof(int));

	// vector_push_back(v1, &(s32){10});
	printf("len: %d cap: %d\n", vector_length(v1), vector_capacity(v1));
	for (int i = 0; i < vector_length(v1); i++)
		printf("%d ", *(int*)vector_get(v1, i));
		
	return 0;
}

