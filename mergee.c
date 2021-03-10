#include "main.h"

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


void merge_sort(s32 *arr, size_t arr_start, size_t arr_length, max_output_t (*max_func)(s32*, s32*)) {
	size_t i = 0, li = 0, ri = 0, mid_point = 0;
	s32 *left_temp, *right_temp;
	max_output_t rv;
	
	if (arr_start == arr_length-1) return;	 /* 1 eleman kalinca bitir */
	mid_point = arr_start + (arr_length - arr_start) / 2; /* l+(r-l)/2 */

	merge_sort(arr, arr_start, mid_point , max_func);
	merge_sort(arr, mid_point, arr_length, max_func);

	left_temp = (s32 *)malloc(sizeof(s32) * (mid_point - arr_start));
	right_temp = (s32 *)malloc(sizeof(s32) * (arr_length - mid_point));
	
	memcpy(left_temp, arr + arr_start , sizeof(s32) * (mid_point  - arr_start));
	memcpy(right_temp, arr + mid_point, sizeof(s32) * (arr_length - mid_point));

	for (i = arr_start; li < (mid_point - arr_start) && ri < (arr_length - mid_point);) {
		rv = max_func(&left_temp[li], &right_temp[ri]);
		if (rv == MO_FIRST_ARG) {
			arr[i] = right_temp[ri];
			ri++; i++;
		} else if (rv == MO_ARGS_EQUAL) {
			arr[i] = left_temp[li];
			li++; i++;
			arr[i] = right_temp[ri];
			ri++; i++;
		} else {
			arr[i] = left_temp[li];
			li++; i++;
		} 		
	}
	
	while (li < (mid_point - arr_start))  { arr[i] = left_temp[li]; li++; i++; }
	while (ri < (arr_length - mid_point)) { arr[i] = right_temp[ri]; ri++; i++; }
	free(left_temp); free(right_temp);
}

int main(){
#define LEN 10
	size_t i = 0;
	int a[LEN];
	for (i = 0; i < LEN; i++) {
		a[i] = LEN-i; 
		printf("%d ", a[i]);
	}
	
	merge_sort(a, 0, LEN, s32_max_func);
	printf("\n");
	for (i = 0; i < LEN; i++) 
		printf("%d ", a[i]);

	return 0;
}
