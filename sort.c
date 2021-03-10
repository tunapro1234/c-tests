#include <string.h>

#include "main.h"
/*
void s32_arr_swap(s32 *arr, size_t index1, size_t index2) {
    s32 temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

 
void s32_arr_bubble_sort(s32 *arr, s32* (*key_func)(s32*, s32*)) {
	size_t i, j, last_index = vector_int_length(arr)-1;
	for (i = 0; i < last_index; i++)
		for (j = 0; j < last_index-i; j++)
			if ( arr[j] == key_func(arr[j], arr[j+1]) )
				s32_arr_swap(arr, j, j+1);
} 
*/

typedef enum max_output_t {
	MO_FIRST_ARG,
	MO_ARGS_EQUAL,
	MO_SECOND_ARG,
} max_output_t;

max_output_t s32_bigger(s32 *a, s32 *b) {
	if (*a > *b)	 	return MO_FIRST_ARG;
	else if (*a == *b) 	return MO_ARGS_EQUAL;
	else				return MO_SECOND_ARG;
}

void s32_arr_merge_sort(s32 *arr, size_t array_start_index, size_t array_length, max_output_t (*max_func)(s32*, s32*)) {
	size_t mid_point, i, li, ri;
	s32 *l_tmp_arr, *r_tmp_arr;

	/* l == r-1 (1 eleman kaldıysa) */
	if (array_start_index == array_length-1) return; 
	
#define LTA_LEN (mid_point - array_start_index)
#define RTA_LEN (array_length - mid_point)
	
	l_tmp_arr = (s32 *)malloc(sizeof(s32) * LTA_LEN);
	r_tmp_arr = (s32 *)malloc(sizeof(s32) * RTA_LEN);

	mid_point = (int)(array_start_index + (array_length - array_start_index) / 2); /* l+(r-l)/2 */
	
	/* arrayin içindekiler kopyalanıyor */
	memcpy(l_tmp_arr, &arr[array_start_index], (LTA_LEN-1) * sizeof(s32));
	memcpy(r_tmp_arr, &arr[mid_point], 		  (RTA_LEN-1) * sizeof(s32));
	
	/* 
	for (li = 0; li < LTA_LEN; li++) { l_tmp_arr[li] = arr[array_start_index + li]; }
	for (ri = 0; ri < RTA_LEN; ri++) { 
		r_tmp_arr[ri] = arr[mid_point + ri]; 
	} */
	
	s32_arr_merge_sort(arr, array_start_index, mid_point, max_func);
	s32_arr_merge_sort(arr, mid_point, array_length, max_func);

	/* li -> temp left index, ri -> temp right index, i -> array index */
	for (li = 0, ri = 0, i = array_start_index; li < LTA_LEN && ri < RTA_LEN;) {
		/* sağ arraydeki son eleman daha küçükse */
		// if (tmp_arr[i] > tmp_arr[j]) {
		if (MO_FIRST_ARG == max_func(&l_tmp_arr[li], &r_tmp_arr[ri])) {
			arr[i] = r_tmp_arr[ri]; ri++; i++;
		} /* else if (MO_ARGS_EQUAL == max_func(&tmp_arr[i], &tmp_arr[j])) {
			arr[k] = tmp_arr[i]; i++; k++;
			arr[k] = tmp_arr[j]; j++; k++;
		} */ else {
			arr[i] = l_tmp_arr[li]; li++; i++;
		}
	}
	while (li < LTA_LEN) { arr[i] = l_tmp_arr[li]; li++; i++; } 
	while (ri < RTA_LEN) { arr[i] = r_tmp_arr[ri]; ri++; i++; }
	free(l_tmp_arr); free(r_tmp_arr);
}

int main() {
	s32 a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	size_t len = sizeof(a) / sizeof(int), i;

	s32_arr_merge_sort(a, 0, len, s32_bigger);
	
	for (i = 0; i < len; i++) printf("%d ", a[i]);
	return 0;
}