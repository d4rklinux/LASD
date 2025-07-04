
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:

  // type operator()(argument) specifiers; // (concrete function should not throw exceptions)
  unsigned long int operator ()(const Data data) const noexcept = 0; 
};

/* ************************************************************************** */

template <typename Data> 
class HashTable : virtual public ResizableContainer, // Must extend ResizableContainer,                                                
virtual public DictionaryContainer<Data> { // DictionaryContainer<Data>
                  

private:

  // ...

protected:

  // using DictionaryContainer<Data>::???;

  // Utilizza l'ereditarietà per ereditare la variabile "size" dalla classe base DictionaryContainer<Data>.
  using DictionaryContainer<Data>::size; 

  // Variabili per la generazione dell'hash.
  unsigned long int hashMultiplier = 1;
  unsigned long int hashOffset = 0;
  
  // Numero primo per l'hashing.
  static const unsigned long int prime_number = 1000003;

  // Motore di generazione di numeri casuali e distribuzioni per generare i moltiplicatori e gli offset dell'hash.
  std::default_random_engine seed = std::default_random_engine(std::random_device{}());
  std::uniform_int_distribution<unsigned long int> genHashMultiplier = std::uniform_int_distribution<unsigned long int>(1, prime_number-1);
  std::uniform_int_distribution<unsigned long int> genHashOffset = std::uniform_int_distribution<unsigned long int>(0, prime_number-1);

  unsigned long int array_size = 32;

  // Default constructor
  inline HashTable(){

    // Genera i moltiplicatori e gli offset dell'hash.
    hashMultiplier = genHashMultiplier(seed) * 2 + 1;
    hashOffset = NextPowOf2(genHashOffset(seed));
  }
  
  // Copy constructor
  HashTable(const HashTable& otherTable);
  // Move constructor
  HashTable(HashTable&& otherTable) noexcept;

public:

  // Destructor
  // ~HashTable() specifiers
   virtual ~HashTable() = default; // ~HashTable() specifiers

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  HashTable& operator =(const HashTable& otherTable);

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  HashTable& operator = (HashTable&& otherTable) noexcept;
   
  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract hashtable is possible but not required.
  // type operator!=(argument) specifiers; // Comparison of abstract hashtable is possible but not required.
  bool operator==(const HashTable& otherTable) const noexcept;
  inline bool operator !=(const HashTable& otherTable) const noexcept {return !(operator ==(otherTable)); };

  // Funzione per leggere la dimensione dell'array
  unsigned long int ReadSizeOfArray() {
  return array_size;
  }
  
  // Utilizza l'ereditarietà per ereditare la funzione Exists dalla classe base DictionaryContainer<Data>.
  using DictionaryContainer<Data>::Exists;

protected:

  // Auxiliary member functions
  inline unsigned long int HashKey(const unsigned long int key) const noexcept {return (hashMultiplier * key + hashOffset ) % array_size; };
  
  // type HashKey(argument) specifiers;
  unsigned long int NextPowOf2(unsigned long int size);
};

/* ************************************************************************** */


}

#include "hashtable.cpp"

#endif
