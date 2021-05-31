// driver program for DynArray class
// Author: Rafaela Lomboy

// TASKS:
// handle exceptions
// string red("\033[0;31m");
// string green("\033[1;32m");
// string yellow("\033[1;33m");
// string cyan("\033[0;36m");
// string magenta("\033[0;35m");
// string reset("\033[0m");

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class UnitTester {
private:
  static const int WIDTH = 50;    // char width to display on console
  static const string RED, GRN,  // change text color and bold
                      UL,         // underlines white text
                      RST;        // reset to default color
  string tTitle;      // name of test (usually has class name if testing class)
public:
  UnitTester(string str);
  void static tEqual(string msg, int cVal, int tVal);
  void static tEqual(string msg, string cVal, string tVal);
  void title();
  void title(string str);
  void subTitle(string str);
  void classTest();
};

const string UnitTester::RED = "\033[1;31m";  // color text bold red
const string UnitTester::GRN = "\033[1;32m";  // color text bold green
const string UnitTester::UL = "\033[4;37m";   // underlines white text
const string UnitTester::RST = "\033[0m";     // reset to default text settings

UnitTester::UnitTester(string str = "Performing Unit Test") : tTitle(str) { }

void UnitTester::tEqual(string msg, int cVal, int tVal) {
// This method performs equality tests on ints (can take boolean too).
// msg = test message, cVal = correct value to compare, tVal = test value

  int msgLen = msg.length();    // length of message
  string testRes,               // pass or fail test result and labels
         testP = GRN + "Pass" + RST,
         testF = RED + "Fail" + RST;

  // label for test
  cout << msg << string(WIDTH - msgLen, '.');

  // test equality and print result
  testRes = (tVal == cVal) ? testP : testF;
  cout << testRes << endl;
}

void UnitTester::tEqual(string msg, string cStr, string tStr) {
// This method performs equality tests (msg = display test message,
// cStr = correct value to compare, tStr = test value).

  int msgLen = msg.length();    // length of message
  string testRes,               // pass or fail test result and labels
         testP = GRN + "Pass" + RST,
         testF = RED + "Fail" + RST;

  // label for test
  cout << msg << string(WIDTH - msgLen, '.');

  // test equality and print result
  testRes = (tStr == cStr) ? testP : testF;
  cout << testRes << endl;
}

void UnitTester::title() {
// Prints out title/header for overall test.
  cout << tTitle << endl << string(WIDTH + 4, '-') << endl;
}

void UnitTester::title(string str) {
// Prints out title/header for overall test.
  tTitle = str;
  cout << str << endl << string(WIDTH + 4, '-') << endl;
}

void UnitTester::subTitle(string str) {
// Prints out title for using entered string (usually for labelling  subtests
// of one method, or pass/fail testing).
  cout << UL << str << RST << endl;
}

void UnitTester::classTest() {

  UnitTester eqTest("Testing UnitTester class"); // for performing equality tests

  eqTest.title();

  // testing if tEqual method shows pass
  eqTest.subTitle("Passing Tests");
  eqTest.tEqual("tEqual(str, int, int)", 4, 4);
  eqTest.tEqual("tEqual(str, str, str)", "korra", "korra");

  // // testing if tEqual method shows fail
  eqTest.subTitle("\nFailing Tests (these should fail!)");
  eqTest.tEqual("tEqual(str, int, int)", 4, 5);
  eqTest.tEqual("tEqual(str, str, str)", "avatar", "korra");

  cout << "\nEnd of UnitTester class tests.\n\n";
}

class DynArray {
  friend ostream &operator<<(ostream& out, const DynArray& array);
  private:
    int* array;
    int size;
    int WIDTH;
    void indexError() const {
      cout << "Index outside of array range.\n";
      exit(1);
    }
  public:
    DynArray(int s);
    DynArray(const DynArray& obj); // copy constructor
    ~DynArray();
    int &operator[](int index) const;
    DynArray& operator=(const DynArray& rhs);
    bool operator==(const DynArray& rhs);
    void print();
    void push(int val);
    void pop();
    int getSize() const;
    void classTest();
};

DynArray::DynArray(int s = 0) : size(s) {
// This is the default DynArray constructor, which uses inputted size to
// initialize a dynamically allocated array.

  // size = s;               // user-inputted size

  array = new int[size];

  // initialize each element to 0
  for (int i = 0; i < size; i++)
    array[i] = 0;
}

// overloaded copy constructor
DynArray::DynArray(const DynArray& obj) {

  // assign size and copy elements of obj into this array
  size = obj.size;
  array = new int[size];

  for (int i = 0; i < size; i++)
    array[i] = obj.array[i];
}

DynArray::~DynArray() {
// This is the DynArray destructor, which frees allocated memory.

  delete [] array;
  array = nullptr;
}

int& DynArray::operator[](int index) const {

  // error if accessing element outside of array range
  if (index < 0 || index > (size - 1))
    indexError();

  return array[index];
}

// add move constructor !!
// move assignment operator !!

// overloaded assignment operator
DynArray& DynArray::operator=(const DynArray& rhs) {
  // check if object is being assigned to self, then assign member variables
  if (this != &rhs) {
    // delete lhs array if it contains elements
    if (size > 0)
      delete [] array;

    // now assign size and copy elements of rhs to this array
    size = rhs.size;
    array = new int[size];

    for (int i = 0; i < size; i++)
      array[i] = rhs.array[i];
  }

  return *this;
}

// overloaded equality operator
bool DynArray::operator==(const DynArray& rhs) {
  bool isEqual = false;
  int index = 0;

  // if sizes are not equal, return false
  if (size != rhs.size)
    return isEqual;

  // loop until parallel values are unequal or end of array reached
  while (!isEqual || index < size) {
    isEqual = (array[index] == rhs.array[index]);
    index++;
  }

  return isEqual;
}

void DynArray::print() {
// This DynArray method prints out array contents.

  if (size == 0)
    cout << "Array has size 0 and no elements.\n";
  else {
    for (int i = 0; i < size; i++)
      cout << array[i] << " ";
  }

  cout << endl;
}

void DynArray::push(int val = 0) {
// This DynArray method increases array size by one element and adds a value to
// its last element.

  int* temp = nullptr;  // to copy elements into larger array

  // create temporary array one size larger
  temp = new int[++size];

  // copy elements only if old array size is not 0 (size already incremented)
  if (size != 1) {
    for (int i = 0; i < (size - 1); i++)
      temp[i] = array[i];
  }

  // add element at end of temp array
  temp[size - 1] = val;

  // free allocated memory of old array and reassign
  delete [] array;
  array = temp;
}

void DynArray::pop() {
// This DynArray method shrinks array size by one element.

  int* temp = nullptr;  // to copy elements into smaller array

  // throw exception if size == 0??? idek this works tho...

  if (size == 0)
    cout << "ERROR: Cannot subtract element from array of size 0.\n";
  else {
    // create temporary array one size smaller
    temp = new int[--size];

    // copy elements of old array into temp until filled
    for (int i = 0; i < size; i++)
      temp[i] = array[i];

    // free allocated memory of old array and reassign
    delete [] array;
    array = temp;
  }
}

int DynArray::getSize() const { return size; }

// overloaded ostream operator
ostream &operator<<(ostream& out, const DynArray& array) {

  if (array.size == 0)
    out << "Array has size 0 and is empty.\n";
  else {
    // outputs all array contents to stream, separated by spaces
    for (int i = 0; i < array.size; i++)
      out << array[i] << " ";
  }

  return out;
}

void DynArray::classTest() {
// This DynArray method performs a self diagnostic on the class.

  UnitTester ut("Testing DynArray class");
  DynArray tArr(3), tArr1;  // to test DynArray methods

  ut.title();

  // testing push method
  tArr.push(7);
  ut.tEqual("push()", 7, tArr[3]);

  // testing pop method
  tArr.pop();
  ut.tEqual("pop()", 3, tArr.getSize());

  // testing default constructor
  ut.subTitle("\nDefault Constructor");
  ut.tEqual("Size Initialization", 3, tArr.getSize());
  cout << "Printing array (each element should be zero):\t "
       << tArr << endl << endl;

  // change tArr elements with known values for testing
  for (int i = 0; i < tArr.getSize(); i++)
    tArr[i] = 7;

  // testing overloaded copy constructor
  DynArray tArr2 = tArr;
  ut.tEqual("Copy Constructor", true, (tArr == tArr2));

  // testing overloaded assignment operator
  tArr1 = tArr;
  ut.tEqual("Overloaded Assignment Operator", true, (tArr == tArr1));

  cout << "\nEnd of testing DynArray class.\n\n";
}



int main()
{
  DynArray a1(3);

  a1.classTest();

  return 0;
}
