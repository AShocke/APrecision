#include <iostream>
#include <vector>
#include <iostream>
#include "precision.h"


int main() {
	bool debug = true;
	std::vector<int> v = {6, 2, 6};
	std::vector<int> l = {3 , 2, 3};
	int exp = 3;
	int decimal = 1;
	bool neg = false;
	int base = 10;
	real_precision rp_a(&v, neg, exp, decimal, base, debug, false);
	real_precision rp_b(&l, neg, exp, decimal, base, debug, false);
	rp_a.print();
	rp_a.print_to_string();
	rp_b.print();
	rp_b.print_to_string();
	real_precision sum = rp_a.add( rp_b );
	sum.print();
    sum.print_to_string();
	return 0;
}

