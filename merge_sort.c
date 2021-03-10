#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void merge_sort(int *arr, size_t array_start_index, size_t array_length) {
	size_t i = 0, li = 0, ri = 0, mid_point = 0;
	int *lta_temp, *rta_temp;
	
	/* 1 eleman kalinca bitir */
	if (array_start_index == array_length-1) return;
	
	/* l+(r-l)/2 */
	mid_point = array_start_index + (array_length - array_start_index) / 2;

	merge_sort(arr, array_start_index, mid_point);
	merge_sort(arr, mid_point, array_length);

#define LTA_LEN (mid_point - array_start_index)	
#define RTA_LEN (array_length - mid_point)
	
	lta_temp = (int *)malloc(sizeof(int) * LTA_LEN);
	rta_temp = (int *)malloc(sizeof(int) * RTA_LEN);
	
	memcpy(lta_temp, arr + array_start_index, sizeof(int) * LTA_LEN);
	memcpy(rta_temp, arr + mid_point		, sizeof(int) * RTA_LEN);

	for (i = array_start_index; li < LTA_LEN && ri < RTA_LEN;) {
		if (lta_temp[li] > rta_temp[ri]) {
			arr[i] = rta_temp[ri];
			ri++; i++;
		} else {
			arr[i] = lta_temp[li];
			li++; i++;
		} 		
	}
	
	while (li < LTA_LEN) { arr[i] = lta_temp[li]; li++; i++; }
	while (ri < RTA_LEN) { arr[i] = rta_temp[ri]; ri++; i++; }
	
	free(lta_temp);
	free(rta_temp);
	printf("\nok");
}

int main(){
#define LEN 10
	size_t i = 0;
	int a[LEN];
	for (i = 0; i < LEN; i++) {
		a[i] = LEN-i; 
		printf("%d ", a[i]);
	}
	
	merge_sort(a, 0, LEN);
	printf("\n");
	for (i = 0; i < LEN; i++) 
		printf("%d ", a[i]);

	return 0;
}
