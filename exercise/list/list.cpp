#include <iostream>

namespace lasd {

/* ************************************************************************** */

// Costruttore che prende un oggetto TraversableContainer
template <typename Data>
List<Data>::List(const TraversableContainer<Data> &container) {
  // Attraversa il contenitore fornito e inserisce gli elementi alla fine della lista
  container.Traverse([this](const Data &currentData) {
    // Itera su tutti gli elementi dell'oggetto con una funzione lambda
    InsertAtBack(currentData); // Inserisce l'elemento alla fine della lista
  });
}

/* ************************************************************************** */

// Costruttore che prende un oggetto MappableContainer
template <typename Data> 
List<Data>::List(MappableContainer<Data> &&container) {
    // Applica la funzione lambda a tutti gli elementi del contenitore e li inserisce alla fine della lista
    container.Map([this](Data &currentData) {
        InsertAtBack(std::move(currentData)); // Inserisce l'elemento alla fine della lista
    });
}

/* ************************************************************************** */

// Costruttore di copia per la classe List
template <typename Data> 
List<Data>::List(const List<Data> &otherList) {
    // Se la lista originale è vuota, esce dalla funzione
    if (!(size = otherList.size))
        return;

    // Crea il primo nodo della nuova lista utilizzando il primo nodo della lista originale
    head = new Node(*(otherList.head));
    tail = head;

    // Copia gli elementi della lista originale nella nuova lista
    Node *temp = otherList.head->next;
    while (temp) {
        tail->next = new Node(*temp);
        tail = tail->next;
        temp = temp->next;
    }
}

/* ************************************************************************** */

// Costruttore di movimento per la classe List
template <typename Data> 
List<Data>::List(List &&otherList) {
    // Utilizza std::swap per scambiare i membri della lista corrente con quelli della lista originale
    std::swap(size, otherList.size);
    std::swap(head, otherList.head);
    std::swap(tail, otherList.tail);
}

/* ************************************************************************** */

// Operatore di assegnamento da un'altra lista
template <typename Data>
List<Data> &List<Data>::operator=(const List<Data> &otherList) {
    // Crea una copia temporanea della lista originale
    List<Data> temp{otherList};
    // Scambia i contenuti della lista temporanea con quelli della lista corrente
    std::swap(temp, *this);
    // Restituisce il riferimento alla lista corrente
    return *this;
}

/* ************************************************************************** */

// Operatore di assegnamento di movimento
template <typename Data>
List<Data> &List<Data>::operator=(List<Data> &&otherList) noexcept {
    // Utilizza std::swap per scambiare i membri della lista corrente con quelli della lista originale
    std::swap(size, otherList.size);
    std::swap(head, otherList.head);
    std::swap(tail, otherList.tail);
    // Restituisce il riferimento alla lista corrente
    return *this;
}

/* ************************************************************************** */

// Operatore di confronto ==
template <typename Data>
inline bool List<Data>::operator==(const List<Data> &otherList) const noexcept {
    // Verifica se le dimensioni delle liste sono diverse
    if (size != otherList.size)
        return false;
    // Puntatori temporanei per scorrere le due liste
    Node *temp = head, *temp2 = otherList.head;
    // Confronta elemento per elemento delle due liste
    while (temp != nullptr) {
        // Se i valori degli elementi correnti sono diversi, le liste non sono uguali
        if (temp->val != temp2->val)
            return false;
        // Passa all'elemento successivo nelle due liste
        temp = temp->next;
        temp2 = temp2->next;
    }
    return true; // Se il loop è terminato senza restituire false, le liste sono uguali

}

/* ************************************************************************** */

// Inserisce un elemento in testa alla lista
template <typename Data> 
void List<Data>::InsertAtFront(const Data &data) {
    // Crea un nuovo nodo con i dati forniti
    Node *temp = new Node(data);
    // Collega il nuovo nodo al nodo corrente della testa
    temp->next = head;
    // Aggiorna il puntatore alla testa della lista al nuovo nodo
    head = temp;
    // Se la lista era vuota, il nuovo nodo diventa anche la coda
    if (tail == nullptr)
        tail = head;
    ++size; // Incrementa il conteggio degli elementi nella lista
}

/* ************************************************************************** */

// Inserisce un elemento in testa alla lista utilizzando il movimento
template <typename Data> 
void List<Data>::InsertAtFront(Data &&data) {
    // Crea un nuovo nodo con i dati forniti utilizzando il movimento
    Node *temp = new Node(std::move(data));
    // Collega il nuovo nodo al nodo corrente della testa
    temp->next = head;
    // Aggiorna il puntatore alla testa della lista al nuovo nodo
    head = temp;
    // Se la lista era vuota, il nuovo nodo diventa anche la coda
    if (tail == nullptr)
        tail = head;
    ++size; // Incrementa il conteggio degli elementi nella lista
}

/* ************************************************************************** */

// Rimuove l'elemento in testa alla lista
template <typename Data> 
void List<Data>::RemoveFromFront() {
    // Se la lista è vuota, solleva un'eccezione
    if (!size)
        throw std::length_error("Impossibile rimuovere - lista vuota");
    
    // Memorizza il puntatore al nodo corrente della testa
    Node *temp{head};
    // Se c'è un solo elemento nella lista, aggiorna anche la coda
    head == tail ? head = tail = nullptr : head = head->next;
    // Disconnette il nodo dalla lista
    temp->next = nullptr;
    // Elimina il nodo
    delete temp;
    // Decrementa il conteggio degli elementi nella lista
    --size;
}

/* ************************************************************************** */

// Restituisce e rimuove l'elemento in testa alla lista
template <typename Data> 
Data List<Data>::FrontNRemove() {
    // Se la lista è vuota, solleva un'eccezione
    if (!size)
        throw std::length_error("Impossibile rimuovere - lista vuota");
    
    // Memorizza il puntatore al nodo corrente della testa
    Node *temp{head};
    // Se c'è un solo elemento nella lista, aggiorna anche la coda
    head == tail ? head = tail = nullptr : head = head->next;
    // Disconnette il nodo dalla lista
    temp->next = nullptr;
    // Ottiene i dati dal nodo e li memorizza in una variabile temporanea
    Data data{std::move(temp->val)};
    // Elimina il nodo
    delete temp;
    --size; // Decrementa il conteggio degli elementi nella lista
    return data; // Restituisce i dati memorizzati

}

/* ************************************************************************** */

// Inserisce un elemento alla fine della lista
template <typename Data> 
void List<Data>::InsertAtBack(const Data &data) {
    // Crea un nuovo nodo con i dati forniti
    Node *temp{new Node(data)};
    // Se la lista non è vuota, collega il nuovo nodo al nodo corrente della coda
    // Altrimenti, il nuovo nodo diventa sia la testa che la coda della lista
    size++ ? tail->next = temp : head = tail = temp;
    // Aggiorna il puntatore alla coda della lista al nuovo nodo
    tail = temp;
}

/* ************************************************************************** */

// Inserisce un elemento alla fine della lista utilizzando il movimento
template <typename Data> 
void List<Data>::InsertAtBack(Data &&data) {
    // Crea un nuovo nodo con i dati forniti utilizzando il movimento
    Node *temp{new Node(std::move(data))};
    // Se la lista non è vuota, collega il nuovo nodo al nodo corrente della coda
    // Altrimenti, il nuovo nodo diventa sia la testa che la coda della lista
    size++ ? tail->next = temp : head = tail = temp;
    // Aggiorna il puntatore alla coda della lista al nuovo nodo
    tail = temp;
}

/* ************************************************************************** */

// Inserisce un elemento alla fine della lista se non è già presente
template <typename Data> 
inline bool List<Data>::Insert(const Data &data) {
    // Verifica se l'elemento è già presente nella lista
    if (Exists(data)) {
        return false;
    }
    // Chiama la funzione per inserire l'elemento alla fine della lista utilizzando il movimento
    InsertAtBack(data);
    return true;
}

/* ************************************************************************** */

// Inserisce un elemento alla fine della lista utilizzando il movimento se non è già presente
template <typename Data> 
inline bool List<Data>::Insert(Data &&data) {
    // Verifica se l'elemento è già presente nella lista
    if (Exists(data)) {
        return false;
    }
    // Chiama la funzione per inserire l'elemento alla fine della lista utilizzando il movimento
    InsertAtBack(std::move(data));
    return true;
}

/* ************************************************************************** */

// Rimuove l'elemento dalla lista se presente
template <typename Data> 
inline bool List<Data>::Remove(const Data &data) {
  // Se la lista è vuota, non c'è nulla da rimuovere
  if (!size)
    return false;
  // Se l'elemento da rimuovere è il primo nella lista, rimuovilo dalla testa
  if (head->val == data) {
    RemoveFromFront();
    return true;
  }
  // Inizia dalla seconda posizione nella lista
  Node *current {head->next}, *previous {head};
  // Cicla attraverso la lista per trovare l'elemento da rimuovere
  while (current != nullptr) {
    // Se l'elemento corrente corrisponde a quello da rimuovere
    if (current->val == data) {
      // Collega l'elemento precedente all'elemento successivo
      previous->next = current->next;
      // Se l'elemento corrente è l'ultimo, aggiorna la coda
      current->next ? current->next = nullptr : tail = previous;
      // Libera la memoria occupata dall'elemento corrente
      delete current;
      // Riduci la dimensione della lista
      --size;
      return true;
    }
    // Passa all'elemento successivo nella lista
    previous = current;
    current = current->next;
  }
  return false; // Se l'elemento da rimuovere non è stato trovato nella lista
}

/* ************************************************************************** */

// Restituisce l'elemento all'indice specificato
template <typename Data> 
inline const Data &List<Data>::operator[](unsigned long index) const {
    // Verifica se l'indice specificato è valido
    if (index >= size)
        throw std::out_of_range("La lista non ha abbastanza elementi.");

    // Scorre la lista fino all'indice specificato
    Node *temp{head};
    for (unsigned int i = 0; i < index; ++i, temp = temp->next);
    // Restituisce il valore dell'elemento all'indice specificato
    return temp->val;
}

/* ************************************************************************** */

// Restituisce l'elemento all'indice specificato
template <typename Data> 
inline Data &List<Data>::operator[](unsigned long index) {
    // Verifica se l'indice specificato è valido
    if (index >= size)
        throw std::out_of_range("La lista non ha abbastanza elementi.");

    // Scorre la lista fino all'indice specificato
    Node *temp{head};
    for (unsigned int i = 0; i < index; ++i, temp = temp->next);
    
    return temp->val; // Restituisce il riferimento all'elemento all'indice specificato
}

/* ************************************************************************** */

// Restituisce l'elemento in testa alla lista
template <typename Data> 
inline const Data &List<Data>::Front() const {
    // Verifica se la lista non è vuota
    if (size)
        return head->val;
    // Se la lista è vuota, solleva un'eccezione
    throw std::length_error("Lista vuota.");
}

/* ************************************************************************** */

// Restituisce l'elemento in testa alla lista
template <typename Data> 
inline Data &List<Data>::Front() {
    // Verifica se la lista non è vuota
    if (size)
        return head->val;
    // Se la lista è vuota, solleva un'eccezione
    throw std::length_error("Lista vuota.");
}

/* ************************************************************************** */

// Restituisce l'elemento in coda alla lista
template <typename Data> 
inline const Data &List<Data>::Back() const {
    // Verifica se la lista non è vuota
    if (size)
        return tail->val;
    // Se la lista è vuota, solleva un'eccezione
    throw std::length_error("Lista vuota.");
}

/* ************************************************************************** */

// Restituisce l'elemento in coda alla lista
template <typename Data> 
inline Data &List<Data>::Back() {
    // Verifica se la lista non è vuota
    if (size)
        return tail->val;
    // Se la lista è vuota, solleva un'eccezione
    throw std::length_error("Lista vuota.");
}

/* ************************************************************************** */

// Esegue una traversata in pre-ordine sulla lista
template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun function, Node *current) const {
    // Verifica se il nodo corrente esiste
    if (!current)
        return;

    // Applica la funzione al valore del nodo corrente
    function(current->val);
    // Esegue la traversata ricorsivamente sul nodo successivo
    PreOrderTraverse(function, current->next);
}

/* ************************************************************************** */

// Esegue una traversata in post-ordine sulla lista
template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun function, Node *current) const {
    // Verifica se il nodo corrente esiste
    if (!current)
        return;

    // Esegue la traversata ricorsivamente sul nodo successivo
    PostOrderTraverse(function, current->next);
    // Applica la funzione al valore del nodo corrente
    function(current->val);
}

/* ************************************************************************** */

// Esegue una mappatura in pre-ordine sulla lista
template <typename Data>
void List<Data>::PreOrderMap(MapFun function, Node *current) const {
    // Verifica se il nodo corrente esiste
    if (!current)
        return;

    // Applica la funzione al valore del nodo corrente
    function(current->val);
    // Esegue la mappatura ricorsivamente sul nodo successivo
    PreOrderMap(function, current->next);
}

/* ************************************************************************** */

// Esegue una mappatura in post-ordine sulla lista
template <typename Data>
void List<Data>::PostOrderMap(MapFun function, Node *current) const {
    // Verifica se il nodo corrente esiste
    if (!current)
        return;

    // Esegue la mappatura ricorsivamente sul nodo successivo
    PostOrderMap(function, current->next);
    // Applica la funzione al valore del nodo corrente
    function(current->val);
}

/* ************************************************************************** */

}
