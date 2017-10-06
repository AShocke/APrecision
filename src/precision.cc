#include "precision.h"
#include <cstdio>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>
#include <ctype.h>



real_precision::real_precision(std::string str)
{
	if (str.size() == 0) {
		fprintf(stderr, "No input was detected!\n");
		empty_precision();
		return;
	}
	std::vector<int> store;
	int exp = 0; // Exponent of string representation of digit
	int decimal_count = 0; // Number of '.' characters
	bool insignificant = true; // Keeps track of insignificant zeroes.
							   // If current number is zero, insignificant stays true
	bool exponent_is_neg = false;
	bool no_decimal = true;
	is_negative_ = false;
	size_t i = 0;
	if (str[0] == '-') {
		is_negative_ = true;
		i++;
	}
	for (; i < str.size(); i++) {
		if (str[i] - '0' == 0 && insignificant) {
			if (exponent_is_neg)
				exp--;
		}
		else if ((str[i] == '.' || str[i] == ',') && decimal_count == 0) {
			no_decimal = false;
			if (insignificant) {
				exponent_is_neg = true;
			}
			else {
				exp = i-1;
			}
		}
		else if (!isdigit(str[i])){
			fprintf(stderr, "Input is invalid! '%c' is not a digit! Please try again.\n"
					, str[i]);
			empty_precision();
			return;
		}
		else {
			store.push_back(str[i] - '0');
			insignificant = false;
		}
		
	}
	if (no_decimal) {
		exponent_ = store.size() - 1;
	}
	else {
		exponent_ = exp;
	}
	store_ = store;
}

std::string real_precision::real_to_string()
{
	std::string real = "";
	if (is_negative_) {
		real.append("-");
	}
	int exp = exponent_;
	if (exp < 0) {
   		real.append(".");
		while (exp < -1) {
			real.append("0");
		    exp++;
		}
		for (unsigned i = 0; i < store_.size(); i++) {
			printf("%d\n", store_[i]);
			real.append(std::to_string(store_[i]));
		}
	}
	else if (exp >= 0) {
		
		for(unsigned i = 0; i < store_.size(); i++) {
			if (i == exp + 1) { // We always place to the right of exponent number!
				real.append(".");
			}
			real.append(std::to_string(store_[i]));
		}
		
		if (exponent_ > store_.size()) {
			/* In this case it is safe to compare a signed integer to a size_type because we know that
               exponent_ is greater than 0
			*/
			
			for (unsigned i = 0; i < exponent_ - store_.size() - 1; i++) {
				real.append("0");
			}
		}
	}
	return real;
}


real_precision real_precision::operator+(real_precision n)
{
	return n;
	
}

real_precision real_precision::add(real_precision n)
{
	int sum_size = ((n.store_size() > store_.size())? n.store_size() : store_.size()) + 1;
	std::vector<int> sum(sum_size);
	// the exponent (10^n) of the last digit in the precision representation
	int last_digit = store_.size() - exponent_; 
	int last_digit_n = n.store_size() - n.exponent_;
	int between = abs(last_digit_n - last_digit); // number of zeroes inbetween the last dits
	std::vector<int> least_store; // store with the last digit int the least digit place
	std::vector<int> most_store; // the converse of least_store
	if (last_digit > last_digit_n) {
		least_store = store_;
		most_store = n.get_real_store();
	}
	else {
		least_store = n.get_real_store();
		most_store = store_;
	}
	printf("between: %d\n", between);
	std::vector<int>::reverse_iterator rit = sum.rbegin();
	std::vector<int>::reverse_iterator most_i = most_store.rbegin(); 
	std::vector<int>::reverse_iterator least_i = least_store.rbegin();
	for (least_i = least_store.rbegin(); least_i != least_store.rbegin() + between; least_i++) {
		*rit = *least_i;
		rit++;
	}

   	int carry = 0;
    rit = sum.rbegin() + between;
	least_i = least_store.rbegin() + between;
	while (rit < sum.rend()) {
		// If all real_precisions are exhausted then the sum vector is at its last element
		// (Remember the sum vector size is the largest real_precisions size + 1)
		if ((least_i == least_store.rend()) && (most_i == most_store.rend())) {
			*rit = carry;
			
			rit++;
		}
		else if(least_i == least_store.rend()) {
			*rit = (*most_i + carry) % 10;
			carry = (*most_i + carry) / 10;
			printf("*rit: %d, carry: %d: \n", *rit, carry);
			rit++;
			most_i++;
		}
		else if (most_i ==  most_store.rend()) {
			*rit = (*least_i + carry) % 10;
			carry = (*least_i + carry) / 10;
			rit++;
			least_i++;
		}
		else {
			*rit = (*least_i + *most_i + carry) % 10;
			carry =  (*least_i + *most_i + carry) / 10;
			printf("carry: %d\n", carry);
			rit++;
			least_i++;
			most_i++;
		}
	}
	for (std::vector<int>::iterator it = least_store.begin(); it != least_store.end(); it++) {
		printf("%d ",*it);
	}
	printf("\n");
   	int sum_exp = ((n.get_exponent() > exponent_)? n.get_exponent() : exponent_);
	if (carry == 1) {
		sum_exp++;
		return real_precision(sum, false, sum_exp);
	}
	else {
		sum.erase(sum.begin());
	}
	return real_precision(sum, false, sum_exp);
}


void real_precision::print()
{
	for (unsigned i = 0; i < store_.size(); i++) {
		printf("%d ", store_[i]);
	}
	printf("\n");
}
void real_precision::print_to_string() {
	std::string s = this->real_to_string();
	printf("%s\n", s.c_str());
}
// eg: transformes [1,3,4] exponent -3, to [0,0,1,3,4] representing .00134
std::vector<int> expand(real_precision b, int before, int after) {
	before += std::abs(b.get_exponent());
	int size = before + after;
	std::vector<int> expanded(size, 0);
	for (int x = before; x < before + b.store_size(); x++) {
		expanded[x] = b.get_real_store()[x - before];
		
	}
	return expanded;
}
