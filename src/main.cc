#include <iostream>
#include <vector>
#include <iostream>
#include "precision.h"


int main() {
	printf("Enter a number of arbitrary precision.\n");
	std::string s;
	std::cin >> s;
	
	real_precision rp_a (s);
	rp_a.print();
	rp_a.print_to_string();
}

