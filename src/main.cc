#include <iostream>
#include <vector>
#include <iostream>
#include "precision.h"


int main() {
	// TESTS
	std::vector<int> a = {1}; // 
	int a_decimal = -4;									   
	std::vector<int> b = {9, 9, 9, 9, 9};
	int b_decimal = 0;

	real_precision rp_a (a, false, a_decimal);
	real_precision rp_b (b, false, b_decimal);
	rp_a.print_to_string();
	rp_b.print_to_string();
	real_precision rp_sum = rp_a.add(rp_b);
	rp_sum.print();				
	rp_sum.print_to_string();	
	
}

