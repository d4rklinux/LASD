#include "queuevec.hpp"

namespace lasd {

/* ************************************************************************** */

// Constructors

// Default constructor
template <typename Data>
QueueVec<Data>::QueueVec() : Vector<Data>::Vector(INIT_SIZE) {}

/* ************************************************************************** */

// Copy constructor from Different DataStructures
template <typename Data>
QueueVec<Data>::QueueVec(const TraversableContainer<Data> &con) : Vector<Data>::Vector(con), tail(con.Size()), elNums(con.Size()) {
  // Se la dimensione del vettore è inferiore alla dimensione iniziale prevista (INIT_SIZE),
  // allora il vettore viene ridimensionato al valore iniziale previsto
  if (size < INIT_SIZE)
    Resize(INIT_SIZE);
}
/* ************************************************************************** */

// Move constructor from Different DataStructures
template <typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data> &&con) : Vector<Data>::Vector(std::move(con)), tail(con.Size()),
      elNums(con.Size()) {
  // Se la dimensione del vettore è inferiore alla dimensione iniziale prevista (INIT_SIZE),
  // allora il vettore viene ridimensionato al valore iniziale previsto
  if (size < INIT_SIZE)
    Resize(INIT_SIZE);
}
/* ************************************************************************** */

// Copy constructor
template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data> &other) : Vector<Data>::Vector(other), head(other.head), tail(other.tail), elNums(other.elNums) {}
// Copia gli attributi head, tail e elNums direttamente dagli attributi di "other"

/* ************************************************************************** */

// Move constructor
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data> &&other) noexcept : Vector<Data>::Vector(std::move(other)) {
    // Scambia gli attributi head, tail e elNums tra questo oggetto e "other"
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(elNums, other.elNums);
}
/* ************************************************************************** */

// Copy assignment
template <typename Data>
inline QueueVec<Data> &QueueVec<Data>::operator=(const QueueVec<Data> &other) {
  // Utilizza l'operatore di assegnazione della classe base per copiare gli elementi
  Vector<Data>::operator=(other);
  // Copia gli attributi head, tail e elNums direttamente dagli attributi di "other"
  head = other.head;
  tail = other.tail;
  elNums = other.elNums;
    // Restituisce un riferimento a questo oggetto dopo l'assegnazione
  return *this;
}

/* ************************************************************************** */

// Move assignment
template <typename Data>
inline QueueVec<Data> &QueueVec<Data>::operator=(QueueVec<Data> &&other) noexcept {
  // Utilizza l'operatore di assegnazione di movimento della classe base per trasferire i dati
  Vector<Data>::operator=(std::move(other));
  // Scambia i membri head, tail e elNums tra questo oggetto e "other"
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(elNums, other.elNums);  
  // Restituisce un riferimento a questo oggetto dopo l'assegnazione
  return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
inline bool QueueVec<Data>::operator==(const QueueVec<Data> &other) const noexcept {
  // Verifica se il numero di elementi è diverso
  if (other.elNums != elNums)
    return false;
  // Controlla gli elementi uno per uno nell'ordine corrispondente
  for (unsigned long i = 0; i < elNums; i++)
    // Utilizza l'aritmetica dei puntatori per accedere agli elementi circolarmente
    if (elements[(head + i) % size] != other[(other.head + i) % other.size])
      return false;
  // Se tutti gli elementi corrispondono, restituisce true
  return true;
}

/* ************************************************************************** */

// Definizione dell'operatore di disuguaglianza per la classe QueueVec.
// Restituisce true se due oggetti QueueVec sono diversi, altrimenti restituisce false.
template <typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data> &other) const noexcept {
  // Utilizza l'operatore di uguaglianza per verificare se due oggetti sono uguali
  // e quindi nega il risultato
  return !(*this == other);
}

/* ************************************************************************** */

// Metodo per ottenere la testa della coda
template <typename Data>
inline const Data &QueueVec<Data>::Head() const {
  // Verifica se la coda è vuota e lancia un'eccezione se lo è
  if (!elNums)
    throw std::length_error("La coda è vuota.");
  // Restituisce il riferimento costante all'elemento in testa
  return elements[head];
};

/* ************************************************************************** */

// Metodo per ottenere la testa della coda (versione non costante)
template <typename Data>
inline Data &QueueVec<Data>::Head() {
  // Verifica se la coda è vuota e lancia un'eccezione se lo è
  if (!elNums)
    throw std::length_error("La coda è vuota.");
  // Restituisce il riferimento all'elemento in testa
  return elements[head];
};

/* ************************************************************************** */

// Metodo per rimuovere l'elemento in testa dalla coda
template <typename Data>
inline void QueueVec<Data>::Dequeue() {
  // Verifica se la coda è vuota e lancia un'eccezione se lo è
  if (!elNums)
    throw std::length_error("La coda è vuota.");

  // Avanza l'indice della testa circolarmente
  head = (head + 1) % size;

  // Riduce la dimensione del vettore se necessario
  if (--elNums == size / REDUCE_TRASHOLD)
    Resize(size / REDUCE_FACTOR);
}

/* ************************************************************************** */

// Metodo per ottenere e rimuovere l'elemento in testa dalla coda
template <typename Data>
inline Data QueueVec<Data>::HeadNDequeue() {
  // Ottiene l'elemento in testa
  Data headEl = Head();
  // Rimuove l'elemento in testa dalla coda
  Dequeue();
  // Restituisce l'elemento in testa
  return headEl;
}

/* ************************************************************************** */

// Metodo per inserire un elemento in coda alla coda (l-value)
template <typename Data>
void QueueVec<Data>::Enqueue(const Data &data) {
  // Ridimensiona il vettore se necessario
  if (elNums == size)
    Resize(size * INCREASE_FACTOR);

  // Inserisce l'elemento in coda alla coda
  elements[tail] = data;
  // Avanza l'indice della coda circolarmente
  tail = (tail + 1) % size;
  // Incrementa il numero di elementi nella coda
  ++elNums;
}

/* ************************************************************************** */

// Metodo per inserire un elemento in coda alla coda (r-value)
template <typename Data>
void QueueVec<Data>::Enqueue(Data &&data) {
  // Ridimensiona il vettore se necessario
  if (elNums == size)
    Resize(size * INCREASE_FACTOR);

  // Inserisce l'elemento in coda alla coda utilizzando il movimento
  elements[tail] = std::move(data);
  // Avanza l'indice della coda circolarmente
  tail = (tail + 1) % size;
  // Incrementa il numero di elementi nella coda
  ++elNums;
}

/* ************************************************************************** */

// Metodo per verificare se la coda è vuota
template <typename Data>
inline bool QueueVec<Data>::Empty() const noexcept {
  // Restituisce true se la coda è vuota, altrimenti false
  return elNums == 0;
}

/* ************************************************************************** */

// Metodo per ottenere la dimensione della coda
template <typename Data>
inline unsigned long QueueVec<Data>::Size() const noexcept {
  // Restituisce il numero di elementi nella coda
  return elNums;
}

/* ************************************************************************** */

// Metodo per svuotare la coda
template <typename Data>
inline void QueueVec<Data>::Clear() {
  // Ridimensiona il vettore alla dimensione iniziale e reimposta gli indici della testa e della coda
  Resize(INIT_SIZE);
  tail = head = elNums = 0;
}

/* ************************************************************************** */

// Metodo per ridimensionare il vettore interno
template <typename Data>
void QueueVec<Data>::Resize(unsigned long newSize) {
  // Verifica se la nuova dimensione è accettabile e se è diversa dalla dimensione attuale
  if (newSize < INIT_SIZE || newSize == size)
    return;

  // Alloca un nuovo array temporaneo di dimensione newSize
  Data *temp{new Data[newSize]{}};
  // Copia gli elementi dal vettore attuale al nuovo array temporaneo
  for (unsigned long i{head}, j{0}; j < elNums; i = (i + 1) % size, ++j)
    temp[j] = elements[i];

  // Scambia il nuovo array temporaneo con il vettore attuale
  std::swap(elements, temp);
  // Dealloca l'array temporaneo
  delete[] temp;

  // Reimposta gli indici della testa e della coda e la dimensione del vettore
  head = 0;
  tail = elNums;
  size = newSize;
}

/* ************************************************************************** */

} 