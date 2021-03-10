#include <stdio.h>

int main(){
	const int *ptr1;
	int sayi1 = 5;
	const int sayi2 = 10;
	
	/* ptr1 isaretcisi sabit bir tamsayiya isaret etmelidir. Dolayisiyla asagidaki satir hatalidir. */
	ptr1 = &sayi1; /* Hata */
	
	/* Asagidaki satirdaki kullanim dogrudur. Cunku hem ptr1 hem de sayi2 const olarak tanimlanmistir. */
	int ptr = &sayi2;
	
	return 0;
}
