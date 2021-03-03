#include "main.h"

u32 search_linear(s32 target, s32 *array, u32 array_start_index, u32 array_length){
	for (int i = array_start_index; i < array_length; i++)
		if (array[i] == target) { return i; }
	return -1;
}

u32 search_binary(s32 target, s32 *array, u32 array_start_index, u32 array_length){
	u32 mid_point = (int)((array_start_index + array_length-1) / 2);
	
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

