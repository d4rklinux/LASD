
#include <iostream>

/* ************************************************************************** */

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/linear.hpp"

#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/stack/stack.hpp"
#include "../zlasdtest/queue/queue.hpp"
#include "../zlasdtest/list/list.hpp"

#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

#include "../zlasdtest/iterator/iterator.hpp"
#include "../zlasdtest/binarytree/binarytree.hpp"
#include "../zlasdtest/bst/bst.hpp"

#include "../iterator/iterator.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../bst/bst.hpp"

#include "../hashtable/hashtable.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

#include "../zlasdtest/hashtable/hashtable.hpp"


/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

  void mytestVectorInt(unsigned int &testnum, unsigned int &testerr)
{
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl
       << "Inizio del test Vector<int>:" << endl;
  try
  {
    {
      lasd::SortableVector<int> vec;
      Empty(loctestnum, loctesterr, vec, true);

      GetFront(loctestnum, loctesterr, vec, false, 0);
      GetBack(loctestnum, loctesterr, vec, false, 0);
      SetAt(loctestnum, loctesterr, vec, false, 1, 0);
      GetAt(loctestnum, loctesterr, vec, false, 2, 0);

      Exists(loctestnum, loctesterr, vec, false, 0);

      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
    }
    {
      lasd::SortableVector<int> vec(3);
      Empty(loctestnum, loctesterr, vec, false);
      Size(loctestnum, loctesterr, vec, true, 3);

      SetAt(loctestnum, loctesterr, vec, true, 0, 10);
      SetAt(loctestnum, loctesterr, vec, true, 1, 20);
      SetAt(loctestnum, loctesterr, vec, true, 2, 30);

      GetFront(loctestnum, loctesterr, vec, true, 10);
      GetBack(loctestnum, loctesterr, vec, true, 30);

      SetFront(loctestnum, loctesterr, vec, true, 5);
      SetBack(loctestnum, loctesterr, vec, true, 4);

      Exists(loctestnum, loctesterr, vec, true, 20);

      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 29);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 1, 400);

      vec.Sort();

      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

      
    }
  }
  catch (...)
  {
    loctestnum++;
    loctesterr++;
    cout << endl
         << "Errore non gestito! " << endl;
  }
  cout << "Fine del test Vector<int>! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
  }

/* ************************************************************************** */

void mytestVectorDouble(unsigned int &testnum, unsigned int &testerr)
{
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl
       << "Inizio del test Vector<double>:" << endl;
  try
  {
    lasd::SortableVector<double> vec(3);
    Empty(loctestnum, loctesterr, vec, false);
    Size(loctestnum, loctesterr, vec, true, 3);

    SetAt(loctestnum, loctesterr, vec, true, 0, 10.0);
    SetAt(loctestnum, loctesterr, vec, true, 1, 20.0);
    SetAt(loctestnum, loctesterr, vec, true, 2, 30.0);

    GetFront(loctestnum, loctesterr, vec, true, 10.0);
    GetBack(loctestnum, loctesterr, vec, true, 30.0);

    Exists(loctestnum, loctesterr, vec, true, 30.0);

    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 2.0, 62.0);
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<double>, 2.0, 12000.0);

    vec.Sort();

    TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
    TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);

    vec.Resize(2);
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<double>, 1, 200);
  }
  catch (...)
  {
    loctestnum++;
    loctesterr++;
    cout << endl
         << "Errore non gestito! " << endl;
  }
  cout << "Fine del test Vector<double>! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestVectorString(unsigned int &testnum, unsigned int &testerr)
{
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl
       << "Inizio del test Vector<string>:" << endl;
  try
  {
    lasd::SortableVector<string> vec(2);

    Empty(loctestnum, loctesterr, vec, false);
    Size(loctestnum, loctesterr, vec, true, 2);

    SetAt(loctestnum, loctesterr, vec, true, 0, string("X"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("Y"));

    GetFront(loctestnum, loctesterr, vec, true, string("X"));
    GetBack(loctestnum, loctesterr, vec, true, string("Y"));

    Exists(loctestnum, loctesterr, vec, true, string("Y"));

    MapPreOrder(loctestnum, loctesterr, vec, true, [](string &str)
                { MapStringAppend(str, string(" ")); });
    TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XX Y "));
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XY X "));

    Exists(loctestnum, loctesterr, vec, false, string("Y"));

    lasd::SortableVector<string> copvec(vec);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    MapPreOrder(loctestnum, loctesterr, vec, true, [](string &str)
                { MapStringAppend(str, string("!")); });
    NonEqualVector(loctestnum, loctesterr, vec, copvec, true);

    copvec = std::move(vec);
    FoldPreOrder(loctestnum, loctesterr, copvec, true, &FoldStringConcatenate, string("?"), string("?X !Y !"));

    lasd::SortableVector<string> movvec(std::move(vec));
    FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?X Y "));
    movvec.Sort();
    FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?X Y "));
    SetAt(loctestnum, loctesterr, vec, false, 1, string(""));
    vec.Resize(1);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("Y"));

    movvec.Clear();
    Empty(loctestnum, loctesterr, movvec, true);
  }
  catch (...)
  {
    loctestnum++;
    loctesterr++;
    cout << endl
         << "Errore non gestito! " << endl;
  }
  cout << "Fine del test Vector<string>! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestListInt(unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio del test List<int>:" << endl;
  try {
    lasd::List<int> lst;
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    GetFront(loctestnum, loctesterr, lst, false, 0);
    GetBack(loctestnum, loctesterr, lst, false, 0);

    Exists(loctestnum, loctesterr, lst, false, 0);

    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0);

    RemoveFromFront(loctestnum, loctesterr, lst, false);
    FrontNRemove(loctestnum, loctesterr, lst, false, 0);

    InsertAtBack(loctestnum, loctesterr, lst, true, 50);
    InsertAtFront(loctestnum, loctesterr, lst, true, 40);
    InsertAtFront(loctestnum, loctesterr, lst, true, 30);
    InsertAtBack(loctestnum, loctesterr, lst, true, 20);
    InsertAtFront(loctestnum, loctesterr, lst, true, 10);

    GetFront(loctestnum, loctesterr, lst, true, 10);
    GetBack(loctestnum, loctesterr, lst, true, 20);
    SetFront(loctestnum, loctesterr, lst, true, 30);
    SetBack(loctestnum, loctesterr, lst, true, 20);

    GetAt(loctestnum, loctesterr, lst, true, 3, 50);
    SetAt(loctestnum, loctesterr, lst, true, 3, 35);

    Exists(loctestnum, loctesterr, lst, false, 45);

    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 155);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 1, 25200000);

    RemoveFromFront(loctestnum, loctesterr, lst, true);
    FrontNRemove(loctestnum, loctesterr, lst, true, 30);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 1, 28000);

    lasd::List<int> coplst(lst);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    MapPreOrder(loctestnum, loctesterr, lst, true, &MapIncrement<int>);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    InsertAtFront(loctestnum, loctesterr, lst, true, 0);
    InsertAtBack(loctestnum, loctesterr, lst, true, 0);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);
    coplst = lst;
    EqualList(loctestnum, loctesterr, lst, coplst, true);

    RemoveFromFront(loctestnum, loctesterr, coplst, true);
    FrontNRemove(loctestnum, loctesterr, coplst, true, 41);
    coplst = std::move(lst);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 57);
    FoldPreOrder(loctestnum, loctesterr, coplst, true, &FoldAdd<int>, 0, 98);

    lasd::List<int> movlst(std::move(lst));
    MapPreOrder(loctestnum, loctesterr, movlst, true, &MapIncrement<int>);
    FoldPreOrder(loctestnum, loctesterr, movlst, true, &FoldAdd<int>, 0, 60);

    InsertC(loctestnum, loctesterr, movlst, true, 60);
    InsertC(loctestnum, loctesterr, movlst, true, 80);
    Remove(loctestnum, loctesterr, movlst, true, 60);
    InsertC(loctestnum, loctesterr, movlst, true, 70);
    FoldPreOrder(loctestnum, loctesterr, movlst, true, &FoldAdd<int>, 1, 211);

    movlst.Clear();
    Empty(loctestnum, loctesterr, movlst, true);
    Size(loctestnum, loctesterr, movlst, true, 0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  cout << "Fine del test List<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestListDouble(unsigned int & testnum, unsigned int & testerr) {
   unsigned int loctestnum = 0, loctesterr = 0;
   cout << endl << "Inizio del test List<double>:" << endl;
   try {
     lasd::List<double> lst;
     Empty(loctestnum, loctesterr, lst, true);
     Size(loctestnum, loctesterr, lst, true, 0);

     InsertAtBack(loctestnum, loctesterr, lst, true, -4.5);
     InsertAtBack(loctestnum, loctesterr, lst, true, 4.5);

     lst.Clear();

     InsertAtBack(loctestnum, loctesterr, lst, true, 40.0);
     InsertAtFront(loctestnum, loctesterr, lst, true, 30.0);
     InsertAtFront(loctestnum, loctesterr, lst, true, 20.0);
     InsertAtBack(loctestnum, loctesterr, lst, true, 10.0);

     GetFront(loctestnum, loctesterr, lst, true, 20.0);
     GetBack(loctestnum, loctesterr, lst, true, 10.0);

     Exists(loctestnum, loctesterr, lst, false, 0.0);

     TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
     TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
     FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<double>, 0.0, 100.0);
     FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<double>, 1.0, 240000.0);
   }
   catch (...) {
     loctestnum++; loctesterr++;
     cout << endl << "Errore non gestito! " << endl;
   }
   cout << "Fine del test List<double> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
   testnum += loctestnum;
   testerr += loctesterr;
 }

/* ************************************************************************** */


 void mytestListString(unsigned int &testnum, unsigned int &testerr) {
   unsigned int loctestnum = 0, loctesterr = 0;
   cout << endl << "Inizio del test List<string>:" << endl;
   try {
     lasd::List<string> lst;
     Empty(loctestnum, loctesterr, lst, true);
     Size(loctestnum, loctesterr, lst, true, 0);

     InsertAtFront(loctestnum, loctesterr, lst, true, string("X"));
     InsertAtBack(loctestnum, loctesterr, lst, true, string("Y"));

     GetFront(loctestnum, loctesterr, lst, true, string("X"));
     GetBack(loctestnum, loctesterr, lst, true, string("Y"));

     Exists(loctestnum, loctesterr, lst, true, string("Y"));

     MapPreOrder(loctestnum, loctesterr, lst, true, [](string & str) { MapStringAppend(str, string(" ")); });
     TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
     FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("X"), string("XX Y "));
     FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("X"), string("XY X "));

     Exists(loctestnum, loctesterr, lst, false, string("Y"));

     lasd::List<string> coplst(lst);
     EqualList(loctestnum, loctesterr, lst, coplst, true);
     RemoveFromFront(loctestnum, loctesterr, coplst, true);
     NonEqualList(loctestnum, loctesterr, lst, coplst, true);

     lst = coplst;
     EqualList(loctestnum, loctesterr, lst, coplst, true);
     InsertAtBack(loctestnum, loctesterr, lst, true, string("C"));
     InsertAtFront(loctestnum, loctesterr, lst, true, string("A"));
     NonEqualList(loctestnum, loctesterr, lst, coplst, true);

     coplst = std::move(lst);
     FoldPreOrder(loctestnum, loctesterr, coplst, true, &FoldStringConcatenate, string("?"), string("?AY C"));
   }
   catch (...) {
     loctestnum++; loctesterr++;
     cout << endl << "Errore non gestito! " << endl;
   }
   cout << "Fine del test List<string> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
   testnum += loctestnum;
   testerr += loctesterr;
 }

/* ************************************************************************** */

void mytestVectorListInt(unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio del test Vector/List<int>:" << endl;
  try {
    lasd::SortableVector<int> vec(3);
    SetAt(loctestnum, loctesterr, vec, true, 0, 10);  
    SetAt(loctestnum, loctesterr, vec, true, 1, 20);  
    SetAt(loctestnum, loctesterr, vec, true, 2, 30);  

    lasd::List<int> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, 30);
    InsertAtFront(loctestnum, loctesterr, lst, true, 20);  
    InsertAtFront(loctestnum, loctesterr, lst, true, 10);  

    EqualLinear(loctestnum, loctesterr, vec, lst, true);

    lasd::SortableVector<int> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    lasd::SortableVector<int> copvecx(vec);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    lasd::List<int> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    lasd::List<int> coplstx(lst);
    EqualList(loctestnum, loctesterr, coplstx, coplst, true);
  }
  catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  cout << "Fine del test Vector/List<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestVectorListDouble(unsigned int & testnum, unsigned int & testerr) {
   unsigned int loctestnum = 0, loctesterr = 0;
   cout << endl << "Inizio del test Vector/List<double>:" << endl;
   try {
     lasd::SortableVector<double> vec(3);
     SetAt(loctestnum, loctesterr, vec, true, 0, 10.0);
     SetAt(loctestnum, loctesterr, vec, true, 1, 20.0);
     SetAt(loctestnum, loctesterr, vec, true, 2, 30.5);

     lasd::List<double> lst;
     InsertAtBack(loctestnum, loctesterr, lst, true, 10.0);
     InsertAtBack(loctestnum, loctesterr, lst, true, 20.0);
     InsertAtBack(loctestnum, loctesterr, lst, true, 30.5);

     EqualLinear(loctestnum, loctesterr, vec, lst, true);

     lasd::SortableVector<double> copvec(lst);
     EqualVector(loctestnum, loctesterr, vec, copvec, true);
     lasd::SortableVector<double> copvecx(vec);
     EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

     lasd::List<double> coplst(vec);
     EqualList(loctestnum, loctesterr, lst, coplst, true);
     lasd::List<double> coplstx(lst);
     EqualList(loctestnum, loctesterr, coplstx, coplst, true);
   }
   catch (...) {
     loctestnum++; loctesterr++;
     cout << endl << "Errore non gestito! " << endl;
   }
   cout << "Fine del test Vector/List<double> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
   testnum += loctestnum;
   testerr += loctesterr;
 }

/* ************************************************************************** */

void mytestVectorListString(unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio del test Vector/List<string>:" << endl;
  try {
    lasd::SortableVector<string> vec(3);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("X"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("Y"));
    SetAt(loctestnum, loctesterr, vec, true, 2, string("Z"));

    lasd::List<string> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, string("Y"));  
    InsertAtBack(loctestnum, loctesterr, lst, true, string("Z"));  
    InsertAtFront(loctestnum, loctesterr, lst, true, string("X"));  

    EqualLinear(loctestnum, loctesterr, vec, lst, true);

    lasd::SortableVector<string> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    lasd::SortableVector<string> copvecx(vec);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    lasd::List<string> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    lasd::List<string> coplstx(lst);
    EqualList(loctestnum, loctesterr, coplstx, coplst, true);

    lasd::List<string> coplsty(std::move(vec));
    EqualList(loctestnum, loctesterr, coplst, coplsty, true);
    EqualVector(loctestnum, loctesterr, vec, copvec, false);

    lasd::SortableVector<string> copvecy(std::move(lst));
    EqualVector(loctestnum, loctesterr, copvec, copvecy, true);
    EqualList(loctestnum, loctesterr, lst, coplst, false);
  }
  catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  cout << "Fine del test Vector/List<string> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Stk>
void mytestStackInt(Stk &stk, unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  try {
    Empty(loctestnum, loctesterr, stk, true);
    Size(loctestnum, loctesterr, stk, true, 0);

    Top(loctestnum, loctesterr, stk, false, 0);
    TopNPop(loctestnum, loctesterr, stk, false, 0);

    PushC(loctestnum, loctesterr, stk, 10);
    PushC(loctestnum, loctesterr, stk, 20);
    PushC(loctestnum, loctesterr, stk, 30);
    PushC(loctestnum, loctesterr, stk, 40);
    PushC(loctestnum, loctesterr, stk, 50);

    Empty(loctestnum, loctesterr, stk, false);
    Size(loctestnum, loctesterr, stk, true, 5);

    TopNPop(loctestnum, loctesterr, stk, true, 50);
    Top(loctestnum, loctesterr, stk, true, 40);
    Top(loctestnum, loctesterr, (const Stk)stk, true, 40);

    Stk copstk(stk);
    EqualStack(loctestnum, loctesterr, stk, copstk, true);
    PushC(loctestnum, loctesterr, stk, 55);
    NonEqualStack(loctestnum, loctesterr, stk, copstk, true);

    copstk = stk;
    EqualStack(loctestnum, loctesterr, stk, copstk, true);
    PushC(loctestnum, loctesterr, copstk, 66);
    NonEqualStack(loctestnum, loctesterr, stk, copstk, true);

    Top(loctestnum, loctesterr, copstk, true, 66);
    copstk = std::move(stk);
    TopNPop(loctestnum, loctesterr, copstk, true, 55);
    Pop(loctestnum, loctesterr, copstk, true);
    Top(loctestnum, loctesterr, copstk, true, 30);

    Stk movstk(std::move(stk));
    Top(loctestnum, loctesterr, stk, false, 0);

    movstk.Clear();
    Pop(loctestnum, loctesterr, movstk, false);
    Empty(loctestnum, loctesterr, movstk, true);
    Size(loctestnum, loctesterr, movstk, true, 0);
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "Fine del test Stack<int> (Errors/Tests: " << loctesterr << "/"
       << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void mytestStackInt(unsigned int &testnum, unsigned int &testerr)
{
  unsigned int loctestnum = 0, loctesterr = 0;
  lasd::StackVec<int> stkvec;
  cout << endl
       << "Inizio del test StackVec<int>:" << endl;
  mytestStackInt(stkvec, loctestnum, loctesterr);
  lasd::StackLst<int> stklst;
  cout << endl
       << "Inizio del test StackLst<int>:" << endl;
  mytestStackInt(stklst, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Stk>
void mytestStackFloat(Stk &stk, unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  try {
    PushC(loctestnum, loctesterr, stk, 10.0);
    PushC(loctestnum, loctesterr, stk, 20.0);
    PushC(loctestnum, loctesterr, stk, 30.0);

    Empty(loctestnum, loctesterr, stk, false);
    Size(loctestnum, loctesterr, stk, true, 3);

    TopNPop(loctestnum, loctesterr, stk, true, 30.0);
    Top(loctestnum, loctesterr, stk, true, 20.0);
    Pop(loctestnum, loctesterr, stk, true);
    TopNPop(loctestnum, loctesterr, stk, true, 10.0);
    Pop(loctestnum, loctesterr, stk, false);
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "Fine del test Stack<double> (Errors/Tests: " << loctesterr << "/"
       << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void mytestStackFloat(unsigned int &testnum, unsigned int &testerr)
{
  unsigned int loctestnum = 0, loctesterr = 0;
  lasd::StackVec<double> stkvec;
  cout << endl
       << "Inizio del test StackVec<double>:" << endl;
  mytestStackFloat(stkvec, loctestnum, loctesterr);
  lasd::StackLst<double> stklst;
  cout << endl
       << "Inizio del test StackLst<double>:" << endl;
  mytestStackFloat(stklst, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Stk>
void mytestStackString(Stk &stk, unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  try {
    PushM(loctestnum, loctesterr, stk, string("X"));
    PushM(loctestnum, loctesterr, stk, string("Y"));

    Empty(loctestnum, loctesterr, stk, false);
    Size(loctestnum, loctesterr, stk, true, 2);

    TopNPop(loctestnum, loctesterr, stk, true, string("Y"));
    Top(loctestnum, loctesterr, stk, true, string("X"));
    Pop(loctestnum, loctesterr, stk, true);
    Pop(loctestnum, loctesterr, stk, false);
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "Fine del test Stack<string> (Errors/Tests: " << loctesterr << "/"
       << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void mytestStackString(unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  lasd::StackVec<string> stkvec;
  cout << endl << "Inizio del test StackVec<string>:" << endl;
  mytestStackString(stkvec, loctestnum, loctesterr);
  lasd::StackLst<string> stklst;
  cout << endl << "Inizio del test StackLst<string>:" << endl;
  mytestStackString(stklst, loctestnum, loctesterr);
  cout << endl;
  try {
    lasd::Vector<string> vec(2);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("X"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("Y"));

    PushM(loctestnum, loctesterr, stkvec, string("X"));
    PushM(loctestnum, loctesterr, stkvec, string("Y"));
    lasd::StackVec<string> newstkvec(vec);
    EqualStack(loctestnum, loctesterr, stkvec, newstkvec, true);

    PushM(loctestnum, loctesterr, stklst, string("Y"));
    PushM(loctestnum, loctesterr, stklst, string("X"));
    lasd::StackLst<string> newstklst(vec);
    EqualStack(loctestnum, loctesterr, stklst, newstklst, true);
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Que>
void mytestQueueInt(Que &que, unsigned int &testnum, unsigned int &testerr)
{
  unsigned int loctestnum = 0, loctesterr = 0;
  try
  {
    Empty(loctestnum, loctesterr, que, true);
    Size(loctestnum, loctesterr, que, true, 0);

    Head(loctestnum, loctesterr, que, false, 0);
    HeadNDequeue(loctestnum, loctesterr, que, false, 0);

    EnqueueC(loctestnum, loctesterr, que, 10);
    EnqueueC(loctestnum, loctesterr, que, 20);
    EnqueueC(loctestnum, loctesterr, que, 30);
    EnqueueC(loctestnum, loctesterr, que, 40);
    EnqueueC(loctestnum, loctesterr, que, 50);

    Empty(loctestnum, loctesterr, que, false);
    Size(loctestnum, loctesterr, que, true, 5);

    HeadNDequeue(loctestnum, loctesterr, que, true, 10);
    Head(loctestnum, loctesterr, que, true, 20);
    Head(loctestnum, loctesterr, (const Que)que, true, 20);

    Que copque(que);
    EqualQueue(loctestnum, loctesterr, que, copque, true);
    EnqueueC(loctestnum, loctesterr, que, 55);
    NonEqualQueue(loctestnum, loctesterr, que, copque, true);

    copque = que;
    EqualQueue(loctestnum, loctesterr, que, copque, true);
    EnqueueC(loctestnum, loctesterr, copque, 66);
    NonEqualQueue(loctestnum, loctesterr, que, copque, true);

    Head(loctestnum, loctesterr, copque, true, 20);
    copque = std::move(que);
    HeadNDequeue(loctestnum, loctesterr, copque, true, 20);
    Dequeue(loctestnum, loctesterr, copque, true);
    Head(loctestnum, loctesterr, copque, true, 40);

    Que movque(std::move(que));
    Head(loctestnum, loctesterr, que, false, 0);

    movque.Clear();
    Dequeue(loctestnum, loctesterr, movque, false);
    Empty(loctestnum, loctesterr, movque, true);
    Size(loctestnum, loctesterr, movque, true, 0);
  }
  catch (...)
  {
    loctestnum++;
     loctesterr++;
     cout << endl
          << "Errore non gestito! " << endl;
   }
   testnum += loctestnum;
   testerr += loctesterr;
   cout << "Fine del test Queue<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
 }

 /* ************************************************************************** */

 void mytestQueueInt(unsigned int &testnum, unsigned int &testerr)
 {
   unsigned int loctestnum = 0, loctesterr = 0;
   lasd::QueueVec<int> quevec;
   cout << endl
        << "Inizio del test QueueVec<int>:" << endl;
   mytestQueueInt(quevec, loctestnum, loctesterr);
   lasd::QueueLst<int> quelst;
   cout << endl
        << "Inizio del test QueueLst<int>:" << endl;
   mytestQueueInt(quelst, loctestnum, loctesterr);
   testnum += loctestnum;
   testerr += loctesterr;
 }

template <typename Que>
void mytestQueueFloat(Que &que, unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  try {
    EnqueueC(loctestnum, loctesterr, que, 10.0);
    EnqueueC(loctestnum, loctesterr, que, 20.0);
    EnqueueC(loctestnum, loctesterr, que, 30.0);

    Empty(loctestnum, loctesterr, que, false);
    Size(loctestnum, loctesterr, que, true, 3);

    HeadNDequeue(loctestnum, loctesterr, que, true, 10.0);
    Head(loctestnum, loctesterr, que, true, 20.0);
    Dequeue(loctestnum, loctesterr, que, true);
    HeadNDequeue(loctestnum, loctesterr, que, true, 30.0);
    Dequeue(loctestnum, loctesterr, que, false);
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "Fine del test Queue<double> (Errors/Tests: " << loctesterr << "/"
       << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void mytestQueueFloat(unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  lasd::QueueVec<double> quevec;
  cout << endl << "Inizio del test QueueVec<double>:" << endl;
  mytestQueueFloat(quevec, loctestnum, loctesterr);
  lasd::QueueLst<double> quelst;
  cout << endl << "Inizio del test QueueLst<double>:" << endl;
  mytestQueueFloat(quelst, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Que>
void mytestQueueString(Que &que, unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  try {
    EnqueueM(loctestnum, loctesterr, que, string("X"));
    EnqueueM(loctestnum, loctesterr, que, string("Y"));

    Empty(loctestnum, loctesterr, que, false);
    Size(loctestnum, loctesterr, que, true, 2);

    HeadNDequeue(loctestnum, loctesterr, que, true, string("X"));
    Head(loctestnum, loctesterr, que, true, string("Y"));
    Dequeue(loctestnum, loctesterr, que, true);
    Dequeue(loctestnum, loctesterr, que, false);
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "Fine del test Queue<string> (Errors/Tests: " << loctesterr << "/"
       << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void mytestQueueString(unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  lasd::QueueVec<string> quevec;
  cout << endl << "Inizio del test QueueVec<string>:" << endl;
  mytestQueueString(quevec, loctestnum, loctesterr);
  lasd::QueueLst<string> quelst;
  cout << endl << "Inizio del test QueueLst<string>:" << endl;
  mytestQueueString(quelst, loctestnum, loctesterr);
  cout << endl;
  try {
    lasd::Vector<string> vec(2);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("X"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("Y"));

    EnqueueM(loctestnum, loctesterr, quevec, string("X"));
    EnqueueM(loctestnum, loctesterr, quevec, string("Y"));
    lasd::QueueVec<string> newquevec(vec);
    EqualQueue(loctestnum, loctesterr, quevec, newquevec, true);

    EnqueueM(loctestnum, loctesterr, quelst, string("X"));
    EnqueueM(loctestnum, loctesterr, quelst, string("Y"));
    lasd::QueueLst<string> newquelst(vec);
    EqualQueue(loctestnum, loctesterr, quelst, newquelst, true);
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestEmptyBinaryTreeInt(uint & testnum, uint & testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio Test Empty BinaryTree<int>" << endl;
  try {
    lasd::Vector<int> vec(0);

    // Crea un albero binario vuoto di interi
    lasd::BinaryTreeVec<int> btvec(vec);
    // Verifica se la funzione Empty funziona correttamente
    Empty(loctestnum, loctesterr, btvec, true);
    Size(loctestnum, loctesterr, vec, true, 0);

  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  cout << "Fine Test BinaryTree<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestEmptyBinaryTreeFloat(uint & testnum, uint & testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio Test Empty BinaryTree<double>" << endl;
  try {
    lasd::Vector<double> vec(0.0);

    // Crea un albero binario vuoto di interi
    lasd::BinaryTreeVec<double> btvec(vec);
    // Verifica se la funzione Empty funziona correttamente
    Empty(loctestnum, loctesterr, btvec, true);
    Size(loctestnum, loctesterr, vec, true, 0.0);

  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  cout << "Fine Test BinaryTree<double> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestRicercaBinaryTreeInt(uint& testnum, uint& testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio Test Ricerca BinaryTree<int>" << endl;
  try {
    lasd::Vector<int> vec(4);
    SetAt(loctestnum, loctesterr, vec, true, 0, 1);
    SetAt(loctestnum, loctesterr, vec, true, 1, 2);
    SetAt(loctestnum, loctesterr, vec, true, 2, 3);
    SetAt(loctestnum, loctesterr, vec, true, 3, 4);

    lasd::BinaryTreeVec<int> btvec(vec);

    // Cerca un elemento presente
    bool trovato = false;
    TraversePreOrder(loctestnum, loctesterr, vec, true, [&trovato](int val) {
      if (val == 3) {
        trovato = true;
      }
    });
    if (!trovato) {
      loctesterr++;
      cout << "Errore: Elemento presente non trovato durante la traversata." << endl;
    }

    // Cerca un elemento non presente
    trovato = false;
    TraversePostOrder(loctestnum, loctesterr, vec, true, [&trovato](int val) {
      if (val == 10) {
        trovato = true;
      }
    });
    if (trovato) {
      loctesterr++;
      cout << "Errore: Elemento non presente trovato durante la traversata." << endl;
    }

  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore imprevisto!" << endl;
  }
  cout << "Fine Test Ricerca BinaryTree! (Errors/Test: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestRicercaBinaryTreeFloat(uint& testnum, uint& testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio Test Ricerca BinaryTree<double>" << endl;
  try {
    lasd::Vector<double> vec(4);
    SetAt(loctestnum, loctesterr, vec, true, 0, 1.0);
    SetAt(loctestnum, loctesterr, vec, true, 1, 2.0);
    SetAt(loctestnum, loctesterr, vec, true, 2, 3.0);
    SetAt(loctestnum, loctesterr, vec, true, 3, 4.0);

    lasd::BinaryTreeVec<double> btvec(vec);

    // Cerca un elemento presente
    bool trovato = false;
    TraversePreOrder(loctestnum, loctesterr, vec, true, [&trovato](int val) {
      if (val == 3.0) {
        trovato = true;
      }
    });
    if (!trovato) {
      loctesterr++;
      cout << "Errore: Elemento presente non trovato durante la traversata." << endl;
    }

    // Cerca un elemento non presente
    trovato = false;
    TraversePostOrder(loctestnum, loctesterr, vec, true, [&trovato](int val) {
      if (val == 10.0) {
        trovato = true;
      }
    });
    if (trovato) {
      loctesterr++;
      cout << "Errore: Elemento non presente trovato durante la traversata." << endl;
    }

  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore imprevisto!" << endl;
  }
  cout << "Fine Test Ricerca BinaryTree<double>! (Errors/Test: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestRicercaBinaryTreeString(uint& testnum, uint& testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  try {
    cout << endl << "Inizio Test Ricerca BinaryTree<string>" << endl;
    lasd::Vector<string> vec(4);

    SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("B"));
    SetAt(loctestnum, loctesterr, vec, true, 2, string("C"));
    SetAt(loctestnum, loctesterr, vec, true, 3, string("D"));

    lasd::BinaryTreeVec<string> btvec(vec);

    // Cerca un elemento presente
    bool trovato = false;
    TraversePreOrder(loctestnum, loctesterr, vec, true, [&trovato](string val) {
      if (val == "C") {
        trovato = true;
      }
    });
    if (!trovato) {
      loctesterr++;
      cout << "Errore: Elemento presente non trovato durante la traversata." << endl;
    }

    // Cerca un elemento non presente
    trovato = false;
    TraversePostOrder(loctestnum, loctesterr, vec, true, [&trovato](string val) {
      if (val == "E") {
        trovato = true;
      }
    });
    if (trovato) {
      loctesterr++;
      cout << "Errore: Elemento non presente trovato durante la traversata." << endl;
    }

  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore imprevisto!" << endl;
  }
  cout << "Fine Test Ricerca BinaryTree<string>! (Errors/Test: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestCopyBinaryTreeVecInt(uint & testnum, uint & testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;

  cout << endl << "Inizio Test BinaryTree<int> Copy " << endl;

  try {
    // Creazione del Vector<int> per inizializzare l'albero binario
    lasd::Vector<int> vec(4);

    // Inizializzazione del Vector<int> con valori
    SetAt(loctestnum, loctesterr, vec, true, 0, 1);
    SetAt(loctestnum, loctesterr, vec, true, 1, 2);
    SetAt(loctestnum, loctesterr, vec, true, 2, 3);
    SetAt(loctestnum, loctesterr, vec, true, 3, 4);

    // Creazione dell'albero binario utilizzando il Vector<int> inizializzato
    lasd::BinaryTreeVec<int> btvec(vec);
    // Creazione di una copia dell'albero binario appena creato
    lasd::BinaryTreeVec<int> copyBtVec(btvec);
    // Modifica l'elemento del nodo a destra del nodo radice nell'albero originale
    btvec.Root().RightChild().Element() = 10;

    // Controllo se la modifica dell'elemento nell'albero originale si è riflessa nella copia
    if (btvec.Root().RightChild().Element() == copyBtVec.Root().RightChild().Element()) {
      // Se i due elementi sono uguali, viene segnalato un errore di copia non profonda
      loctestnum++;
      loctesterr++;
      cout << "Errore: BinaryTree copiato non è una copia profonda." << endl;
    }
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << "Errore imprevisto!" << endl;
  }

  cout << "Fine Test BinaryTree<int> Copy (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;

  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestCopyBinaryTreeVecFloat(uint & testnum, uint & testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;

  cout << endl << "Inizio Test BinaryTree<double> Copy " << endl;

  try {
    // Creazione del Vector<int> per inizializzare l'albero binario
    lasd::Vector<double> vec(4);

    // Inizializzazione del Vector<int> con valori
    SetAt(loctestnum, loctesterr, vec, true, 0, 1.0);
    SetAt(loctestnum, loctesterr, vec, true, 1, 2.0);
    SetAt(loctestnum, loctesterr, vec, true, 2, 3.0);
    SetAt(loctestnum, loctesterr, vec, true, 3, 4.0);

    // Creazione dell'albero binario utilizzando il Vector<int> inizializzato
    lasd::BinaryTreeVec<double> btvec(vec);
    // Creazione di una copia dell'albero binario appena creato
    lasd::BinaryTreeVec<double> copyBtVec(btvec);
    // Modifica l'elemento del nodo a destra del nodo radice nell'albero originale
    btvec.Root().RightChild().Element() = 10.0;

    // Controllo se la modifica dell'elemento nell'albero originale si è riflessa nella copia
    if (btvec.Root().RightChild().Element() == copyBtVec.Root().RightChild().Element()) {
      // Se i due elementi sono uguali, viene segnalato un errore di copia non profonda
      loctestnum++;
      loctesterr++;
      cout << "Errore: BinaryTree copiato non è una copia profonda." << endl;
    }
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << "Errore imprevisto!" << endl;
  }

  cout << "Fine Test BinaryTree<double> Copy (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;

  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestBSTInt(uint & testnum, uint & testerr) {
  // Contatori locali per il numero di test e errori all'interno di questa funzione
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio Test BST<int> Test" << endl;

  try {
    // Creazione di un albero di ricerca binario vuoto di interi
    lasd::BST<int> bst;

    // Verifica se l'albero è inizialmente vuoto e la sua dimensione è 0
    Empty(loctestnum, loctesterr, bst, true);
    Size(loctestnum, loctesterr, bst, true, 0);

    // Tentativo di trovare il minimo e il massimo nell'albero vuoto (dovrebbe restituire false)
    Min(loctestnum, loctesterr, bst, false, 0);
    Max(loctestnum, loctesterr, bst, false, 0);

    // Inserimento di elementi nel BST
    InsertC(loctestnum, loctesterr, bst, true, 2);
    InsertC(loctestnum, loctesterr, bst, true, 1);
    InsertC(loctestnum, loctesterr, bst, true, 3);
    InsertC(loctestnum, loctesterr, bst, true, 4);
    InsertC(loctestnum, loctesterr, bst, true, 0);
   
    // Verifica se l'albero non è vuoto e la sua dimensione è corretta
    Empty(loctestnum, loctesterr, bst, false);
    Size(loctestnum, loctesterr, bst, true, 5);

    // Attraversamento dell'albero in ordine e stampa degli elementi
    TraverseInOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);

    // Verifica i valori minimo e massimo nell'albero
    Min(loctestnum, loctesterr, bst, true, 0);
    Max(loctestnum, loctesterr, bst, true, 4);

    // Verifica il valore della radice
    Root(loctestnum, loctesterr, bst, true, 2);

    // Rimuove l'elemento minimo e verifica il nuovo minimo
    RemoveMin(loctestnum, loctesterr, bst, true);
    MinNRemove(loctestnum, loctesterr, bst, true, 1);

    // Inserisce ulteriori elementi e verifica i valori minimo e massimo
    InsertC(loctestnum, loctesterr, bst, true, -1);
    InsertC(loctestnum, loctesterr, bst, true, 1);
    Min(loctestnum, loctesterr, bst, true, -1);
    MaxNRemove(loctestnum, loctesterr, bst, true, 4);
    Size(loctestnum, loctesterr, bst, true, 4);

    // Inserisce un elemento e verifica la dimensione
    InsertC(loctestnum, loctesterr, bst, true, 6);
    Size(loctestnum, loctesterr, bst, true, 5);
    Max(loctestnum, loctesterr, bst, true, 6);

    // Inserisce un altro elemento e verifica la dimensione
    InsertC(loctestnum, loctesterr, bst, true, 7);
    Size(loctestnum, loctesterr, bst, true, 6);

    // Verifica l'esistenza di determinati elementi
    Exists(loctestnum, loctesterr, bst, true, 6);
    Exists(loctestnum, loctesterr, bst, false, 8);
    Exists(loctestnum, loctesterr, bst, false, 0);
    Exists(loctestnum, loctesterr, bst, true, -1);
    Exists(loctestnum, loctesterr, bst, true, 2);

    // Rimuove gli elementi e verifica la loro esistenza
    Remove(loctestnum, loctesterr, bst, false, 5);
    Remove(loctestnum, loctesterr, bst, true, 2);
    Exists(loctestnum, loctesterr, bst, false, 5);
    Exists(loctestnum, loctesterr, bst, false, 2);

    // Rimuove l'elemento massimo e verifica il nuovo massimo
    RemoveMax(loctestnum, loctesterr, bst, true);
    Max(loctestnum, loctesterr, bst, true, 6);

    // Attraversa di nuovo l'albero in ordine
    TraverseInOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);

    // Verifica i predecessori e i successori
    Predecessor(loctestnum, loctesterr, bst, true, 4, 3);
    Predecessor(loctestnum, loctesterr, bst, true, 5, 3);
    Successor(loctestnum, loctesterr, bst, true, 2, 3);
    Successor(loctestnum, loctesterr, bst, true, 4, 6);

    // Rimuove predecessori e successori
    PredecessorNRemove(loctestnum, loctesterr, bst, true, 7, 6);
    SuccessorNRemove(loctestnum, loctesterr, bst, true, 0, 1);

    // Esegue operazioni di fold
    FoldPreOrder(loctestnum, loctesterr, bst, true, &FoldAdd<int>, 0, 2);
    FoldInOrder(loctestnum, loctesterr, bst, true, &FoldAdd<int>, 0, 2);
    FoldPostOrder(loctestnum, loctesterr, bst, true, &FoldAdd<int>, 0, 2);
    FoldBreadth(loctestnum, loctesterr, bst, true, &FoldAdd<int>, 0, 2);

    // Crea una copia dell'albero e li confronta
    lasd::BST<int> bst1(bst);
    EqualBST(loctestnum, loctesterr, bst, bst1);
    Remove(loctestnum, loctesterr, bst1, true, 3);
    NonEqualBST(loctestnum, loctesterr, bst, bst1);
    InsertC(loctestnum, loctesterr, bst1, true, 3);
    EqualBST(loctestnum, loctesterr, bst, bst1);

    // Assegna una copia dell'albero e li confronta
    lasd::BST<int> bst2 = bst1;
    EqualBST(loctestnum, loctesterr, bst1, bst2);
    RemovePredecessor(loctestnum, loctesterr, bst1, true, 9);
    NonEqualBST(loctestnum, loctesterr, bst1, bst2);

    // Costruttore di movimento e assegnazioni
    lasd::BST<int> bst3(std::move(bst2));
    Empty(loctestnum, loctesterr, bst2, true);
    Size(loctestnum, loctesterr, bst2, true, 0);
    Empty(loctestnum, loctesterr, bst3, false);
    Size(loctestnum, loctesterr, bst3, true, 2);
    bst2 = std::move(bst1);
    Empty(loctestnum, loctesterr, bst1, true);
    Size(loctestnum, loctesterr, bst1, true, 0);
    Empty(loctestnum, loctesterr, bst2, false);
    Size(loctestnum, loctesterr, bst2, true, 1);
    NonEqualBST(loctestnum, loctesterr, bst3, bst2);

    // Attraversa di nuovo l'albero in ordine
    TraverseInOrder(loctestnum, loctesterr, bst2, true, &TraversePrint<int>);
    TraverseInOrder(loctestnum, loctesterr, bst3, true, &TraversePrint<int>);

    // Inserisce un elemento e confronta gli alberi
    InsertC(loctestnum, loctesterr, bst2, true, 3);
    EqualBST(loctestnum, loctesterr, bst3, bst2);

    // Svuota l'albero originale e verifica
    bst.Clear();
    Empty(loctestnum, loctesterr, bst, true);
    Size(loctestnum, loctesterr, bst, true, 0);
  }
  catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore Imprevisto! " << endl;
  }
  cout << "Fine Test BST<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestBSTFindPointerToMaxAndToMinInt(uint &testnum, uint &testerr) {
    uint loctestnum = 0, loctesterr = 0;
    std::cout << std::endl << "Inizio Test BSTFindPointerToMaxAndToMin<int> Test" << std::endl;

    try {
        // Crea un albero di ricerca binario (BST) con alcuni valori
        lasd::BST<int> bst;
        bst.Insert(10);
        bst.Insert(5);
        bst.Insert(3);
        bst.Insert(7);
        bst.Insert(12);
        bst.Insert(17);

    Max(loctestnum,loctesterr,bst,true,17);
    Min(loctestnum,loctesterr,bst,true,3);

    Remove(loctestnum, loctesterr, bst, true, 17);
    Remove(loctestnum, loctesterr, bst, true, 3);

    Max(loctestnum,loctesterr,bst,true,12);
    Min(loctestnum,loctesterr,bst,true,5);

    } catch (...) {
        loctestnum++;
        loctesterr++;
        std::cout << std::endl << "Errore Imprevisto!" << std::endl;
    }

    std::cout << "Fine Test Test BSTFindPointerToMaxAndToMin<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void mytestBSTFindPointerToMaxAndToMinFloat(uint &testnum, uint &testerr) {
    uint loctestnum = 0, loctesterr = 0;
    std::cout << std::endl << "Inizio Test BSTFindPointerToMaxAndToMin<double> Test" << std::endl;

    try {
        // Crea un albero di ricerca binario (BST) con alcuni valori
        lasd::BST<double> bst;
        bst.Insert(10.0);
        bst.Insert(5.0);
        bst.Insert(3.0);
        bst.Insert(7.0);
        bst.Insert(12.0);
        bst.Insert(17.0);

    Max(loctestnum,loctesterr,bst,true,17.0);
    Min(loctestnum,loctesterr,bst,true,3.0);

    Remove(loctestnum, loctesterr, bst, true, 17.0);
    Remove(loctestnum, loctesterr, bst, true, 3.0);

    Max(loctestnum,loctesterr,bst,true,12.0);
    Min(loctestnum,loctesterr,bst,true,5.0);

    } catch (...) {
        loctestnum++;
        loctesterr++;
        std::cout << std::endl << "Errore Imprevisto!" << std::endl;
    }

    std::cout << "Fine Test Test BSTFindPointerToMaxAndToMin<double> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void myTestHashTableInt(lasd::HashTable<int> & ht, const lasd::LinearContainer<int> & con, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {
    lasd::Vector<int> vec(120);
    for (int i = 0; i < 120; ++i) {
      vec[i] = 3 * (i - 60);
    }
    Size(loctestnum, loctesterr, ht, true, 51);
    for (int i = 0; i < 120; i += 12) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    for (int i = 0; i < 120; i += 18) {
      Remove(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 45);
    for (int i = 0; i < 120; i += 18) {
      Exists(loctestnum, loctesterr, ht, false, con[i]);
    }
    CountHT(loctestnum, loctesterr, ht, vec, 3);
    for (int i = 0; i < 120; i += 15) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 48);
    for (int i = 0; i < 120; i += 25) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    CountHT(loctestnum, loctesterr, ht, vec, 3);
    for (int i = 0; i < 120; i += 20) {
      Remove(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 42);
    for (int i = 0; i < 120; i += 20) {
      Exists(loctestnum, loctesterr, ht, false, con[i]);
    }
    CountHT(loctestnum, loctesterr, ht, vec, 3);
    for (int i = 0; i < 120; i += 10) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 48);
    for (int i = 0; i < 120; i += 10) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    CountHT(loctestnum, loctesterr, ht, vec, 3);
    ht.Resize(2500);
    for (int i = 0; i < 120; i += 20) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    ht.Resize(4500);
    Size(loctestnum, loctesterr, ht, true, 48);
    ht.Resize(80);
    CountHT(loctestnum, loctesterr, ht, vec, 3);
    Empty(loctestnum, loctesterr, ht, false);
    ht.Clear();
    Empty(loctestnum, loctesterr, ht, true);
    Size(loctestnum, loctesterr, ht, true, 0);
    InsertC(loctestnum, loctesterr, ht, con);
    Empty(loctestnum, loctesterr, ht, false);
    Size(loctestnum, loctesterr, ht, true, 51);
    CountHT(loctestnum, loctesterr, ht, vec, 3);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Errore Imprevisto! " << endl;
  }
  cout << "Fine Test HashTable<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void myTestHashTableInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio Test HashTable<int>" << endl;
  try {
    lasd::Vector<int> vec(150);
    for (uint i = 0; i < 150; i++) {
      vec[i] = pow(-3, i % 25) * ((70 * i + 31) % 150);
    }

    lasd::HashTableClsAdr<int> htclsadr(90, vec);
    cout << endl << "Inizio Test HashTableClsAdr<int>:" << endl;
    myTestHashTableInt(htclsadr, vec, loctestnum, loctesterr);
    lasd::HashTableOpnAdr<int> htopnadr(90, vec);
    cout << endl << "Inizio Test HashTableOpnAdr<int>:" << endl;
    myTestHashTableInt(htopnadr, vec, loctestnum, loctesterr);
    cout << "\n";

    lasd::HashTableClsAdr<int> cophtclsadr(htclsadr);
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr.Clear();
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr = std::move(cophtclsadr);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    cophtclsadr = htclsadr;
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);

    lasd::HashTableOpnAdr<int> cophtopnadr(htopnadr);
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr.Clear();
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr = std::move(cophtopnadr);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    cophtopnadr = htopnadr;
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Errore Imprevisto! " << endl;
  }
  cout << "Fine Test HashTable<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestHashTableFloat(lasd::HashTable<double> & ht, const lasd::LinearContainer<double> & con, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {
    Size(loctestnum, loctesterr, ht, true, 150);
    for (int i = 0; i < 150; i += 15) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    for (int i = 0; i < 150; i += 15) {
      Remove(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 140);
    for (int i = 0; i < 150; i += 15) {
      Exists(loctestnum, loctesterr, ht, false, con[i]);
    }
    for (int i = 0; i < 150; i += 8) {
      Remove(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 123);
    for (int i = 0; i < 150; i += 8) {
      Exists(loctestnum, loctesterr, ht, false, con[i]);
    }
    for (int i = 0; i < 150; i += 15) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 133);
    for (int i = 0; i < 150; i += 15) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    ht.Resize(4500);
    Size(loctestnum, loctesterr, ht, true, 133);
    ht.Resize(70);
    Size(loctestnum, loctesterr, ht, true, 133);
    for (int i = 0; i < 150; i += 8) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 150);
    for (int i = 0; i < 150; i += 8) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Errore Imprevisto! " << endl;
  }
  cout << "Fine Test HashTable<double> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void mytestHashTableFloat(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio Test HashTable<double>" << endl;
  try {
    lasd::List<double> lst;
    for (uint i = 0; i < 150; i++) {
      lst.InsertAtFront((pow(-2, i % 25) * ((70 * i + 31) % 150)) / (90 * pow(-3, i % 8)));
    }

    lasd::HashTableClsAdr<double> htclsadr(90, lst);
    cout << endl << "Inizio Test HashTableClsAdr<double>:" << endl;
    mytestHashTableFloat(htclsadr, lst, loctestnum, loctesterr);
    lasd::HashTableOpnAdr<double> htopnadr(90, lst);
    cout << endl << "Inizio Test HashTableOpnAdr<double>:" << endl;
    mytestHashTableFloat(htopnadr, lst, loctestnum, loctesterr);
    cout << "\n";

    lasd::HashTableClsAdr<double> cophtclsadr(htclsadr);
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr.Clear();
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr = std::move(cophtclsadr);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    cophtclsadr = htclsadr;
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);

    lasd::HashTableOpnAdr<double> cophtopnadr(htopnadr);
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr.Clear();
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr = std::move(cophtopnadr);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    cophtopnadr = htopnadr;
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Errore Imprevisto! " << endl;
  }
  cout << "Fine Test HashTable<double> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestHashTableString(lasd::HashTable<string> & ht, const lasd::LinearContainer<string> & con, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {
    Size(loctestnum, loctesterr, ht, true, 140);
    for (int i = 0; i < 140; i += 10) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    for (int i = 0; i < 140; i += 10) {
      Remove(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 126);
    for (int i = 0; i < 140; i += 10) {
      Exists(loctestnum, loctesterr, ht, false, con[i]);
    }
    for (int i = 0; i < 140; i += 14) {
      Remove(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 118);
    for (int i = 0; i < 140; i += 14) {
      Exists(loctestnum, loctesterr, ht, false, con[i]);
    }
    for (int i = 0; i < 140; i += 10) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 132);
    for (int i = 0; i < 140; i += 10) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    ht.Resize(3700);
    Size(loctestnum, loctesterr, ht, true, 132);
    ht.Resize(800);
    Size(loctestnum, loctesterr, ht, true, 132);
    for (int i = 0; i < 140; i += 14) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    for (int i = 0; i < 140; i += 14) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    ht.Resize(105);
    Size(loctestnum, loctesterr, ht, true, 140);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Errore Imprevisto! " << endl;
  }
  cout << "Fine Test HashTable<string> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void mytestHashTableString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio Test HashTable<string>" << endl;
  try {
    lasd::Vector<string> vec(140);
    vec[0] = "#";
    for (uint i = 1; i < 20; i++) {
      vec[i] = vec[i - 1] + static_cast<char>(33 + ((140 * i + 33) % 94));
    }
    for (uint i = 20; i < 140; i++) {
      vec[i] = vec[i - 1];
      vec[i][i % 20] = static_cast<char>(33 + ((140 * i + 33) % 94));
    }

    lasd::HashTableClsAdr<string> htclsadr(105, vec);
    cout << endl << "Inizio Test HashTableClsAdr<string>:" << endl;
    mytestHashTableString(htclsadr, vec, loctestnum, loctesterr);
    lasd::HashTableOpnAdr<string> htopnadr(105, vec);
    cout << endl << "Inizio Test HashTableOpnAdr<string>:" << endl;
    mytestHashTableString(htopnadr, vec, loctestnum, loctesterr);
    cout << "\n";

    lasd::HashTableClsAdr<string> cophtclsadr(htclsadr);
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr.Clear();
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr = std::move(cophtclsadr);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    cophtclsadr = htclsadr;
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);

    lasd::HashTableOpnAdr<string> cophtopnadr(htopnadr);
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr.Clear();
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr = std::move(cophtopnadr);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    cophtopnadr = htopnadr;
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Errore Imprevisto! " << endl;
  }
  cout << "Fine Test HashTable<string> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}


/* ************************************************************************** */

// Fase di test per gli esercizi 1
void eseguiTest1(unsigned int &testnum, unsigned int &testerr)
{
    // Esegue i test su vettori di interi, double e stringhe
    mytestVectorInt(testnum, testerr);
    mytestVectorDouble(testnum, testerr);
    mytestVectorString(testnum, testerr);

    // Esegue i test su liste di interi, double e stringhe
    mytestListInt(testnum, testerr);
    mytestListDouble(testnum, testerr);
    mytestListString(testnum, testerr);

    // Esegue i test su vettori di liste di interi, double e stringhe
    mytestVectorListInt(testnum, testerr);
    mytestVectorListDouble(testnum, testerr);
    mytestVectorListString(testnum, testerr);

    // Esegue i test su stack di interi, float e stringhe
    mytestStackInt(testnum, testerr);
    mytestStackFloat(testnum, testerr);
    mytestStackString(testnum, testerr);

    // Esegue i test su code di interi, float e stringhe
    mytestQueueInt(testnum, testerr);
    mytestQueueFloat(testnum, testerr);
    mytestQueueString(testnum, testerr);
 
}

/* ************************************************************************** */
// Fase di Test per gli esercizi 2
void eseguiTest2(unsigned int &testnum, unsigned int &testerr) {

  mytestEmptyBinaryTreeInt(testnum, testerr);  // Test per l'albero binario vuoto
  mytestEmptyBinaryTreeFloat(testnum,testerr); // Test per l'albero binario vuoto

  mytestRicercaBinaryTreeInt(testnum, testerr); // Test per la ricerca nell'albero binario<int>
  mytestRicercaBinaryTreeFloat(testnum, testerr); // Test per la ricerca nell'albero binario<double>
  mytestRicercaBinaryTreeString(testnum,testerr); // Test per la ricerca nell'albero binario<string>

  mytestCopyBinaryTreeVecInt(testnum, testerr); // Test per la copia dell'albero binario<int>
  mytestCopyBinaryTreeVecFloat(testnum,testerr); // Test per la copia dell'albero binario<double>

  mytestBSTInt(testnum,testerr); // Serie di test sull'albero di ricerca binario di interi (BST<int>)
  mytestBSTFindPointerToMaxAndToMinInt(testnum, testerr); //  Serie di test per trovare il puntatore al max e al min in un albero di ricerca binario<int>
  mytestBSTFindPointerToMaxAndToMinFloat(testnum,testerr); // Serie di test per trovare il puntatore al max e al min in un albero di ricerca binario<double>

}

/* ************************************************************************** */

void eseguiTest3(unsigned int &testnum, unsigned int &testerr) {

myTestHashTableInt(testnum, testerr);   //Test per Hashtable<int>
mytestHashTableFloat(testnum, testerr); //Test per Hashtable<double>
mytestHashTableString(testnum,testerr); //Test per Hashtable<string>

}
/* ************************************************************************** */

void mytest() {
  cout << endl
       << "~*~#~*~ Benvenuti nella suite di test LASD ~*~#~*~ " << endl;
  cout << endl << endl
       << "~*~#~*~ Test esercizio 1 LASD ~*~#~*~ " << endl;

  unsigned int loctestnum, loctesterr;
  unsigned int stestnum = 0, stesterr = 0;

  loctestnum = 0; loctesterr = 0;
  eseguiTest1(loctestnum, loctesterr);
  stestnum += loctestnum;
  stesterr += loctesterr;
  cout << endl
       << "Esercizio 1(myTest) (Errors/Tests: " << stesterr << "/" << stestnum << ")";

/* ************************************************************************** */

  cout << endl << endl
       << "~*~#~*~ Test esercizio 2 LASD ~*~#~*~ " << endl;

  loctestnum = 0; loctesterr = 0;
  stestnum = 0, stesterr = 0;
  eseguiTest2(loctestnum,loctesterr);
  stestnum += loctestnum;
  stesterr += loctesterr;
  cout << endl
       << "Esercizio 2(myTest) (Errors/Tests: " << stesterr << "/" << stestnum << ")";

/* ************************************************************************** */

cout << endl << endl
       << "~*~#~*~ Test esercizio 3 LASD ~*~#~*~ " << endl;

  loctestnum = 0; loctesterr = 0;
  stestnum = 0, stesterr = 0;
  eseguiTest3(loctestnum,loctesterr);
  stestnum += loctestnum;
  stesterr += loctesterr;
  cout << endl
       << "Esercizio 3(myTest) (Errors/Tests: " << stesterr << "/" << stestnum << ")";

       if (stesterr == 0)
  {
    cout << endl
         << endl
         << "#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ NESSUN PROBLEMA! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#" << endl;
  }
  cout << endl
       << "Arrivederci!" << endl;

}
