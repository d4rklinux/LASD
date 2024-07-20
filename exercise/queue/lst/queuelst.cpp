
namespace lasd {

/* ************************************************************************** */

// Costruttore che inizializza la coda con i dati di un contenitore attraversabile
template <typename Data>
QueueLst<Data>::QueueLst(const TraversableContainer<Data> &container) : List<Data>::List(container) {}

/* ************************************************************************** */

// Costruttore che inizializza la coda con i dati di un contenitore mappabile utilizzando il movimento
template <typename Data>
QueueLst<Data>::QueueLst(MappableContainer<Data> &&container) : List<Data>::List(std::move(container)) {}

/* ************************************************************************** */

// Costruttore di copia che inizializza la coda con un'altra coda
template <typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data> &other) : List<Data>::List(other) {}

/* ************************************************************************** */

// Costruttore di movimento che inizializza la coda con un'altra coda utilizzando il movimento
template <typename Data>
QueueLst<Data>::QueueLst(QueueLst<Data> &&other) noexcept : List<Data>::List(std::move(other)) {}

/* ************************************************************************** */

// Operatore di assegnamento che assegna una coda a un'altra coda
template <typename Data>
inline QueueLst<Data> &QueueLst<Data>::operator=(const QueueLst<Data> &other) {
  List<Data>::operator=(other);
  return *this;
}

/* ************************************************************************** */

// Operatore di assegnamento di movimento che assegna il contenuto di una coda a un'altra coda utilizzando il movimento
template <typename Data>
inline QueueLst<Data> &QueueLst<Data>::operator=(QueueLst<Data> &&other) noexcept {
  List<Data>::operator=(std::move(other));
  return *this;
}

/* ************************************************************************** */

// Operatore di confronto per verificare l'uguaglianza tra due code
template <typename Data>
inline bool QueueLst<Data>::operator==(const QueueLst<Data> &other) const noexcept {
  return List<Data>::operator==(other);
}

/* ************************************************************************** */

// Operatore di confronto per verificare la disuguaglianza tra due code
template <typename Data>
inline bool QueueLst<Data>::operator!=(const QueueLst<Data> &other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */
// Overrided Methods

// Restituisce il riferimento all'elemento in testa alla coda
template <typename Data> inline Data &QueueLst<Data>::Head() {
  if (!size)
    throw std::length_error("La coda e' vuota");

  return List<Data>::Front();
}

/* ************************************************************************** */

// Restituisce il riferimento costante all'elemento in testa alla coda
template <typename Data> inline const Data &QueueLst<Data>::Head() const {
  if (!size)
    throw std::length_error("La coda e' vuota");

  return List<Data>::Front();
}

/* ************************************************************************** */

// Rimuove l'elemento in testa alla coda
template <typename Data> inline void QueueLst<Data>::Dequeue() {
  if (!size)
    throw std::length_error("La coda e' vuota");

  return List<Data>::RemoveFromFront();
}

/* ************************************************************************** */

// Restituisce e rimuove l'elemento in testa alla coda
template <typename Data> inline Data QueueLst<Data>::HeadNDequeue() {
  if (!size)
    throw std::length_error("La coda e' vuota");

  return List<Data>::FrontNRemove();
}

/* ************************************************************************** */

// Inserisce un elemento in coda alla coda
template <typename Data> inline void QueueLst<Data>::Enqueue(const Data &data) {
  return List<Data>::InsertAtBack(data);
}

/* ************************************************************************** */

// Inserisce un elemento in coda alla coda utilizzando il movimento
template <typename Data> inline void QueueLst<Data>::Enqueue(Data &&data) {
  return List<Data>::InsertAtBack(std::move(data));
}

/* ************************************************************************** */


} 
