#include "bst.hpp"

namespace lasd {

/* ************************************************************************** */

// Costruttore che inizializza un albero binario di ricerca (BST) 
// utilizzando gli elementi contenuti nell'oggetto TraversableContainer<Data> fornito in input.
template <typename Data>
BST<Data>::BST(const TraversableContainer<Data>& inputData){
  // Utilizza la funzione Traverse per iterare su tutti gli elementi dell'inputData.
  inputData.Traverse(
    // Per ogni elemento, esegue la seguente lambda function che inserisce
    // l'elemento nell'albero binario di ricerca utilizzando la funzione Insert.
    [this](const Data& element){
        Insert(element);
    }
  );
}

/* ************************************************************************** */

// Costruttore che inizializza un albero binario di ricerca (BST) 
// utilizzando gli elementi contenuti nell'oggetto MappableContainer<Data> 
template <typename Data>
BST<Data>::BST(MappableContainer<Data>&& inputData) noexcept {
    // Utilizza la funzione Map per trasformare ogni elemento dell'inputData.
    inputData.Map(
        // Per ogni elemento, esegue la seguente lambda function che inserisce
        // l'elemento nell'albero binario di ricerca utilizzando std::move per trasferire la proprietà dell'oggetto.
        [this](Data& element) {
            Insert(std::move(element));
        }
    );
}

/* ************************************************************************** */

// Costruttore di copia che inizializza un nuovo albero binario di ricerca (BST)
template<typename Data>
BST<Data>::BST(const BST<Data>& inputData) : BinaryTreeLnk<Data>::BinaryTreeLnk(inputData) {}

/* ************************************************************************** */

// Costruttore di spostamento che inizializza un nuovo albero binario di ricerca (BST)
template<typename Data>
BST<Data>::BST(BST<Data>&& inputData) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(inputData)) {}

/* ************************************************************************** */

// Operatore di assegnamento che copia i dati dall'albero binario di ricerca di input 
template <typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& inputData){
  BinaryTreeLnk<Data>::operator=(inputData);
  return *this;
}

/* ************************************************************************** */

// Operatore di assegnamento che trasferisce i dati dall'albero binario di ricerca di input 
template <typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& inputData) noexcept {
  BinaryTreeLnk<Data>::operator=(std::move(inputData));
  return *this;
}

/* ************************************************************************** */

// Operatore di confronto di uguaglianza che confronta due alberi binari di ricerca (BST), verificando se contengono gli stessi elementi nello stesso ordine.
template <typename Data>
bool BST<Data>::operator==(const BST& inputData) const noexcept {
    // Verifica preliminare della dimensione degli alberi.
    if (size == inputData.Size()) {
        // Ottiene iteratori in-order per entrambi gli alberi.
        BTInOrderIterator<Data> IterThis(*this);
        BTInOrderIterator<Data> IterOther(inputData);
        // Itera attraverso entrambi gli alberi contemporaneamente utilizzando un ciclo while.
        while (!IterThis.Terminated()) {
            if ((*IterThis) != (*IterOther)) // Se gli elementi correnti non corrispondono, restituisce false.
                return false;       
            ++IterThis;
            ++IterOther; // Avanza agli elementi successivi in entrambi gli alberi.

        }
        return true; // Se tutti gli elementi sono uguali, restituisce true.
    }
    return false; // Se le dimensioni degli alberi sono diverse, restituisce false.
}

/* ************************************************************************** */
// Specific member functions

// Restituisce il valore minimo presente nell'albero.
template<typename Data>
const Data& BST<Data>::Min() const {
  if (root != nullptr)
    // Trova il puntatore al nodo contenente il valore minimo e restituisce il suo valore.
    return FindPointerToMin(root)->elem;
  else
    // Se l'albero è vuoto, solleva un'eccezione.
    throw std::length_error("L'albero è vuoto in Min()");
}

/* ************************************************************************** */

// Restituisce il valore minimo presente nell'albero e lo rimuove dall'albero.
template <typename Data>
Data BST<Data>::MinNRemove(){
  if (root != nullptr)
    // Rimuove il nodo contenente il valore minimo e restituisce il suo valore.
    return DataNDelete(DetachMin(root));
  else
    // Se l'albero è vuoto, solleva un'eccezione.
    throw std::length_error("L'albero è vuoto in MinNRemove()");
}

/* ************************************************************************** */

// Rimuove il valore minimo presente nell'albero.
template<typename Data>
void BST<Data>::RemoveMin(){
  if (root != nullptr)
    // Rimuove il nodo contenente il valore minimo senza restituirlo.
    delete DetachMin(root);
  else
    // Se l'albero è vuoto, solleva un'eccezione.
    throw std::length_error("L'albero è vuoto in RemoveMin()");
}

/* ************************************************************************** */

// Restituisce il valore massimo presente nell'albero.
template <typename Data>
const Data& BST<Data>::Max()const{
  if (root != nullptr)
    // Trova il puntatore al nodo contenente il valore massimo e restituisce il suo valore.
    return FindPointerToMax(root)->elem;
  else
    // Se l'albero è vuoto, solleva un'eccezione.
    throw std::length_error("L'albero è vuoto in Max()");
}

/* ************************************************************************** */

// Restituisce il valore massimo presente nell'albero e lo rimuove dall'albero.
template <typename Data>
Data BST<Data>::MaxNRemove(){
  if (root != nullptr)
    // Rimuove il nodo contenente il valore massimo e restituisce il suo valore.
    return DataNDelete(DetachMax(root));
  else
    // Se l'albero è vuoto, solleva un'eccezione.
    throw std::length_error("L'albero è vuoto in MaxNRemove()");
}

/* ************************************************************************** */

// Rimuove il valore massimo presente nell'albero.
template<typename Data>
void BST<Data>::RemoveMax(){
  if (root != nullptr)
    // Rimuove il nodo contenente il valore massimo senza restituirlo.
    delete DetachMax(root);
  else
    // Se l'albero è vuoto, solleva un'eccezione. 
    throw std::length_error("L'albero è vuoto in RemoveMax()");
}

/* ************************************************************************** */

// Restituisce il predecessore del valore dato nell'albero.
template <typename Data>
const Data& BST<Data>::Predecessor(const Data& element) const {
  // Trova il puntatore al nodo contenente il predecessore del valore dato e restituisce il suo valore.
  NodeLnk* const* nodePtr = &FindPointerToPredecessor(root,element);
  if (nodePtr != nullptr)
    return (*nodePtr)->elem;
  else
    // Se l'albero è vuoto, solleva un'eccezione.
    throw std::length_error("Predecessore non trovato in Predecessor()");
}

/* ************************************************************************** */

// Restituisce il predecessore del valore dato nell'albero e lo rimuove dall'albero.
template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& element){
  // Trova il puntatore al nodo contenente il predecessore del valore dato e lo rimuove dall'albero.
  NodeLnk** nodePtr = &FindPointerToPredecessor(root,element);
  if (nodePtr != nullptr)
    return DataNDelete(Detach(*nodePtr));
  else
    // Se l'albero è vuoto, solleva un'eccezione.
    throw std::length_error("Predecessore non trovato in PredecessorNRemove()");
}

/* ************************************************************************** */

// Rimuove il predecessore del valore dato nell'albero.
template <typename Data>
void BST<Data>::RemovePredecessor(const Data& element){
  // Trova il puntatore al nodo contenente il predecessore del valore dato e lo rimuove dall'albero.
  NodeLnk** nodePtr = &FindPointerToPredecessor(root,element);
  if (nodePtr != nullptr)
    delete Detach(*nodePtr);
  else
    // Se l'albero è vuoto, solleva un'eccezione.
    throw std::length_error("Predecessore non trovato in RemovePredecessor()");
}

/* ************************************************************************** */

// Restituisce il successore del valore dato nell'albero.
template <typename Data>
const Data& BST<Data>::Successor(const Data& element) const {
  // Trova il puntatore al nodo contenente il successore del valore dato e restituisce il suo valore.
  NodeLnk* const* nodePtr = &FindPointerToSuccessor(root,element);
  if(nodePtr != nullptr)
    return (*nodePtr)->elem;
  else
    // Se l'albero è vuoto, solleva un'eccezione.
    throw std::length_error("Successore non trovato in Successor()");
}

/* ************************************************************************** */

// Restituisce il successore del valore dato nell'albero e lo rimuove dall'albero.
template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& element){
  // Trova il puntatore al nodo contenente il successore del valore dato e lo rimuove dall'albero.
  NodeLnk** nodePtr = &FindPointerToSuccessor(root,element);
  if (nodePtr != nullptr)
    return DataNDelete(Detach(*nodePtr));
  else
    // Se l'albero è vuoto, solleva un'eccezione.
    throw std::length_error("Successore non trovato in SuccessorNRemove()");
}

/* ************************************************************************** */

// Rimuove il successore del valore dato nell'albero.
template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& element){
  // Trova il puntatore al nodo contenente il successore del valore dato e lo rimuove dall'albero.
  NodeLnk **nodePtr = &FindPointerToSuccessor(root, element);
  if (nodePtr != nullptr)
    delete Detach(*nodePtr);
  else
    // Se l'albero è vuoto, solleva un'eccezione.
    throw std::length_error("Successore non trovato in RemoveSuccessor()");
}

/* ************************************************************************** */
// DictionaryContainer functions

// Inserisce un nuovo elemento nell'albero binario di ricerca (BST) utilizzando la semantica di l-value.
template <typename Data>
bool BST<Data>::Insert(const Data& element){
  // Trova il puntatore al nodo che dovrebbe contenere l'elemento.
  NodeLnk*& nodePtr = FindPointerTo(root, element);
  // Se il puntatore è nullo, il nodo non esiste ancora e può essere creato.
  if (nodePtr == nullptr) {
    // Crea un nuovo nodo contenente l'elemento utilizzando una copia.
    nodePtr = new NodeLnk(element);
    size++; // Incrementa la dimensione dell'albero.

    return true; // Restituisce true per indicare che l'inserimento è avvenuto con successo.

  }
  
  return false; // Se il puntatore non è nullo, l'elemento esiste già., restituisce false per indicare che l'inserimento non è avvenuto
}

/* ************************************************************************** */

// Inserisce un nuovo elemento nell'albero binario di ricerca (BST) utilizzando la semantica di r-value.
template <typename Data>
bool BST<Data>::Insert(Data&& element){
  // Trova il puntatore al nodo che dovrebbe contenere l'elemento.
  NodeLnk*& nodePtr = FindPointerTo(root, element);
  // Se il puntatore è nullo, il nodo non esiste ancora e può essere creato.
  if (nodePtr == nullptr) {
    // Crea un nuovo nodo contenente l'elemento utilizzando il trasferimento di proprietà.
    nodePtr = new NodeLnk(std::move(element));
    size++; // Incrementa la dimensione dell'albero.
    return true; // Restituisce true per indicare che l'inserimento è avvenuto con successo.

  }
  
  return false; // Se il puntatore è nullo,non esiste nell'albero e non può essere rimosso. Restituisce false per indicare che l'inserimento non è avvenuta.

}

/* ************************************************************************** */

// Rimuove un elemento dall'albero binario di ricerca (BST).
template <typename Data>
bool BST<Data>::Remove(const Data& element) {
  // Trova il puntatore al nodo contenente l'elemento.
  NodeLnk*& nodePtr = FindPointerTo(root, element);
  // Se il puntatore non è nullo, il nodo esiste nell'albero
  if (nodePtr != nullptr) {
    // Rimuove il nodo e restituisce true per indicare che la rimozione è avvenuta con successo.
    delete Detach(nodePtr);
    return true;
  }
  
  return false;// Se il puntatore è nullo,non esiste nell'albero e non può essere rimosso. Restituisce false per indicare che la rimozione non è avvenuta.

}

/* ************************************************************************** */
// Exists

// Verifica se un elemento esiste nell'albero binario di ricerca (BST).
template <typename Data>
  // Trova il puntatore al nodo contenente l'elemento.
  bool BST<Data>::Exists(const Data& element) const noexcept {
  // Restituisce true se il puntatore non è nullo, altrimenti restituisce false.
  return (FindPointerTo(root, element) != nullptr);
}

/* ************************************************************************** */
// Auxiliary Member Functions

// Rimuove il nodo specificato e restituisce il valore contenuto nel nodo.
template <typename Data>
Data BST<Data>::DataNDelete(NodeLnk* node){
  // Crea una variabile temporanea per memorizzare il valore del nodo.
  Data value {};
  std::swap(value, node->elem); // Scambia il valore del nodo con la variabile temporanea.
  delete node; // Elimina il nodo.
  return value; // Restituisce il valore memorizzato nella variabile temporanea.
}

/* ************************************************************************** */

// Rimuove il nodo specificato dall'albero e restituisce il nodo rimosso.
template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& node) noexcept {
  // Verifica se il nodo non è nullo.
  if (node != nullptr) {
    // Se il nodo non ha solo un figlio sinistro, esegue il "passo a destra".
    if (node->l_child == nullptr)
      return Skip2Right(node);
    // Se il nodo non ha solo un figlio destro, esegue il "passo a sinistra".
    else if (node->r_child == nullptr)
      return Skip2Left(node);
    // Se il nodo ha entrambi i figli, esegue il "passo al massimo" nel sottoalbero sinistro.  
    else {
      // Trova il massimo nel sottoalbero sinistro.
      NodeLnk *max = DetachMax(node->l_child);
      // Scambia il valore del nodo corrente con il valore del massimo trovato.
      std::swap(node->elem, max->elem);
      return max; // Restituisce il nodo massimo che è stato rimosso.
    }
  }
  return nullptr; // Se il nodo è nullo, restituisce nullptr.
}

/* ************************************************************************** */

// Rimuove il nodo con il valore minimo nell'albero e restituisce il nodo rimosso.
template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& node) noexcept {
  // Trova il puntatore al nodo con il valore minimo e restituisce il nodo rimosso eseguendo un "passo a destra".
  return Skip2Right(FindPointerToMin(node));
}

// Rimuove il nodo con il valore massimo nell'albero e restituisce il nodo rimosso.
template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& node) noexcept {
  // Trova il puntatore al nodo con il valore massimo e restituisce il nodo rimosso eseguendo un "passo a sinistra".
  return Skip2Left(FindPointerToMax(node));
}

/* ************************************************************************** */

// Sposta il nodo corrente verso sinistra nell'albero e restituisce il nuovo figlio sinistro.
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk*& currentNode) noexcept {
  // Crea un puntatore temporaneo per il nuovo figlio sinistro.
  NodeLnk* newLeftChild = nullptr;
  // Verifica se il nodo corrente non è nullo.
  if (currentNode != nullptr) {
    // Scambia il puntatore al figlio sinistro del nodo corrente con il puntatore temporaneo.
    std::swap(newLeftChild, currentNode->l_child);
    // Scambia il nodo corrente con il suo figlio sinistro.
    std::swap(newLeftChild, currentNode);
    size--; // Decrementa la dimensione dell'albero.
  }
  
  return newLeftChild; // Restituisce il puntatore al nuovo figlio sinistro.
}

/* ************************************************************************** */

// Sposta il nodo corrente verso destra nell'albero e restituisce il nuovo figlio destro.
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(NodeLnk*& currentNode) noexcept {
  // Crea un puntatore temporaneo per il nuovo figlio destro.
  NodeLnk* newRightChild = nullptr;
  // Verifica se il nodo corrente non è nullo.
  if (currentNode != nullptr) {
    // Scambia il puntatore al figlio destro del nodo corrente con il puntatore temporaneo.
    std::swap(newRightChild, currentNode->r_child);
    // Scambia il nodo corrente con il suo figlio destro.
    std::swap(newRightChild, currentNode);
    size--; // Decrementa la dimensione dell'albero.

  }
  
  return newRightChild;  // Restituisce il puntatore al nuovo figlio destro.
}

/* ************************************************************************** */

// Trova il puntatore al nodo contenente il valore minimo nell'albero a partire dal nodo corrente.
template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& currentNode) const noexcept {
  // Inizializza un puntatore costante al puntatore al nodo minimo con il nodo corrente.
  NodeLnk* const* pointerToMin = &currentNode;
  // Inizializza un puntatore al nodo corrente.
  NodeLnk* current = currentNode;
  // Verifica se il nodo corrente non è nullo.
  if(current != nullptr) {
    // Continua a iterare verso sinistra fino a raggiungere il nodo con il valore minimo.
    while(current->l_child != nullptr) {
      pointerToMin = &current->l_child; // Aggiorna il puntatore al puntatore al nodo minimo.
      current = current->l_child; // Aggiorna il puntatore al nodo corrente.
    }
  }
  
  return *pointerToMin; // Restituisce il puntatore al nodo contenente il valore minimo.
}

/* ************************************************************************** */

// Trova il puntatore al nodo contenente il valore massimo nell'albero a partire dal nodo corrente.
template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& currentNode) const noexcept {
  // Inizializza un puntatore costante al puntatore al nodo massimo con il nodo corrente.
  NodeLnk* const* pointerToMax = &currentNode;
  // Inizializza un puntatore al nodo corrente.
  NodeLnk* current = currentNode;
  // Verifica se il nodo corrente non è nullo.
  if(current != nullptr) {
    // Continua a iterare verso destra fino a raggiungere il nodo con il valore massimo.
    while(current->r_child != nullptr) {
      pointerToMax = &current->r_child; // Aggiorna il puntatore al puntatore al nodo massimo.
      current = current->r_child; // Aggiorna il puntatore al nodo corrente.

    }
  }
  
  return *pointerToMax; // Restituisce il puntatore al nodo contenente il valore massimo.
}

/* ************************************************************************** */

// Trova il puntatore al nodo contenente il valore minimo nell'albero (versione non costante).
template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& node) noexcept {
  // Utilizza una conversione di tipo per richiamare la versione costante della funzione e rimuove la costante con const_cast.
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(node));
}

/* ************************************************************************** */

// Trova il puntatore al nodo contenente il valore massimo nell'albero (versione non costante).
template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& node) noexcept {
  // Utilizza una conversione di tipo per richiamare la versione costante della funzione e rimuove la costante con const_cast.
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(node));
}

/* ************************************************************************** */

// Trova il puntatore al nodo contenente l'elemento specificato nell'albero a partire dal nodo corrente.
template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& node, Data element) const noexcept {
  NodeLnk *const *nodePtr = &node;
  NodeLnk *current = node;
  // Continua a iterare fino a trovare il nodo con l'elemento specificato o raggiungere la fine dell'albero.
  while (current != nullptr) {
    // Se l'elemento specificato è maggiore dell'elemento nel nodo corrente, muoviti verso destra nell'albero.
    if (element > current->elem) {
      nodePtr = &current->r_child;
      current = current->r_child;
    }
    // Se l'elemento specificato è minore dell'elemento nel nodo corrente, muoviti verso sinistra nell'albero.
    else if (element < current->elem) {
      nodePtr = &current->l_child;
      current = current->l_child;
    }
    // Se l'elemento specificato è uguale all'elemento nel nodo corrente, esci dal ciclo.
    else
      break;
  }

  return *nodePtr;  // Restituisce il puntatore al nodo contenente l'elemento specificato.
}

/* ************************************************************************** */

// Trova il puntatore al nodo contenente l'elemento specificato nell'albero a partire dal nodo corrente (versione non costante).
template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& node, Data element) noexcept {
  // Utilizza una conversione di tipo per chiamare la versione costante della funzione e rimuovere la costante con const_cast.
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(node, element));
}

/* ************************************************************************** */

// Trova il puntatore al nodo contenente il predecessore dell'elemento specificato nell'albero a partire dal nodo corrente.
template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(NodeLnk* const& node, Data element) const noexcept {
  NodeLnk *const *predecessore = nullptr;
  NodeLnk *const *current = &node;
  // Continua a iterare finché non trova il nodo con l'elemento specificato o raggiunge la fine dell'albero.
  while ((*current) != nullptr && (*current)->elem != element) {
    // Se l'elemento nel nodo corrente è maggiore dell'elemento specificato, muoviti verso sinistra nell'albero.
    if ((*current)->elem > element) {
      current = &(*current)->l_child;
    }
    // Se l'elemento nel nodo corrente è minore dell'elemento specificato, memorizza il nodo corrente come predecessore e muoviti verso destra nell'albero.
    else if ((*current)->elem < element) {
      predecessore = current;
      current = &(*current)->r_child;
    }
  }
  // Se il nodo con l'elemento specificato è stato trovato e ha un sottoalbero sinistro, trova il massimo nel sottoalbero sinistro e memorizza il suo puntatore come predecessore.
  if ((*current) != nullptr && (*current)->l_child != nullptr)
    predecessore = &FindPointerToMax((*current)->l_child);
  
  return *predecessore; // Restituisce il puntatore al predecessore.
}

/* ************************************************************************** */

// Trova il puntatore al nodo contenente il successore dell'elemento specificato nell'albero a partire dal nodo corrente.
template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(NodeLnk* const& node, Data element) const noexcept {
  typename BST<Data>::NodeLnk *const *successor = nullptr;
  typename BST<Data>::NodeLnk *const *current = &node;
  // Continua a iterare finché non trova il nodo con l'elemento specificato o raggiunge la fine dell'albero.
  while ((*current) != nullptr && (*current)->elem != element) {
    // Se l'elemento nel nodo corrente è minore dell'elemento specificato, muoviti verso destra nell'albero.
    if ((*current)->elem < element)
      current = &(*current)->r_child;
    // Se l'elemento nel nodo corrente è maggiore dell'elemento specificato, memorizza il nodo corrente come successore e muoviti verso sinistra nell'albero.
    else if ((*current)->elem > element) {
      successor = current;
      current = &(*current)->l_child;
    }
  }
  // Se il nodo con l'elemento specificato è stato trovato e ha un sottoalbero destro, trova il minimo nel sottoalbero destro e memorizza il suo puntatore come successore.
  if ((*current) != nullptr && (*current)->r_child != nullptr)
    successor = &FindPointerToMin((*current)->r_child);
  
  return *successor; // Restituisce il puntatore al successore.
}

/* ************************************************************************** */

// Trova il puntatore al nodo contenente il predecessore dell'elemento specificato nell'albero a partire dal nodo corrente (versione non costante).
template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(NodeLnk*& node, Data element) noexcept {
  // Utilizza una conversione di tipo per chiamare la versione costante della funzione e rimuovere la costante con const_cast.
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(node, element));
}

// Trova il puntatore al nodo contenente il successore dell'elemento specificato nell'albero a partire dal nodo corrente (versione non costante).
template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(NodeLnk*& node, Data element) noexcept {
  // Utilizza una conversione di tipo per chiamare la versione costante della funzione e rimuovere la costante con const_cast.
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(node, element));
}

/* ************************************************************************** */


};
