
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"

// #include ...
#include <random>
#include <bitset>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> { // Must extend HashTable<Data>

private:

protected:

  // ...
  using DictionaryContainer<Data>::size;
  
  // using HashTable<Data>::???;
  using HashTable<Data>::array_size;
  using HashTable<Data>::NextPowOf2;
  using HashTable<Data>::HashKey; 

  

  Data* Elements = nullptr;
  std::bitset<2>* flagsArray = nullptr; //Array of 2 bits: 00=Empty; 01=Impossible; 10=Deleted; 11=Accessible
  unsigned long int deleted_elements = 0; 

public:

  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::InsertSome;
  using DictionaryContainer<Data>::RemoveAll;
  using DictionaryContainer<Data>::RemoveSome;

  // Default constructor
  inline HashTableOpnAdr() { // HashTableOpnAdr() specifiers;
  Elements = new Data[array_size] {};
  flagsArray = new std::bitset<2>[array_size] {};
  
  };

/* ************************************************************************** */

  // Specific constructors
  // HashTableOpnAdr(argument) specifiers; // A hash table of a given size
  // HashTableOpnAdr(argument) specifiers; // A hash table obtained from a TraversableContainer
  // HashTableOpnAdr(argument) specifiers; // A hash table of a given size obtained from a TraversableContainer
  // HashTableOpnAdr(argument) specifiers; // A hash table obtained from a MappableContainer
  // HashTableOpnAdr(argument) specifiers; // A hash table of a given size obtained from a MappableContainer
  HashTableOpnAdr(const unsigned long int size);  
  HashTableOpnAdr(TraversableContainer<Data>&& otherTable) noexcept; 
  HashTableOpnAdr(const unsigned long int size, TraversableContainer<Data>&& otherTable) noexcept; 
  HashTableOpnAdr(const MappableContainer<Data>& otherTable); 
  HashTableOpnAdr(const unsigned long int size, const MappableContainer<Data>& otherTable); 

/* ************************************************************************** */

  // Copy constructor
  // HashTableOpnAdr(argument) specifiers;
  HashTableOpnAdr(const HashTableOpnAdr<Data>& otherTable);

  // Move constructor
  // HashTableOpnAdr(argument) specifiers;
  HashTableOpnAdr(HashTableOpnAdr<Data>&& otherTable) noexcept; 

/* ************************************************************************** */

  // Destructor
  // ~HashTableOpnAdr() specifiers;
  inline virtual ~HashTableOpnAdr() { 
  delete [] flagsArray; 
  delete [] Elements; 
  
  };

/* ************************************************************************** */

  // Copy assignment
  // type operator=(argument) specifiers;
  HashTableOpnAdr& operator=(const HashTableOpnAdr& otherTable); 

  // Move assignment
  // type operator=(argument) specifiers;
  HashTableOpnAdr& operator=(HashTableOpnAdr&& otherTable) noexcept; 

/* ************************************************************************** */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  bool operator==(const HashTableOpnAdr& otherTable) const noexcept; 
  inline bool operator!=(const HashTableOpnAdr& otherTable) const noexcept { return !(operator==(otherTable)); }; 

/* ************************************************************************** */

  // Specific member functions (inherited from DictionaryContainer)

  // type Insert(argument) specifiers; // Override DictionaryContainer member (Copy of the value)
  // type Insert(argument) specifiers; // Override DictionaryContainer member (Move of the value)
  // type Remove(argument) specifiers; // Override DictionaryContainer member
  virtual bool Insert(const Data& data) override;  
  virtual bool Insert(Data&& data) override; 
  virtual bool Remove(const Data& data) override; 

/* ************************************************************************** */

  // Specific member functions (inherited from TestableContainer)

  // type Exists(argument) specifiers; // Override TestableContainer member
  virtual bool Exists(const Data& data) const noexcept override; 

/* ************************************************************************** */

  // Specific member functions (inherited from ResizableContainer)
  
  // type Resize(argument) specifiers; // Resize the hashtable to a given size
  virtual void Resize(const unsigned long int new_size) override; 

/* ************************************************************************** */

  // Specific member functions (inherited from ClearableContainer)

  // type Clear() specifiers; // Override Container member
  virtual void Clear() override; 

/* ************************************************************************** */

protected:

  // Auxiliary member functions

  // type HashKey(argument) specifiers;
  // type Find(argument) specifiers;
  // type FindEmpty(argument) specifiers;
  // type Remove(argument) specifiers;
  unsigned long int HashKey(unsigned long int& probe, const Data &key) const noexcept; // Calcola una chiave hash per il dato
  bool Find(unsigned long int& index, unsigned long int& probe, const Data& key) const noexcept; // Cerca una chiave, restituisce true se trovata
  unsigned long int FindEmpty(unsigned long int& probe, const Data& key) noexcept; // Trova una posizione vuota per inserire il dato
  bool Remove(unsigned long int& probe, const Data& key); // Rimuove una chiave, restituisce true se rimossa

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
