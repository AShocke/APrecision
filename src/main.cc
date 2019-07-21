#include <iostream>
#include <vector>
#include <iostream>
#include "precision.h"


int main() {
	bool debug = true;
	std::vector<int> v = {1, 2, 3};
	std::vector<int> l = {3 , 2, 1};
	int exp = 3;
	bool neg = false;
	int base = 10;
	real_precision rp_a(v, neg, exp, base, debug);
	real_precision rp_b(l, neg, -exp, base, debug);
	rp_a.print();
	rp_a.print_to_string();
	rp_b.print();
	rp_b.print_to_string();
	real_precision sum = rp_a.add( rp_b );
	sum.print();
	sum.print_to_string();
}

