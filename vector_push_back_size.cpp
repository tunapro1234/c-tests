#include <iostream>
#include <vector>

// 2, 5, 11
/*
3
6 6 6 
12 12 12 12 12 12 
24 24 24 24 24 24 24 24 24 24 24 24 

Her seferinde ikiye katlaniyor iste

*/

int main(){
	std::vector<int> a = {1, 2, 3};
	int oldSize, newSize;
	
	std::cout << a.capacity() << std::endl;
	oldSize = a.capacity();
	for (int i = 0; i < 100; i++){
		a.push_back(1);		
		newSize = a.capacity();
		std::cout << (float)newSize / oldSize << " ";
		oldSize = newSize;
		}
	return 0;
}
