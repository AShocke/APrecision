#include "precision.h"
#include <cstdio>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>
#include <ctype.h>


real_precision::real_precision(bool negative, int exponent, int decimal_precision,
			       int base, bool debug) {
  int size = exponent + decimal_precision + 1;
  decimal_precision = decimal_precision;
  decimal_ = exponent;
  exponent_ = exponent;
  base_ = base;
  is_negative_ = negative;
  store_ =  new std::vector<int> (size);
  store_size_ = size;
  DEBUG = debug;
}

std::string real_precision::real_to_string()
{
	std::string real = "";
	if (is_negative_) {
		real.append("-");
	}
	int exp = exponent_;
	if (exp < 0) {
   		real.append("0.");
		int i = 0;
		while (i < abs(exp) - 1) { // in an n x 10^(z) number, where z < 0,
								   // there are |z| - 1 zeroes before the first number
			real.append("0");
		    i++;
		}
		for (int i = store_->size() - 1; i >= 0; i--) {
		  printf("%d\n", (*store_)[i]);
		  real.append(std::to_string((*store_)[i]));
		}
	}
	else if (exp >= 0) {
		
		for(int i = store_->size() - 1; i >= 0; i--) {
			if (i == store_->size() - (exp + 1)) { // We always place to the right of exponent number!
				real.append(".");
			}
			real.append(std::to_string((*store_)[i]));
		}
		
		if (exponent_ + 1 > store_->size()) {
			/* In this case it is safe to compare a signed integer to a size_type because we know that
               exponent_ is greater than 0
			*/
			
			for (unsigned i = 0; i < exponent_  + 1 - store_->size(); i++) {
				real.append("0");
			}
		}
	}
	return real;
}


real_precision real_precision::operator+(real_precision n)
{
	return add(n);
}

/*
 * Gradeschool addition algorithm
 * Assumes that:
 * **both numbers have the same base**
 * the bases of the real_precision objects are valid with their stores
 * Require that the numbers have the same all around precision, before and after decimal place
 */
real_precision real_precision::add(real_precision n)
{
	if (DEBUG) {
		printf("In add(real_precision)...\n");
		printf("Adding %s and %s \n", this->real_to_string().c_str(),
		       n.real_to_string().c_str());
		if (exponent_ != n.exponent_ || decimal_precision_ != n.decimal_precision_) {
		    std::cerr << "Real precision objects are not of the same precision. \n";
		    return n;
		}
		else {
		    
		}
		
	}
	

   if (DEBUG) {
	   printf("leaving add...\n");
   }
   return n;
}

// copies the numbers of a given real_precison object to a vector
void real_precision::copy_store(std::vector<int> store, int start_s,  int to_add,
				std::vector<int> &n, int start_n)
{
	for (int i = start_n; i < start_n + to_add; i++ ) {
		n[i] = store[start_s + start_n-i];
	}
}
void real_precision::print()
{
	for (unsigned i = 0; i < store_->size(); i++) {
	    printf("%d ", (*store_)[i]);
	}
	printf("\n");
}
void real_precision::print_to_string()
{
	std::string s = this->real_to_string();
	printf("%s\n", s.c_str());
}

/*
 * 
 * Private functions
 *
 */

// prepares a vector for addition and subtraction
int real_precision::find_size(real_precision x, real_precision y)
{
	if (DEBUG) {
		printf("In find_size(real_precision, real_precision)\n\n");
	}
	int size;
	int digits_before_x = x.before_decimal(); // digits before the decimal (to the right)
	int digits_before_y = y.before_decimal();
	int digits_after_x = x.after_decimal(); // digits after the decimal (to the right)
	int digits_after_y = y.after_decimal();
	// if (x.get_exponent() >= 0) {
	// 	digits_after_x = (x.digits() > digits_before_x)? (x.digits() - digits_before_x) : 0;
	// }
	// else {
	// 	digits_after_x = abs(x.get_exponent()) + x.digits() - 1; // There are (exponent - 1) zeroes
	// 															 // followed by all the digits.  
	// }
	// if (y.get_exponent() >= 0) {
	// 	digits_after_y = (y.digits() > digits_before_y)?  y.digits() - digits_before_y: 0;
	// }
	// else {
	// 	digits_after_y = abs(y.get_exponent()) + y.digits() - 1; // There are (exponent - 1) zeroes
	// 															 // followed by all the digits.  
	// }
	size = std::max(digits_before_x, digits_before_y) 
	       + std::max(digits_after_x, digits_after_y);
   	if (DEBUG) {
		printf("digits_before_x: %d \ndigits_before_y: %d \ndigits_after_x: %d \ndigits_after_y: %d\n"
			   ,digits_before_x, digits_before_y, digits_after_x, digits_after_y);
		printf("return (int): %d\n", size);
		printf("Leaving find_size...\n\n");
	}
	return size;

}
