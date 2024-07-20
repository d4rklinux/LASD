
namespace lasd {

/* ************************************************************************** */

// Definizione della funzione Fold all'interno della classe TraversableContainer
template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> function, Accumulator initial) const {
   
    // Iterazione attraverso gli elementi e applicazione della funzione func
    Traverse([&](const Data& element) {
        initial = function(element, initial);
    });
    // Ritorno del risultato accumulato
    return initial;
}

/* ************************************************************************** */

// Implementazione della funzione Exists all'interno della classe TraversableContainer
template <typename Data>
inline bool TraversableContainer<Data>::Exists(const Data& element) const noexcept
{
    // Inizializzazione del risultato a falso
    bool risultato = false;
    // Verifica se l'elemento esiste attraverso l'iterazione attraverso gli elementi
    Traverse([&risultato, element](const Data& dat) { risultato |= (dat == element); });
    // Ritorno del risultato
    return risultato;
}

/* ************************************************************************** */

// Implementazione della funzione Traverse per PreOrderTraversableContainer
template <typename Data>
void PreOrderTraversableContainer<Data>::Traverse(TraverseFun function) const {
    // Utilizzo della funzione PreOrderTraverse
    PreOrderTraverse(function);
}

/* ************************************************************************** */

// Implementazione della funzione PreOrderFold per PreOrderTraversableContainer
template <typename Data>
template <typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> function, Accumulator initial) const {
    
    // Iterazione attraverso gli elementi in preordine e applicazione della funzione func
    PreOrderTraverse([&](const Data& element) {
        initial = function(element, initial);
    });
    
    return initial; // Ritorno del risultato accumulato
}

/* ************************************************************************** */

// Implementazione della funzione Traverse per PostOrderTraversableContainer
template <typename Data>
void PostOrderTraversableContainer<Data>::Traverse(TraverseFun function) const {
    // Utilizzo della funzione PostOrderTraverse
    PostOrderTraverse(function);
}

/* ************************************************************************** */

// Implementazione della funzione PostOrderFold per PostOrderTraversableContainer
template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> function, Accumulator initial) const {
   
    // Iterazione attraverso gli elementi in postordine e applicazione della funzione func
    PostOrderTraverse([&](const Data& element) {
        initial = function(element, initial);
    });
    return initial; // Ritorno del risultato accumulato
}

/* ************************************************************************** */

// Funzione membro per attraversare il contenitore con una funzione di attraversamento specificata.
template <typename Data>
inline void InOrderTraversableContainer<Data>::Traverse(TraverseFun function) const {
    InOrderTraverse(function);
  }

/* ************************************************************************** */

// Applica una funzione specificata a ogni elemento del contenitore in ordine, consentendo una piegatura dei risultati.
template <typename Data>
template <typename Accumulator>
inline Accumulator InOrderTraversableContainer<Data>::InOrderFold(FoldFun<Accumulator> function, Accumulator initial) const {
    InOrderTraverse([&](const Data& element) {
      initial = function(element, initial); // Applica la funzione specificata a ciascun elemento nel contenitore in ordine.
    });
    return initial; // Restituisce il valore accumulato finale.
  }

/* ************************************************************************** */

// Funzione membro per attraversare il contenitore con una funzione di attraversamento specificata.
  template <typename Data>
  inline void BreadthTraversableContainer<Data>::Traverse(TraverseFun function) const {
    BreadthTraverse(function);  // Chiama la funzione di attraversamento in ampiezza.
  }

/* ************************************************************************** */
  
// Applica la funzione fornita a ogni elemento del contenitore seguendo un attraversamento in ampiezza.  
  template <typename Data>
  template <typename Accumulator>
  inline Accumulator BreadthTraversableContainer<Data>::BreadthFold(FoldFun<Accumulator> function, Accumulator initial) const {
    BreadthTraverse([&](const Data& element) {
      initial = function(element, initial); // Applica la funzione specificata a ciascun elemento nel contenitore in ampiezza.
    });
    return initial; // Restituisce il valore accumulato finale.
  }

/* ************************************************************************** */


}
