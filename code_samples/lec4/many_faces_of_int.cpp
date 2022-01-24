/* 
 * This code demonstrates the amount of storage needed for different integer data types. The code also shows 
 * the range of values that can be represented in an integer type. 
 *
 * @author: Apan Qasem <apan@txstate.edu>
 * @date: 09/14/21 
 */


#include<iostream>
#include<limits>

using namespace std; 

int main() {

  /* integer data types */
  cout << "Memory space taken up by different integer data types in C++" << endl << endl;
  cout << "\tchar = " << sizeof(char) << " Bytes" << endl;
  cout << "\tshort = " << sizeof(short) << " Bytes" << endl;
  cout << "\tint = " << sizeof(int) <<  " Bytes" << endl;
  cout << "\tunsigned int = " << sizeof(unsigned int) << " Bytes" << endl;
  cout << "\tlong = " <<  sizeof(long) << " Bytes" << endl;
  cout << "\tlong long = " << sizeof(long long) << " Bytes" << endl << endl; 

  /* pointers */
  cout << "Memory space taken up by a pointer data type" << endl << endl;
  cout << "\tint* = " << sizeof(int *) << " Bytes" << endl; 
  cout << "\tdouble* = " << sizeof(double *) << " Bytes" << endl << endl; 

  /* ranges */
  cout << "Range of values that can be represented with integer data types" << endl << endl;
  cout << "\tMAX_INT = " << INT_MAX << endl;
  cout << "\tMAX_UINT = " << UINT_MAX << endl;
  cout << "\tMAX_LONG = " << LONG_MAX << endl;
  cout << "\tMAX_LONG_LONG = " << __LONG_LONG_MAX__ << endl << endl;
  return 0;
}

/* 
 *
 *  1. Will this code compile? Which parts of the code seem problematic?
 *
 *  2. What does the sizeof() function return? Have you ever had to use it?
 *
 *  3. From a programmer's perspective, what is the difference between int and long?
 *
 *  4. From a programmer's perspective, what is the difference between long and long long?
 *
 *  5. Write down what you expect from each line of output. Then compile and run the code and check if your guess are correct.
 *
 */

