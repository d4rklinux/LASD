
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
// #include ...
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : virtual public HashTable<Data> { // Must extend HashTable<Data>

private:

protected:

  using DictionaryContainer<Data>::size;
  
  // using HashTable<Data>::???;
  // Utilizza l'ereditarietà per ereditare la variabile "array_size" e le funzioni membro da HashTable<Data>.
  using HashTable<Data>::array_size; 
  using HashTable<Data>::NextPowOf2;
  using HashTable<Data>::HashKey;

  List<Data>* array = nullptr;
  
public:

  // Utilizza l'ereditarietà per ereditare le funzioni membro dalla classe base DictionaryContainer<Data>.
  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::InsertSome;
  using DictionaryContainer<Data>::RemoveAll;
  using DictionaryContainer<Data>::RemoveSome;

  // Default constructor
  // HashTableClsAdr() specifiers;
  inline HashTableClsAdr() { array_size = 32; array = new List<Data>[array_size] {}; };

/* ************************************************************************** */

  // Specific constructors
  // HashTableClsAdr(argument) specifiers; // A hash table of a given size
  // HashTableClsAdr(argument) specifiers; // A hash table obtained from a TraversableContainer
  // HashTableClsAdr(argument) specifiers; // A hash table of a given size obtained from a TraversableContainer
  // HashTableClsAdr(argument) specifiers; // A hash table obtained from a MappableContainer
  // HashTableClsAdr(argument) specifiers; // A hash table of a given size obtained from a MappableContainer
  HashTableClsAdr(const unsigned long int size); 
  HashTableClsAdr(TraversableContainer<Data>&& otherTable) noexcept; 
  HashTableClsAdr(const unsigned long int size, TraversableContainer<Data>&& otherTable) noexcept; 
  HashTableClsAdr(const MappableContainer<Data>& otherTable); 
  HashTableClsAdr(const unsigned long int size, const MappableContainer<Data>& otherTable); 

/* ************************************************************************** */

  // Copy constructor
  // HashTableClsAdr(argument) specifiers;
  HashTableClsAdr(const HashTableClsAdr<Data>& otherTable);

  // Move constructor
  // HashTableClsAdr(argument) specifiers;
  HashTableClsAdr(HashTableClsAdr<Data>&& otherTable) noexcept; 

/* ************************************************************************** */

  // Destructor
  // ~HashTableClsAdr() specifiers;
 inline virtual ~HashTableClsAdr() { delete[] array; }; 

/* ************************************************************************** */

  // Copy assignment
  // type operator=(argument) specifiers;
  HashTableClsAdr& operator=(const HashTableClsAdr& otherTable); 

  // Move assignment
  // type operator=(argument) specifiers;
  HashTableClsAdr& operator=(HashTableClsAdr&& otherTable) noexcept;

/* ************************************************************************** */

  // Comparison operators

  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  bool operator==(const HashTableClsAdr& otherTable) const noexcept;
  inline bool operator!=(HashTableClsAdr& otherTable) const noexcept { return !(operator==(otherTable)); };

/* ************************************************************************** */

  // Specific member functions (inherited from DictionaryContainer)

  // type Insert(argument) specifiers; // Override DictionaryContainer member (Copy of the value)
  // type Insert(argument) specifiers; // Override DictionaryContainer member (Move of the value)
  // type Remove(argument) specifiers; // Override DictionaryContainer member
  virtual bool Insert(const Data& value) override; 
  virtual bool Insert(Data&& value) noexcept override; 
  virtual bool Remove(const Data& value) override; 
  
/* ************************************************************************** */

  // Specific member functions (inherited from TestableContainer)
  // type Exists(argument) specifiers; // Override TestableContainer member
  virtual bool Exists(const Data& key) const noexcept override; 

/* ************************************************************************** */

  // Specific member functions (inherited from ResizableContainer)

  // type Resize(argument) specifiers; // Resize the hashtable to a given size
  virtual void Resize(const unsigned long int new_size) override; 

/* ************************************************************************** */

  // Specific member functions (inherited from ClearableContainer)

  // type Clear() specifiers; // Override Container member
  virtual void Clear() override; 

};

/* ************************************************************************** */


}


#include "htclsadr.cpp"

#endif
