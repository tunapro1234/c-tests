#include "main.h"

u32 search_binary(s32 target, s32 *array, u32 array_start_index, u32 array_length){
	u32 mid_point = array_length-1;
	
	mid_point = (int)((array_start_index + mid_point) / 2);
	
	if (array[mid_point] == target)
		return mid_point;
	else if (mid_point == 0 || mid_point == array_length-1)
		return -1;
	else if (target < array[mid_point])
		return search_binary(target, array, array_start_index, mid_point);
	else if (array[mid_point] < target)
		return search_binary(target, array, mid_point+1, array_length);
}

int main(){
	s32 a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	s32 input; printf(">>> "); scanf("%d", &input);
	
	printf("%d", search_binary(input, a, 0, 10));
	return 0;
}

