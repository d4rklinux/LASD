#include "linear.hpp"
#include "mappable.hpp"

namespace lasd {

/* ************************************************************************** */

// Verifica se il contenitore è uguale a un altro contenitore lineare
  template <typename Data>
  inline bool LinearContainer<Data>::operator==(const LinearContainer<Data>& container) const noexcept {
    // Controlla se le dimensioni dei container sono uguali
    if (size != container.Size()) {
        return false;
    }
    // Confronta elemento per elemento i due container
    for (unsigned long int i {0}; i < size; ++i){
        if ((*this)[i] != container[i]){
            return false;
        }
    }
    return true;
  }

/* ************************************************************************** */

// Verifica se il contenitore è diverso da un altro contenitore lineare
  template <typename Data>
  inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& container) const noexcept {
    // Utilizza l'operatore di uguaglianza per verificare la disuguaglianza
    return !(*this == container);
  }

/* ************************************************************************** */

// Restituisce il riferimento costante al primo elemento del contenitore lineare
  template <typename Data>
  inline const Data& LinearContainer<Data>::Front() const {
    // Restituisce il primo elemento del container
    if (size) {
        return (*this)[0];
    }
    throw std::length_error("Contenitore lineare vuoto.");
  }

/* ************************************************************************** */

// Restituisce il riferimento al primo elemento del contenitore lineare
  template <typename Data>
  inline Data& LinearContainer<Data>::Front() {
    // Restituisce il primo elemento del container
    if (size) {
        return (*this)[0];
    }
    throw std::length_error("Contenitore lineare vuoto.");
  }

/* ************************************************************************** */

// Restituisce il riferimento costante all'ultimo elemento del contenitore lineare
  template <typename Data>
  inline const Data& LinearContainer<Data>::Back() const {
    // Restituisce l'ultimo elemento del container
    if (size) {
        return (*this)[size - 1];
    }
    throw std::length_error("Contenitore lineare vuoto.");
  }

/* ************************************************************************** */

// Restituisce il riferimento all'ultimo elemento del contenitore lineare
  template <typename Data>
  inline Data& LinearContainer<Data>::Back() {
    // Restituisce l'ultimo elemento del container
    if (size) {
        return (*this)[size - 1];
    }
    throw std::length_error("Contenitore lineare vuoto.");
  }

/* ************************************************************************** */

  // Attraversamento del contenitore lineare
  template <typename Data> 
  inline void LinearContainer<Data>::Traverse(TraverseFun function) const {
    PreOrderTraverse(function);
  }

/* ************************************************************************** */

  // Attraversamento pre-ordine del contenitore lineare
  template <typename Data>  
  inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun function) const {
    // Attraversamento pre-ordine del container
    for (unsigned long int i {0}; i < size; ++i){
        function((*this)[i]);
    } 
  }

/* ************************************************************************** */

  // Attraversamento post-ordine del contenitore lineare
  template <typename Data>  
  inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun function) const {
    // Attraversamento post-ordine del container
    for (unsigned long int i {size}; i > 0;){
        function((*this)[--i]);
    }
  }

/* ************************************************************************** */

  // Mappatura del contenitore lineare
  template <typename Data>  
  inline void LinearContainer<Data>::Map(MapFun function) {
    PreOrderMap(function);
  }

/* ************************************************************************** */

  // Mappatura pre-ordine del contenitore lineare  
  template <typename Data>  
  inline void LinearContainer<Data>::PreOrderMap(MapFun function) {
    // Mappatura pre-ordine del container
    for (unsigned long int i {0}; i < size; ++i){
        function((*this)[i]);
    } 
  }

/* ************************************************************************** */

  // Mappatura post-ordine del contenitore lineare
  template <typename Data>  
  inline void LinearContainer<Data>::PostOrderMap(MapFun function) {
    // Mappatura post-ordine del container
    for (unsigned long int i {size}; i > 0;){
        function((*this)[--i]);
    } 
  }

/* ************************************************************************** */
  // SortableLinearContainer

  // Ordina il contenitore utilizzando l'algoritmo quicksort
  template <typename Data>
  void SortableLinearContainer<Data>::Sort() noexcept {
    // Ordina il container utilizzando l'algoritmo quicksort
    quick(0, size - 1);
  }

/* ************************************************************************** */

  // Implementazione dell'algoritmo quicksort per il contenitore lineare ordinabile
  template <typename Data>
  void SortableLinearContainer<Data>::quick(unsigned long int start, unsigned long int end) noexcept {
    // Implementazione dell'algoritmo quicksort
    if (start >= end) {
        return;
    }
    unsigned long int middle = part(start, end);
    quick(start, middle);
    quick(middle + 1, end);
  }

/* ************************************************************************** */

  // Partiziona il contenitore per l'algoritmo quicksort
  template <typename Data>
  unsigned long int SortableLinearContainer<Data>::part(unsigned long int start, unsigned long int end) noexcept {
  
  // Inizializza il generatore di numeri casuali con un seme univoco
  std::default_random_engine generator(std::random_device{}());
  // Distribuzione uniforme per generare un indice casuale nel range [start, end]
  std::uniform_int_distribution<unsigned long int> distribution(start, end);

  // Scambia l'elemento iniziale con un elemento casuale nel range [start, end]
  std::swap((*this)[start], (*this)[distribution(generator)]);
  // Ottiene il riferimento all'elemento di partizione
  Data& element = (*this)[start];

  // Inizializza gli indici per la scansione
  unsigned long int i = start - 1;
  unsigned long int j = end + 1;

  // Esegue la scansione e lo scambio degli elementi
  do {
    // Scansiona da destra a sinistra fino a trovare un elemento minore o uguale all'elemento di partizione
    while (element < (*this)[--j]);
    // Scansiona da sinistra a destra fino a trovare un elemento maggiore o uguale all'elemento di partizione
    while (element > (*this)[++i]);
    // Se gli indici non si sono ancora incrociati, scambia gli elementi
    if (i < j) std::swap((*this)[i], (*this)[j]);
  } while (i < j);

  // Restituisce l'indice del pivot dopo la partizione
  return i;
}

/* ************************************************************************** */

} 
