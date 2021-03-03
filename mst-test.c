typedef enum {
	MST_INT,
	MST_FLOAT,
	MST_COUNT
} my_struct_type_t;

typedef struct my_header_t{
	char name[32]
	my_struct_type_t type;
} my_header_t;

typedef struct my_struct_int_t{
	my_header_t head;
	int value;
} my_struct_int_t;

typedef struct my_struct_float_t{
	my_header_t head;
	float value;
} my_struct_float_t;

/*
** my_struct_float_t* ve my_struct_int_t*, my_header* yerine verilebiliyor
** müthis
*/

void my_set_value(my_header_t *h, double value){
	if (h->type == MST_INT)
		((my_struct_int_t *)h)->value = (int)value;
	else
		((my_struct_float_t *)h)->value = (float)value;
}

