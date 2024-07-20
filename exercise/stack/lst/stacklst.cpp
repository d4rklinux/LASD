
namespace lasd {

/* ************************************************************************** */

// Constructors

// Costruttore di copia che inizializza StackLst con TraversableContainer
template <typename Data>
StackLst<Data>::StackLst(const TraversableContainer<Data> &con) : List<Data>::List(con) {}

// Costruttore di spostamento che inizializza StackLst con MappableContainer
template <typename Data>
StackLst<Data>::StackLst(MappableContainer<Data> &&con) : List<Data>::List(std::move(con)) {}

// Costruttore di copia che inizializza StackLst con un altro StackLst
template <typename Data>
inline StackLst<Data>::StackLst(const StackLst<Data> &s) : List<Data>::List(s) {}

// Costruttore di spostamento che inizializza StackLst con un altro StackLst utilizzando std::move
template <typename Data>
inline StackLst<Data>::StackLst(StackLst<Data> &&s) : List<Data>::List(std::move(s)) {}

/* ************************************************************************** */

// Operatore di assegnamento che assegna un altro StackLst
template <typename Data>
inline StackLst<Data> &StackLst<Data>::operator=(const StackLst<Data> &s) {
  List<Data>::operator=(s);
  return *this;
}

/* ************************************************************************** */

// Operatore di assegnamento per spostamento che assegna un altro StackLst utilizzando std::move
template <typename Data>
inline StackLst<Data> &StackLst<Data>::operator=(StackLst<Data> &&s) noexcept {
  List<Data>::operator=(std::move(s));
  return *this;
}

/* ************************************************************************** */

// Operatore di confronto di uguaglianza che confronta due StackLst
template <typename Data>
inline bool StackLst<Data>::operator==(const StackLst<Data> &s) const noexcept {
  return List<Data>::operator==(s);
}

/* ************************************************************************** */

// Operatore di confronto di disuguaglianza che confronta due StackLst
template <typename Data>
inline bool StackLst<Data>::operator!=(const StackLst<Data> &s) const noexcept {
  return !(*this == s);
}

/* ************************************************************************** */

// Overrided Methods

// Restituisce il riferimento costante all'elemento in cima alla pila
template <typename Data> inline const Data &StackLst<Data>::Top() const {
  if (!size)
    throw std::length_error("La pila è vuota");

  return List<Data>::Front();
}

// Restituisce il riferimento all'elemento modificabile in cima alla pila
template <typename Data> inline Data &StackLst<Data>::Top() {
  if (!size)
    throw std::length_error("La pila è vuota");

  return List<Data>::Front();
}

/* ************************************************************************** */

// Rimuove l'elemento in cima alla pila
template <typename Data> inline void StackLst<Data>::Pop() {
  if (!size)
    throw std::length_error("La pila è vuota");

  List<Data>::RemoveFromFront();
}

/* ************************************************************************** */

// Restituisce e rimuove l'elemento in cima alla pila
template <typename Data> inline Data StackLst<Data>::TopNPop() {
  if (!size)
    throw std::length_error("La pila è vuota");

  return List<Data>::FrontNRemove();
}

/* ************************************************************************** */

// Inserisce un nuovo elemento in cima alla pila
template <typename Data> inline void StackLst<Data>::Push(const Data &dat) {
  return List<Data>::InsertAtFront(dat);
}

/* ************************************************************************** */

// Inserisce un nuovo elemento in cima alla pila utilizzando il movimento dei dati
template <typename Data> inline void StackLst<Data>::Push(Data &&dat) {
  return List<Data>::InsertAtFront(std::move(dat));
}

/* ************************************************************************** */

}
