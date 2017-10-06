#ifndef AP
#define AP
#include <iostream>
#include <vector>
#include <string>

class real_precision {
public:
	/* the simple constructor for the arbitrary precision class is_negative states
	 * if real number is negative
	 * decimal_point is an  integer denoting the place of the decimal point or 0 if
	 * it is at the begining of the	number (eg. 0.356 decimal_point = 0, 0.00356 decimal_point = -2) 
	 */
	real_precision(std::vector<int> real_number, bool negative, int exp) {
		store_ = real_number;
		is_negative_ = negative;
		exponent_ = exp;
  	};
	/*
	 String constructor:
	 Converts a string to a real_precision instance. If string is invalid and error
	message is outputed and class is initialized with a store_.size()
 	*/
	real_precision(std::string real_string);
	real_precision() {
	};
	/* Can be used to set a default precision class
	 * (store_.size() = 0, exponent_ = 0, is_negative_ = false)
	 */
	void empty_precision() {
		store_ = std::vector<int> (0);
		exponent_ = 0;
		is_negative_ = false;
	}
	// destrctor
	~real_precision() {
	}
	/*
	 * get functions
	 */
   	std::vector<int> get_real_store() { return store_; }
	bool is_negative() { return is_negative_; }
	long get_exponent() { return exponent_; }
	size_t store_size() { return store_.size(); }
	
	/* Operations */
	real_precision operator+ (real_precision a);
	real_precision add(real_precision n);
	real_precision subtract(real_precision a);
	real_precision multiply(real_precision a);
    real_precision karatsuba(real_precision a);
	std::string real_to_string();
	void print();
	void print_to_string();
private:
	std::vector<int> store_;
	int exponent_;
	bool is_negative_;
	
};

std::vector<int> expand(real_precision a); // makes it easier to do operations
#endif
