
/* ************************************************************************** */

#include <algorithm>
#include <utility>

/* ************************************************************************** */

namespace lasd
{
/* ************************************************************************** */

  // Vector

// Costruisce un vettore utilizzando un contenitore attraversabile
template <typename Data>
inline Vector<Data>::Vector(const TraversableContainer<Data> &container) : Vector(container.Size())
{
  // Inizializza l'indice
  unsigned long i = 0;
  // Attraversa il contenitore fornito
  container.Traverse([this, &i](const Data &currentData)
  { 
    // Assegna l'elemento corrente agli elementi del vettore e incrementa l'indice
    elements[i++] = currentData; 
  });
}

/* ************************************************************************** */

// Costruisce un vettore utilizzando un contenitore mappabile e movendo i suoi elementi
template <typename Data>
inline Vector<Data>::Vector(MappableContainer<Data> &&container) : Vector(container.Size())
{
  // Inizializza l'indice
  unsigned long i = 0;
  // Mappa il contenitore fornito
  container.Map([this, &i](Data &currentData)
  { 
    // Assegna l'elemento corrente agli elementi del vettore utilizzando move semantics e incrementa l'indice
    elements[i++] = std::move(currentData);
  });
}

/* ************************************************************************** */

// Costruisce un vettore copiando un altro vettore
template <typename Data>
inline Vector<Data>::Vector(const Vector<Data> &otherVector) : Vector(otherVector.size)
{
  // Copia gli elementi dal vettore otherVector a questo vettore utilizzando uninitialized_copy
  std::uninitialized_copy(otherVector.elements, otherVector.elements + size, elements);
}

/* ************************************************************************** */

// Costruisce un vettore utilizzando il movimento da un altro vettore
template <typename Data>
inline Vector<Data>::Vector(Vector<Data> &&otherVector) noexcept
{
  // Scambia la dimensione e il puntatore agli elementi tra questo vettore e otherVector
  std::swap(size, otherVector.size);
  std::swap(elements, otherVector.elements);
}

/* ************************************************************************** */
// Operators

// Operatore di assegnamento che copia un altro vettore
template <typename Data>
inline Vector<Data> &Vector<Data>::operator=(const Vector<Data> &otherVector)
{
  // Crea una copia temporanea di otherVector
  Vector<Data> temp{otherVector};
  // Scambia i contenuti tra la copia temporanea e questo vettore
  std::swap(temp, *this);
  return *this; // Restituisce un riferimento a questo vettore
}

/* ************************************************************************** */

// Operatore di assegnamento che sposta un altro vettore
template <typename Data>
inline Vector<Data> &Vector<Data>::operator=(Vector<Data> &&otherVector) noexcept
{
  // Scambia la dimensione e il puntatore agli elementi tra questo vettore e otherVector
  std::swap(size, otherVector.size);
  std::swap(elements, otherVector.elements);
  return *this; // Restituisce un riferimento a questo vettore
}

/* ************************************************************************** */

// Operatore di confronto di uguaglianza che confronta due vettori
template <typename Data>
bool Vector<Data>::operator==(const Vector<Data> &otherVector) const noexcept
{
  // Verifica se la dimensione di questo vettore è diversa da quella di otherVector
  if (size != otherVector.size)
  {
    return false;
  }

  // Confronta gli elementi di questo vettore con quelli di otherVector
  for (unsigned long i = 0; i < size; i++)
  {
    if (elements[i] != otherVector[i])
    {
      return false; 
    }
  }
  return true;// Se tutte le coppie di elementi sono uguali, restituisce true altrimenti false
}

/* ************************************************************************** */

// Operatore di confronto di disuguaglianza che confronta due vettori utilizzando l'operatore di uguaglianza e negandolo
template <typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data> &otherVector) const noexcept
{
  // Verifica se questo vettore è diverso da otherVector utilizzando l'operatore di uguaglianza e negandolo
  return !(*this == otherVector);
}

/* ************************************************************************** */

// Restituisce il riferimento costante all'elemento all'indice specificato, sollevando un'eccezione se l'indice è fuori dal range
template <typename Data>
inline const Data &Vector<Data>::operator[](unsigned long index) const
{
  // Verifica se l'indice è valido
  if (index >= size)
  {
  // Solleva un'eccezione se l'indice è fuori dal range
  throw std::out_of_range("Questo vettore non ha molti elementi");
  }
  return elements[index]; // Restituisce il riferimento costante all'elemento all'indice specificato

}

/* ************************************************************************** */

// Restituisce il riferimento all'elemento modificabile all'indice specificato, sollevando un'eccezione se l'indice è fuori dal range
template <typename Data>
inline Data &Vector<Data>::operator[](unsigned long index)
{
  // Verifica se l'indice è valido
  if (index >= size)
  {
  throw std::out_of_range("Questo vettore non ha molti elementi"); // Solleva un'eccezione se l'indice è fuori dal range
  }
  return elements[index]; // Restituisce il riferimento all'elemento all'indice specificato

}

/* ************************************************************************** */
// Overrided Methods
  

// Cancella la memoria allocata per gli elementi, impostando la dimensione a 0 e il puntatore agli elementi a nullptr
template <typename Data>
inline void Vector<Data>::Clear()
{
  // Cancella la memoria allocata per gli elementi
  delete[] elements;
  // Imposta la dimensione a 0 e il puntatore agli elementi a nullptr
  size = 0;
  elements = nullptr;
}

/* ************************************************************************** */

// Ridimensiona il vettore alla nuova dimensione specificata, deallocando e riallocando la memoria se necessario
template <typename Data>
void Vector<Data>::Resize(unsigned long newSize)
{
  // Se la nuova dimensione è uguale a quella attuale, esci dalla funzione
  if (newSize == size)
  {
    return;
  }
  // Se la nuova dimensione è 0, chiama la funzione Clear e esci
  if (newSize == 0)
  {
    Clear();
    return;
  }

  // Alloca una nuova area di memoria temporanea della nuova dimensione
  Data *temp{new Data[newSize]{}};
  // Copia gli elementi dalla vecchia area di memoria alla nuova (minimo tra vecchia e nuova dimensione)
  std::uninitialized_copy(elements, elements + std::min(size, newSize), temp);
  // Cancella la vecchia area di memoria
  delete[] elements;
  // Imposta il puntatore agli elementi alla nuova area di memoria
  elements = temp;
  // Imposta la dimensione alla nuova dimensione
  size = newSize;
}

/* ************************************************************************** */

// Restituisce il riferimento costante al primo elemento del vettore, sollevando un'eccezione se il vettore è vuoto
template <typename Data>
inline const Data &Vector<Data>::Front() const
{
  // Se il vettore non è vuoto, restituisce il primo elemento
  if (size != 0)
    return elements[0];
  // Altrimenti, solleva un'eccezione di lunghezza
  throw std::length_error("Il vettore è vuoto.");
}

/* ************************************************************************** */

// Restituisce il riferimento al primo elemento modificabile del vettore, sollevando un'eccezione se il vettore è vuoto
template <typename Data>
inline Data &Vector<Data>::Front()
{
  // Se il vettore non è vuoto, restituisce il primo elemento
  if (size != 0)
    return elements[0];
  // Altrimenti, solleva un'eccezione di lunghezza
  throw std::length_error("Il vettore è vuoto.");
}

/* ************************************************************************** */

// Restituisce il riferimento costante all'ultimo elemento del vettore, sollevando un'eccezione se il vettore è vuoto
template <typename Data>
inline const Data &Vector<Data>::Back() const
{
  // Se il vettore non è vuoto, restituisce l'ultimo elemento
  if (size != 0)
    return elements[size - 1];
  // Altrimenti, solleva un'eccezione di lunghezza
  throw std::length_error("Il vettore è vuoto.");
}

/* ************************************************************************** */

// Restituisce il riferimento all'ultimo elemento modificabile del vettore, sollevando un'eccezione se il vettore è vuoto
template <typename Data>
inline Data &Vector<Data>::Back()
{
  // Se il vettore non è vuoto, restituisce l'ultimo elemento
  if (size != 0)
    return elements[size - 1];
  // Altrimenti, solleva un'eccezione di lunghezza
  throw std::length_error("Il vettore è vuoto.");
}

/* ************************************************************************** */

// Operatore di assegnamento che copia un altro SortableVector e restituisce un riferimento a questo oggetto
template <typename Data>
inline SortableVector<Data> &SortableVector<Data>::operator=(const SortableVector<Data> &otherVector)
{
  // Richiama l'operatore di assegnazione della classe base e restituisce un riferimento a questo oggetto
  Vector<Data>::operator=(std::move(otherVector));
  return *this;
}

/* ************************************************************************** */

// Operatore di assegnamento che sposta un altro SortableVector e restituisce un riferimento a questo oggetto
template <typename Data>
inline SortableVector<Data> &SortableVector<Data>::operator=(SortableVector<Data> &&otherVector) noexcept
{
  // Richiama l'operatore di assegnazione della classe base e restituisce un riferimento a questo oggetto
  Vector<Data>::operator=(std::move(otherVector));
  return *this;
}

/* ************************************************************************** */


}
