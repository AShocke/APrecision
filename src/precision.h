
/*
 * precision.h
 * Author: Aisosa Efemwonkieke <isosceles.aisosa@gmail.com>
 * Numbers stored in reverse
 */
#ifndef AP
#define AP
#include <iostream>
#include <vector>
#include <string>

class real_precision {
public:
     /* the simple constructor for the arbitrary precision class 
      * is_negative states if real number is negative
      * TODO in .cc file

      */
     real_precision(std::vector<int>* real_number, bool negative,
		    int exponent, int decimal_precision, int base,
		    bool debug = false);

     real_precision(bool negative, int exponent, int decimal_precision,
		    int base, bool debug = false);
     /*
      * String constructor:
      * Converts a string to a real_precision instance. If string is invalid and error
      * message is outputed and empty_precision() is called
      */
     real_precision(std::string real_string, int precision);
     real_precision() {
     };
     /* Can be used to set a default precision class
      * (store_.size() = 0, exponent_ = 0, is_negative_ = false)
      */
     void empty_precision() {
	  store_ = new std::vector<int> (0);
	  exponent_ = 0;
	  decimal_ = 0;
	  decimal_precision_ = 0;
	  is_negative_ = false;
     }
     // destrctor
     ~real_precision() {
	  delete store_;
     }
     /*
      * get functions
      */
     std::vector<int>* get_real_store() { return store_; }
     bool is_negative() { return is_negative_; }
     int get_exponent() { return exponent_; }
     size_t size() { return store_->size(); }
     int before_decimal() { // to the right of decimal point
	  return (exponent_ >= 0)? exponent_ + 1: 0;
     };

     int after_decimal() { // to the left of decimal point
	  int after = before_decimal();
	  if (exponent_ >= 0) {
	       return (store_->size() > after)? (store_->size() - after): 0;
	  }
	  else {
	       return abs(exponent_) + store_->size() - 1;
	  }
     }
	
     /* Operations */
     /*
      * 1x10^4 + 1x10^(-4) = 10000 + 0.00001 a total of 10 digits
      */
     real_precision operator+ (real_precision a);
     real_precision add(real_precision n);
     real_precision subtract(real_precision a);
     real_precision multiply(real_precision a);
     real_precision karatsuba(real_precision a);
     std::string real_to_string();
     void print();
     void print_to_string();
private:
     bool DEBUG;
     std::vector<int>* store_;
     unsigned int store_size_;
     int exponent_;
     bool is_negative_;
     unsigned base_;
     int decimal_; // The index after the decimal point
     int decimal_precision_;
     void debug_msg() {
	 printf("Debugging On\n");
     }
     /*
      * Helper to operations
      */
	
     /* 
      * prepare_store
      * finds the size of a store based
      * on the parameters given, so that the store has the maximum size needed to 
      * function.
      * prepare_store(real_precision x, real_precision y) -- addition subtraction
      * (TODO) other implementations

      */
     int find_size(real_precision x, real_precision y);
     /*
      * copy_store:
      * fills the target 'n vector with the store contents of real_precision object s from start_s to
      * end_s beginning at start n
      *
      */
     void copy_store(std::vector<int> s, int start_s, int end_s, std::vector<int> &n, int start_n);
	
};

#endif
