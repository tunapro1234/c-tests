#include "main.h"
#include "vector-1.h"

typedef enum max_output_t {
	MO_FIRST_ARG,
	MO_ARGS_EQUAL,
	MO_SECOND_ARG,
} max_output_t;

max_output_t s32_max_func(s32* a, s32* b) {
	if (*a > *b) 		return MO_FIRST_ARG ;
	else if (*a == *b) 	return MO_ARGS_EQUAL;
	else 				return MO_SECOND_ARG;
}


#define create_merge_sort(TYPE, NAME) \
	void __inter_##NAME##_merge_sort(NAME *self, size_t arr_start, size_t arr_length, max_output_t (*max_func)(TYPE*, TYPE*)) {	\
		size_t i = 0, li = 0, ri = 0, mid_point = 0; 	\
		TYPE *left_temp, *right_temp; 					\
		max_output_t rv; 								\
		\
		if (arr_start == arr_length-1) return;	 /* 1 eleman kalinca bitir */ 	\
		mid_point = arr_start + (arr_length - arr_start) / 2; /* l+(r-l)/2 */ 	\
		\
		__inter_##NAME##_merge_sort(self, arr_start, mid_point , max_func); 	\
		__inter_##NAME##_merge_sort(self, mid_point, arr_length, max_func); 	\
		\
		left_temp  = (TYPE *)malloc(sizeof(TYPE) * (mid_point - arr_start )); 	\
		right_temp = (TYPE *)malloc(sizeof(TYPE) * (arr_length - mid_point)); 	\
		\
		memcpy(left_temp,  self->_start + arr_start, sizeof(TYPE) * (mid_point  - arr_start)); 	\
		memcpy(right_temp, self->_start + mid_point, sizeof(TYPE) * (arr_length - mid_point)); 	\
		\
		for (i = arr_start; li < (mid_point - arr_start) && ri < (arr_length - mid_point);) { 	\
			rv = max_func(&left_temp[li], &right_temp[ri]); \
			if (rv == MO_FIRST_ARG) { 						\
				*NAME##_get(self, i) = right_temp[ri]; 		\
				ri++; i++; 									\
			} else if (rv == MO_ARGS_EQUAL) { 				\
				*NAME##_get(self, i) = left_temp[li]; 		\
				li++; i++; 									\
				*NAME##_get(self, i) = right_temp[ri]; 		\
				ri++; i++; 									\
			} else { 										\
				*NAME##_get(self, i) = left_temp[li]; 		\
				li++; i++; 									\
			} 	\
		}	\
		\
		while (li < (mid_point  - arr_start)) { *NAME##_get(self, i) = left_temp[li]; li++; i++; } 	\
		while (ri < (arr_length - mid_point)) { *NAME##_get(self, i) = right_temp[ri]; ri++; i++; } 	\
		free(left_temp); free(right_temp); 												\
	} 	\
	void NAME##_merge_sort(NAME *self, max_output_t (*max_func)(TYPE*, TYPE*)) {	\
		__inter_##NAME##_merge_sort(self, 0, NAME##_length(self), max_func);		\
	} struct __internal_semicolon

create_vector_t(int, vector_int_t);
create_merge_sort(int, vector_int_t);

int main(){
#define LEN 10
	size_t i = 0;
	vector_int_t *a = vector_int_t_init_h(LEN);
	for (i = 0; i < LEN; i++) {
		vector_int_t_push_back(a, LEN-i);
		printf("%d ", vector_int_t_read(a, i));
	}
	
	// __inter_vector_int_t_merge_sort(a, 0, LEN, s32_max_func);
	vector_int_t_merge_sort(a, s32_max_func);
	printf("\n");
	for (i = 0; i < LEN; i++) 
		printf("%d ", vector_int_t_read(a, i));

	return 0;
}
