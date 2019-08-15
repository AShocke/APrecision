#include "precision.h"
#include <cstdio>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>
#include <ctype.h>


real_precision::real_precision(bool negative, int exponent, int decimal_precision,
			       int base, bool debug, bool error) 
{
	//TODO Improper input checking
  int size = exponent + decimal_precision + 1;
  decimal_precision_ = decimal_precision;
  decimal_ = exponent;
  exponent_ = exponent;
  base_ = base;
  is_negative_ = negative;
  store_ =  new std::vector<int> (size);
  store_->at(0) = 0;
  store_size_ = size;
  DEBUG = debug;
  is_error_ = error;
}

real_precision::real_precision(std::vector<int>* real_number, bool negative,
    int exponent, int decimal_precision, int base,
    bool debug, bool error)
{
	//TODO improper input checking
    int size = real_number->size();
    decimal_precision_ = decimal_precision;
    decimal_ = exponent;
    exponent_ = exponent;
    base_ = base;
    is_negative_ = negative;
    store_ =  new std::vector<int> (size);
	for (int i = 0; i < size; i++) {
		store_->at(i) = real_number->at(i);
	}
    store_size_ = size;
    DEBUG = debug;  
	is_error_ = error; 	
}

std::string real_precision::real_to_string() 
{
	if (is_error_ == true) {
		return "ERROR";
	}
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
	if (is_error_ == true) {
		printf("Cannot do operation on error precision.\n");
		return error_precision();
	}
	return add(n);
}

/*
 * Gradeschool addition algorithm
 * Assumes that:
 * **both numbers have the same base**
 * the bases of the real_precision objects are valid with their stores
 * Require that the numbers have the same all around precision, before and after decimal place
 * Overflows are note accounted for, so make sure there is enough precision in the exponent to add.
 */
real_precision real_precision::add(real_precision &n)
{
	if (is_error_ == true) {
		printf("Cannot do operation on error precision.\n");
		return error_precision();
	}
	if (DEBUG) {
		printf("In add(real_precision)...\n");
		printf("Adding %s and %s \n", this->real_to_string().c_str(),
		     n.real_to_string().c_str());
	}
	if (exponent_ != n.exponent_ || decimal_precision_ != n.decimal_precision_) {
		if (DEBUG) {
			std::cerr << "this exponent = " << exponent_ 
				<< "; other exponent = " << n.exponent_  << "\n";
			std::cerr << "this decimal = " << decimal_precision_
				<< "; other decimal = " << n.decimal_precision_ << "\n";
		}
	    std::cerr << "Real precision objects are not of the same precision. \n";
	    return error_precision();
	}
	else {
		std::vector<int>* sum_store = new std::vector<int>(store_size_);
		if ((*store_)[store_size_ - 1] + (*n.store_)[store_size_ - 1] >= 9) {
			std::cerr << "WARNING: Possible Overflow:\n";
		}
		int carry = 0;
		for (int i = 0; i < store_size_; i++) {
			int sum = (*store_)[i] + (*n.store_)[i] + carry;
			sum_store->at(i) = sum % 10;
			carry = sum / 10;
		}
		if(carry != 0)
		{
			std::cerr << "WARNING: An overflow has occured " 
				<< "further operations with the resulting class is marred.\n";
		}
	   
		 real_precision sum_p(sum_store, is_negative_, exponent_, decimal_precision_, base_,
		 DEBUG);
		delete sum_store;
 	    if (DEBUG) {
 	 	   printf("leaving add...\n");
 	    }
		 return sum_p;
	}

   
}

// copies the numbers of a given real_precison object to a vector
void real_precision::copy_store(std::vector<int> store, int start_s,  int to_add,
				std::vector<int> &n, int start_n)
{
	if (is_error_ == true) {
		printf("Cannot do operation on error precision.\n");
		return;
	}
	for (int i = start_n; i < start_n + to_add; i++ ) {
		n[i] = store[start_s + start_n-i];
	}
}
void real_precision::print()
{
	if (is_error_ == true) {
		printf("ERR\n");
	}
	for (unsigned i = 0; i < store_->size(); i++) {
	    printf("%d ", (*store_)[i]);
	}
	printf("\n");
}
void real_precision::print_to_string()
{
	if (is_error_ == true) {
		printf("ERR\n");
		return;
	}
	std::string s = this->real_to_string();
	printf("%s\n", s.c_str());
}

/*
 * 
 * Private functions
 *
 */

