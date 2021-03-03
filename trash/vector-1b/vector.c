#include "vector.h"

vector_t *vector_init(u32 size, u32 capacity){
	vector_t *new_vector = (vector_t*)malloc(sizeof(vector_t));
	
	new_vector->slave = NULL;
	new_vector->stride = size;
	new_vector->start = malloc(stride * capacity);
	new_vector->capacity = new_vector->start + (size * capacity);
	new_vector->end = new_vector->start;
	
	return new_vector;
}

/* void *vector_init(...); */

void *vector_destroy(vector_t *self);

u32 vector_capacity(const vector_t *self){ return (self->capacity - self->start) / self->stride; }

u32 vector_length(const vector_t *self){ return (self->end - self->start) / self->stride; }

u32 vector_size(const vector_t *self){ return vector_length(self); }

vector_t *vector_move(vector_t *self){
	/* 
	** böyle bir fonksiyonun nerde kullanilacagini hic bilmiyorum 
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
	self->stride			= NULL	;
	self->slave				= NULL	;
	self->start				= NULL	;
	self->end				= NULL	;
	
	return new_vector;
}

vector_t *vector_copy(const vector_t *self){
	vector_t *new_vector = vector_init( self->stride, vector_capacity(self) );
	memcpy( new_vector->start, self->start, (self->end - self->start) );
	return new_vector;
}

const vector_t *vector_copy_ro(vector_t *self){
	vector_t *target, *new_vector = (vector_t*)malloc(sizeof(vector_t));

	/* eskidekileri yenisine tasi */
	new_vector->stride		= NULL			 ;
	new_vector->capacity	= self->capacity ;
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
		head = head->next;
		free(tmp);
	}
}

u8 vector_extend_capacity(vector_t *self){
	u32 length = vector_length(self), new_capacity = 2 * (self->capacity - self->start);
	/* exception handling */
	if ((void* tmp = realloc(self->start, new_capacity) == NULL) { return 0; }
	
	self->start		= tmp;
	self->capacity	= self->start + new_capacity;
	self->end 		= self->start + length;
	
	return 1;
}

u8 vector_push_back(vector_t *self, void *data){
#ifdef _DEBUG
	if (self->end < data && data < (self->end + self->stride)) return 0;
#endif
	if (self->end == self->capacity){
		if (vector_extend_capacity(self) == 0)
			return 0;
	}
	
	memcpy(self->end, data, self->stride);
	self->end += self->stride;
	
}

u8 vector_append(vector_t *self, void *data);





























