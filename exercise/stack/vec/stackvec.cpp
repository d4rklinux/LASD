
namespace lasd {

/* ************************************************************************** */

// Constructor

// Default constructor
// Costruisce uno StackVec con una dimensione iniziale predefinita
template <typename Data>
StackVec<Data>::StackVec() : Vector<Data>::Vector(INIT_SIZE) {}

/* ************************************************************************** */

// Costruisce uno StackVec utilizzando un contenitore attraversabile come modello e inizializza la cima della pila
template <typename Data>
StackVec<Data>::StackVec(const TraversableContainer<Data> &con) : Vector<Data>::Vector(con), top(con.Size()) {
  if (size < INIT_SIZE)
    Resize(INIT_SIZE);
}

/* ************************************************************************** */

// Costruisce uno StackVec utilizzando un contenitore mappabile attraverso lo spostamento e inizializza la cima della pila
template <typename Data>
StackVec<Data>::StackVec(MappableContainer<Data> &&con) : Vector<Data>::Vector(std::move(con)), top(con.Size()) {
  if (size < INIT_SIZE)
    Resize(INIT_SIZE);
}

/* ************************************************************************** */

// Costruisce uno StackVec copiando un altro StackVec e inizializza la cima della pila
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data> &otherStack) : Vector<Data>::Vector(otherStack), top(otherStack.top) {}

/* ************************************************************************** */

// Costruisce uno StackVec utilizzando il movimento di un altro StackVec e scambia le cime delle pile
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data> &&otherStack) noexcept : Vector<Data>::Vector(std::move(otherStack)) {
  std::swap(top, otherStack.top);
}

/* ************************************************************************** */

// Operators

// Operatore di assegnamento che copia un altro StackVec e aggiorna la cima della pila
template <typename Data>
inline StackVec<Data> &StackVec<Data>::operator=(const StackVec<Data> &otherStack) {
   // Utilizziamo l'operatore di assegnamento della classe base Vector per copiare gli elementi dall'altra pila
  Vector<Data>::operator=(otherStack);
  // Copiamo il valore del puntatore alla cima della pila dall'altra pila
  top = otherStack.top;
  // Restituiamo un riferimento a questa istanza di StackVec
  return *this;
}

/* ************************************************************************** */

// Operatore di assegnamento con spostamento che sposta un altro StackVec e aggiorna la cima della pila
template <typename Data>
inline StackVec<Data> &StackVec<Data>::operator=(StackVec<Data> &&otherStack) noexcept {
   // Utilizziamo l'operatore di assegnamento con movimento della classe base Vector per spostare gli elementi dell'altra pila
  Vector<Data>::operator=(std::move(otherStack));
  // Scambiamo i valori dei puntatori alla cima della pila tra le due pile
  std::swap(top, otherStack.top);
  // Restituiamo un riferimento a questa istanza di StackVec
  return *this;
}

/* ************************************************************************** */

// Operatore di confronto di uguaglianza che confronta due StackVec
template <typename Data>
inline bool StackVec<Data>::operator==(const StackVec<Data> &otherStack) const noexcept {
  // Se il numero di elementi nella cima della pila non corrisponde, le pile non sono uguali
  if (top != otherStack.top)
    return false;
  // Iteriamo attraverso gli elementi delle pile
  for (unsigned long i = 0; i < top; i++) {
    // Se troviamo anche solo un elemento diverso, le pile non sono uguali
    if (elements[i] != otherStack[i]) {
      return false;
    }
  }
  // Se non abbiamo trovato differenze, le pile sono uguali
  return true;
}

/* ************************************************************************** */

// Operatore di confronto di disuguaglianza che confronta due StackVec
template <typename Data>
// Definizione dell'operatore di confronto di disuguaglianza tra due StackVec
inline bool StackVec<Data>::operator!=(const StackVec<Data> &otherStack) const noexcept {
  // Utilizziamo l'operatore di uguaglianza definito sopra e invertiamo il risultato, poiché stiamo verificando la disuguaglianza
  return !(*this == otherStack);
}

/* ************************************************************************** */

// Overrided Methods

// Restituisce il riferimento costante all'elemento in cima alla pila
template <typename Data> inline const Data &StackVec<Data>::Top() const {
  // Se la cima della pila è vuota, lanciamo un'eccezione di lunghezza
  if (!top)
    throw std::length_error("La pila è vuota");
  // Restituiamo il riferimento costante all'elemento in cima
  return elements[top - 1];
}

/* ************************************************************************** */

// Restituisce il riferimento all'elemento modificabile in cima alla pila
template <typename Data> inline Data &StackVec<Data>::Top() {
  // Se la cima della pila è vuota, lanciamo un'eccezione di lunghezza
  if (!top)
    throw std::length_error("La pila è vuota");
  // Restituiamo il riferimento all'elemento in cima
  return elements[top - 1];
}

/* ************************************************************************** */

// Rimuove l'elemento in cima alla pila
template <typename Data> inline void StackVec<Data>::Pop() {
  // Se la cima della pila è vuota, lanciamo un'eccezione di lunghezza
  if (!top)
    throw std::length_error("La pila è vuota");

  // Decrementiamo il puntatore alla cima e, se necessario, ridimensioniamo l'array
  if (--top < size / REDUCE_TRASHOLD)
    Resize(size / REDUCE_FACTOR);
}

/* ************************************************************************** */

// Restituisce e rimuove l'elemento in cima alla pila
template <typename Data> inline Data StackVec<Data>::TopNPop() {
  // Salviamo l'elemento in cima
  Data topEl{Top()};
  // Rimuoviamo l'elemento in cima dalla pila
  Pop();
  // Restituiamo l'elemento precedentemente in cima
  return topEl;
}

/* ************************************************************************** */

// Inserisce un nuovo elemento in cima alla pila
template <typename Data> void StackVec<Data>::Push(const Data &newData) {
  // Se la pila è piena, aumentiamo la dimensione
  if (top == size)
    Resize(size * INCREASE_FACTOR);
  // Inseriamo il nuovo dato nella cima della pila
  elements[top++] = newData;
}

/* ************************************************************************** */

// Inserisce un nuovo elemento in cima alla pila utilizzando il movimento dei dati
template <typename Data> void StackVec<Data>::Push(Data &&newData) {
  // Se la pila è piena, aumentiamo la dimensione
  if (top == size)
    Resize(size * INCREASE_FACTOR);
  // Inseriamo il nuovo dato nella cima della pila utilizzando il movimento
  elements[top++] = std::move(newData);
}

/* ************************************************************************** */

// Svuota la pila reimpostando la dimensione dell'array e la cima
template <typename Data> inline void StackVec<Data>::Clear() {
  // Ridimensioniamo l'array alla dimensione iniziale e reimpostiamo la cima a 0
  Resize(INIT_SIZE);
  top = 0;
}

/* ************************************************************************** */

// Ridimensiona il vettore se la nuova dimensione è maggiore o uguale alla dimensione iniziale
template <typename Data> inline void StackVec<Data>::Resize(unsigned long newSize) {
  // Se la nuova dimensione è maggiore o uguale alla dimensione iniziale, ridimensioniamo il vettore
  if (newSize >= INIT_SIZE)
    Vector<Data>::Resize(newSize);
}

/* ************************************************************************** */

} 
