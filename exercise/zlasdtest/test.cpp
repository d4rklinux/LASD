
#include "./exercise1a/test.hpp"
#include "./exercise1b/test.hpp"

#include "./exercise2a/test.hpp"
#include "./exercise2b/test.hpp"

#include "./exercise3/test.hpp"

/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */

void lasdtest() {
  cout << endl << "~*~#~*~ Welcome to the LASD Test Suite ~*~#~*~ " << endl;

  unsigned int loctestnum, loctesterr;
  unsigned int stestnum = 0, stesterr = 0;
  unsigned int ftestnum = 0, ftesterr = 0;

  loctestnum = 0; loctesterr = 0;
  testSimpleExercise1A(loctestnum, loctesterr);
  stestnum += loctestnum; stesterr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  testSimpleExercise1B(loctestnum, loctesterr);
  stestnum += loctestnum; stesterr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  testFullExercise1A(loctestnum, loctesterr);
  ftestnum += loctestnum; ftesterr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  testFullExercise1B(loctestnum, loctesterr);
  ftestnum += loctestnum; ftesterr += loctesterr;

  cout << endl << "Exercise 1 (Simple Test) (Errors/Tests: " << stesterr << "/" << stestnum << ")";
  cout << endl << "Exercise 1 (Full Test) (Errors/Tests: " << ftesterr << "/" << ftestnum << ")" << endl;

  stestnum = 0; stesterr = 0; ftestnum = 0; ftesterr = 0;

  loctestnum = 0; loctesterr = 0;
  testSimpleExercise2A(loctestnum, loctesterr);
  stestnum += loctestnum; stesterr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  testSimpleExercise2B(loctestnum, loctesterr);
  stestnum += loctestnum; stesterr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  testFullExercise2A(loctestnum, loctesterr);
  ftestnum += loctestnum; ftesterr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  testFullExercise2B(loctestnum, loctesterr);
  ftestnum += loctestnum; ftesterr += loctesterr;

  cout << endl << "Exercise 2 (Simple Test) (Errors/Tests: " << stesterr << "/" << stestnum << ")";
  cout << endl << "Exercise 2 (Full Test) (Errors/Tests: " << ftesterr << "/" << ftestnum << ")" << endl;

  stestnum = 0; stesterr = 0; ftestnum = 0; ftesterr = 0;

  loctestnum = 0; loctesterr = 0;
  testSimpleExercise3(loctestnum, loctesterr);
  stestnum += loctestnum; stesterr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  testFullExercise3(loctestnum, loctesterr);
  ftestnum += loctestnum; ftesterr += loctesterr;

  cout << endl << "Exercise 3 (Simple Test) (Errors/Tests: " << stesterr << "/" << stestnum << ")";
  cout << endl << "Exercise 3 (Full Test) (Errors/Tests: " << ftesterr << "/" << ftestnum << ")" << endl;

  cout << endl << "Goodbye!" << endl;
}
