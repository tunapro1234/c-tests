#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "main.h"

/*
 * NAME* NAME##_init_h(size_t capacity);
 *	heapte vector oluşturur 
 *
 * NAME NAME##_init(size_t capacity);
 * 	3 pointer kopyalasak nolur sanki
 * 
 * void NAME##_destroy(NAME *self);
 * 	free(self->_start); obje heapte oluştuturldaysa ayrıca temizlenmesi gerekiyor
 * 
 * size_t NAME##_capacity(const NAME *self);
 * 	vektörün kapasitesinin kaç elemanlık olduğu
 * 
 * size_t NAME##_length(const NAME *self);
 * 	vektörün içinde kaç eleman olduğu
 * 
 * size_t NAME##_size(const NAME *self);
 * 	vektörün içinde kaç eleman olduğu ama daha seksi
 * 
 * NAME* NAME##_move_h(NAME *self);
 * 	vektörü heape taşır (eski vektör yok ediliyor)
 * 
 * NAME NAME##_move(NAME *self);
 * 	vektörü stacka taşır gibi bir şey
 * 
 * NAME* NAME##_copy_h(const NAME *self);
 * 	vektörü kopyalar, yeni kopya heapte
 * 
 * NAME NAME##_copy(const NAME *self);
 * 	vektörü kopyalar
 * 
 * bool NAME##_extend_capacity(NAME *self);
 * 	vektörün kapasitesini realloc yarıdımıyla 2 katına çıkarır
 * 
 * bool NAME##_push_back(NAME *self, TYPE data);
 * 	vektörün sonuna eleman ekler
 * 
 * bool NAME##_push_back_p(NAME *self, TYPE *data);
 * 	vektörün sonuna eleman ekler, pointer alıyor
 * 
 * TYPE *NAME##_get(NAME *self, size_t index);
 * 	vektörün indexinci elemanının pointerını döndürür
 * 
 * TYPE NAME##_read(const NAME *self, size_t index);
 * 	vektörün indexinci elemanının değerini döndürür
 * 
 * 
 * void NAME##_bubble_sort(NAME *self, TYPE* (*key_func)(TYPE*, TYPE*));
 * 	elemanları bubble sort algoritması ile sırala (büyük olan elemanı belirlemek için fonksiyon pointerı alıyor)
 * 
 * void NAME##_swap(NAME *self, size_t index1, size_t index2);
 * 	iki indeksteki elemanları değiştirir
 * 
 * bool NAME##_insert_p(NAME *self, size_t index, TYPE *value);
 * 	verilen adresteki datayı verilen indekse kopyalar
 * 
 * bool NAME##_insert(NAME *self, size_t index, TYPE value);
 * 	verilen datayı indekse kopyalar
 * 
 * void NAME##_shift_r(NAME *self);
 * 	vektörün elemanlarını sağa kaydırır (sonuncu eleman başa geliyor)
 * 
 * void NAME##_shift_l(NAME *self);
 * 	vektörün elemanlarını sola kaydırır (baştaki eleman sola geliyor)
 * 
 * void NAME##_reverse(NAME *self);
 * 	vektörü ters döndürür
 * 
*/


int* vector_int_sort_example(int *a, int *b) {
	return (*a > *b) ? a : b;
}

#define create_vector_t(TYPE, NAME)																							\
	typedef struct NAME{																							\
		TYPE *_start, *_end, *_capacity;																					\
	} NAME; 																										\
\
	NAME* NAME##_init_h(size_t capacity); 																\
	NAME NAME##_init(size_t capacity); 																	\
	void NAME##_destroy(NAME *self); 																		\
\
	size_t NAME##_capacity(const NAME *self); 															\
	size_t NAME##_length(const NAME *self); 																\
	size_t NAME##_size(const NAME *self); 																\
\
	NAME* NAME##_move_h(NAME *self); 															\
	NAME NAME##_move(NAME *self); 																\
	NAME* NAME##_copy_h(const NAME *self);														\
	NAME NAME##_copy(const NAME *self); 															\
\
	bool NAME##_extend_capacity(NAME *self); 																\
	bool NAME##_push_back(NAME *self, TYPE data); 														\
	bool NAME##_push_back_p(NAME *self, TYPE *data); 														\
\
	TYPE *NAME##_get(NAME *self, size_t index); 															\
	TYPE NAME##_read(const NAME *self, size_t index); 													\
\
\
	void NAME##_swap(NAME *self, size_t index1, size_t index2);											\
	bool NAME##_insert_p(NAME *self, size_t index, TYPE *value);											\
	bool NAME##_insert(NAME *self, size_t index, TYPE value);												\
\
	void NAME##_shift_r(NAME *self);																		\
	void NAME##_shift_l(NAME *self);																		\
	void NAME##_reverse(NAME *self);																		\
\
	void NAME##_bubble_sort(NAME *self, TYPE* (*key_func)(TYPE*, TYPE*));									\
\
/********************************************************************************/											\
\
	NAME* NAME##_init_h(size_t capacity) { 																\
		NAME *new_vector = (NAME *)malloc(sizeof(NAME)); 										\
		\
		new_vector->_start 		= (TYPE *)malloc(sizeof(TYPE) * capacity); 													\
		new_vector->_capacity	= new_vector->_start + capacity; 															\
		new_vector->_end			= new_vector->_start; 																	\
		return new_vector; 																									\
	}	\
\
	NAME NAME##_init(size_t capacity) { 																	\
		NAME new_vector; 																							\
		\
		new_vector._start 		= (TYPE *)malloc(sizeof(TYPE) * capacity); 													\
		new_vector._capacity		= new_vector._start + capacity; 														\
		new_vector._end			= new_vector._start; 																		\
		return new_vector; 																									\
	} 	\
\
	void NAME##_destroy(NAME *self) { 																	\
		free(self->_start); 																								\
	} 	\
\
	size_t NAME##_capacity(const NAME *self) { return self->_capacity - self->_start; } 					\
	size_t NAME##_length(const NAME *self) { return self->_end - self->_start; } 							\
	size_t NAME##_size(const NAME *self) { return self->_end - self->_start; } 							\
\
	NAME* NAME##_move_h(NAME *self) { 															\
		NAME *new_vector = (NAME *)malloc(sizeof(NAME)); 										\
		new_vector->_capacity = self->_capacity; 																			\
		new_vector->_start = self->_start; 																					\
		new_vector->_end = self->_end; 																						\
		self->_capacity = NULL; 																							\
		self->_start = NULL; 																								\
		self->_end = NULL; 																									\
		return new_vector; 																									\
	} 	\
\
	NAME NAME##_move(NAME *self) {																\
		NAME new_vector; 							 																\
		new_vector._capacity = self->_capacity; 			 																\
		new_vector._start = self->_start; 					  																\
		new_vector._end = self->_end; 						  																\
		self->_capacity = NULL; 							  																\
		self->_start = NULL; 								  																\
		self->_end = NULL; 									  																\
		return new_vector; 									  																\
	} 	\
\
	NAME* NAME##_copy_h(const NAME *self) { 														\
		size_t length = NAME##_length(self); 																		\
		NAME *new_vector = NAME##_init_h(NAME##_capacity(self)); 								\
		memcpy(new_vector->_start, self->_start, NAME##_capacity(self) * sizeof(TYPE)); 							\
		new_vector->_end = new_vector->_start + length; 																	\
		return new_vector; 																									\
	} 	\
\
	NAME NAME##_copy(const NAME *self) { 														\
		size_t length = NAME##_length(self); 																		\
		NAME new_vector = NAME##_init(NAME##_capacity(self)); 									\
		memcpy(new_vector._start, self->_start, NAME##_capacity(self) * sizeof(TYPE)); 							\
		new_vector._end = new_vector._start + length; 																		\
		return new_vector; 																									\
	} 	\
\
	bool NAME##_extend_capacity(NAME *self) { 															\
		size_t new_capacity = NAME##_capacity(self) * 2; 															\
		size_t length 		= NAME##_length(self); 																\
		\
		void *tmp = realloc(self->_start, new_capacity * sizeof(TYPE)); 													\
		if (tmp == NULL) return False; 																						\
		\
		self->_start 	= (TYPE *)tmp; 																						\
		self->_capacity 	= self->_start + new_capacity; 																	\
		self->_end 		= self->_start + length; 																			\
		return True; 																										\
	} 	\
\
	bool NAME##_push_back(NAME *self, TYPE data) { 														\
		if (self->_end == self->_capacity){ 																				\
			if (NAME##_extend_capacity(self) == False) 															\
				return False; 																								\
		} 																													\
		*self->_end = data; 																								\
		self->_end++; 																										\
		return True; 																										\
	} 	\
\
	bool NAME##_push_back_p(NAME *self, TYPE *data) { 													\
		if (self->_end == self->_capacity){ 																				\
			if (NAME##_extend_capacity(self) == False) 															\
				return False; 																								\
		} 																													\
		memcpy(self->_end, data, sizeof(TYPE)); 																			\
		self->_end++; 																										\
		return True; 																										\
	} 	\
\
	TYPE *NAME##_get(NAME *self, size_t index) { return self->_start + index; } 							\
	TYPE NAME##_read(const NAME *self, size_t index) { return *(self->_start + index); } 					\
\
\
	void NAME##_swap(NAME *self, size_t index1, size_t index2) {											\
		TYPE tmp = *NAME##_get(self, index1);																		\
		*NAME##_get(self, index1) = *NAME##_get(self, index2);											\
		*NAME##_get(self, index2) = tmp;																			\
	}	\
\
	bool NAME##_insert_p(NAME *self, size_t index, TYPE *value) {											\
		size_t i, length;																									\
		if (self->_end == self->_capacity)																					\
			if (NAME##_extend_capacity(self) == False)																\
				return False;																								\
		\
		length = NAME##_length(self);																				\
		for (i = length; i > index; i--)																					\
			*(self->_start + i) = *(self->_start + i - 1);																	\
		memcpy(NAME##_get(self, index), value, sizeof(TYPE));														\
		self->_end++;																										\
		return True;																										\
	}	\
\
	bool NAME##_insert(NAME *self, size_t index, TYPE value) {											\
		size_t i, length;																									\
		if (self->_end == self->_capacity)																					\
			if (NAME##_extend_capacity(self) == False)																\
				return False;																								\
		\
		length = NAME##_length(self);																				\
		for (i = length; i > index; i--)																					\
			*(self->_start + i) = *(self->_start + i - 1);																	\
		*NAME##_get(self, index) = value;																			\
		self->_end++;																										\
		return True;																										\
	}	\
\
	void NAME##_shift_r(NAME *self) {																		\
		size_t i, last_index = NAME##_length(self)-1;																\
		TYPE tmp = *NAME##_get(self, last_index);																	\
		for (i = last_index; i > 0; i--)																					\
			*NAME##_get(self, i) = *NAME##_get(self, i-1);												\
		*NAME##_get(self, 0) = tmp;																				\
	}	\
\
	void NAME##_shift_l(NAME *self) {																		\
		size_t i, length = NAME##_length(self);																	\
		TYPE tmp = *NAME##_get(self, 0);																			\
		for (i = 1; i < length; i++)																						\
			*NAME##_get(self, i-1) = *NAME##_get(self, i);												\
		*NAME##_get(self, length-1) = tmp;																			\
	}	\
\
	void NAME##_reverse(NAME *self) {																		\
		size_t i, length = NAME##_length(self);																	\
		for (i = 0; i < length/2; i++)																						\
			NAME##_swap(self, i, length-1-i);																		\
	}	\
\
	void NAME##_bubble_sort(NAME *self, TYPE* (*key_func)(TYPE*, TYPE*)){									\
	size_t i, j, last_index = NAME##_length(self)-1;																\
	for (i = 0; i < last_index; i++)																						\
		for (j = 0; j < last_index-i; j++)																					\
           	if ( NAME##_get(self, j) == key_func(NAME##_get(self, j), NAME##_get(self, j+1)) )	\
              	NAME##_swap(self, j, j+1);																			\
}	\
\
struct __internal_you_need_semicolon


#endif