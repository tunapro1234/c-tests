#include "main.h"

size_t search_linear(s32 target, s32 *array, size_t array_start_index, size_t array_length){
	size_t i;
	for (i = array_start_index; i < array_length; i++)
		if (array[i] == target) { return i; }
	return -1;
}

size_t search_binary(s32 target, s32 *array, size_t array_start_index, size_t array_length){
	/* size_t mid_point = (int)((array_start_index + array_length-1) / 2); */ /* (r+l)/2 */
	size_t mid_point = (int)(array_start_index + (array_length - array_start_index) / 2); /* l+(r-l)/2 */
	
	if (array[mid_point] == target)
		return mid_point;
	else if (array_start_index == array_length-1)
		return -1;
	else if (target < array[mid_point])
		return search_binary(target, array, array_start_index, mid_point);
	else if (array[mid_point] < target)
		return search_binary(target, array, mid_point+1, array_length);
}

int main(){
	s32 a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	s32 input; printf(">>> "); scanf("%d", &input);
	
	printf("%d\n", search_binary(input, a, 0, 10));
	printf("%d\n", search_linear(input, a, 0, 10));
	return 0;
}

