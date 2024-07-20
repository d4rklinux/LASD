#include "binarytreevec.hpp"

namespace lasd {

/* ************************************************************************** */

// Costruttore di un nodo per un albero binario implementato con vettori
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data &data, unsigned long int index, BinaryTreeVec<Data>* BT) {
    // Assegna il puntatore all'albero binario
    this->BT = BT;
    // Assegna il dato al vettore degli elementi dell'albero all'indice specificato
    BT->elements[index] = data;  
    // Assegna l'indice del nodo
    this->index = index;
}

/* ************************************************************************** */

// Costruttore di spostamento di un nodo per un albero binario implementato con vettori
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& data, unsigned long int index, BinaryTreeVec<Data>* BT) noexcept {
    // Assegna il puntatore all'albero binario
    this->BT = BT;
    // Sostituisce il dato nell'albero binario al dato specificato tramite movimento
    std::swap(BT->data[index], data);
    // Assegna l'indice del nodo
    this->index = index;
}

/* ************************************************************************** */

// Verifica se il nodo ha un figlio sinistro
template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    // Restituisce true se l'indice del figlio sinistro è valido e non è un puntatore nullo
    return (index * 2 + 1 < (BT->NodeArray).Size()) && ((BT->NodeArray)[index * 2 + 1] != nullptr);
}

/* ************************************************************************** */

// Verifica se il nodo ha un figlio destro
template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    // Restituisce true se l'indice del figlio destro è valido e non è un puntatore nullo
    return index * 2 + 2 < (BT->NodeArray).Size() && (BT->NodeArray)[index * 2 + 2] != nullptr;
}

/* ************************************************************************** */

// Restituisce il figlio sinistro costante del nodo
template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    // Se il nodo ha un figlio sinistro, restituisce il riferimento costante ad esso
    if(HasLeftChild())
        return *(BT->NodeArray[index * 2 + 1]);
    // Se il nodo non ha un figlio sinistro, lancia un'eccezione
    else
        throw std::out_of_range("Non esiste figlio sinistro in NodeVec::LeftChild()");
}

/* ************************************************************************** */

// Restituisce il figlio sinistro del nodo
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() {
    // Se il nodo ha un figlio sinistro, restituisce il riferimento ad esso
    if(HasLeftChild())
        return *(BT->NodeArray[index * 2 + 1]);
    // Se il nodo non ha un figlio sinistro, lancia un'eccezione
    else
        throw std::out_of_range("Non esiste figlio sinistro in NodeVec::LeftChild()");
}

/* ************************************************************************** */

// Restituisce il figlio destro costante del nodo
template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    // Se il nodo ha un figlio destro, restituisce il riferimento costante ad esso
    if(HasRightChild())
        return *(BT->NodeArray[index * 2 + 2]);
    // Se il nodo non ha un figlio destro, lancia un'eccezione
    else
        throw std::out_of_range("Non esiste figlio destro in NodeVec::RightChild()");
}

/* ************************************************************************** */

// Restituisce il figlio destro del nodo
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() {
    // Se il nodo ha un figlio destro, restituisce il riferimento ad esso
    if(HasRightChild())
        return *(BT->NodeArray[index * 2 + 2]);
    // Se il nodo non ha un figlio destro, lancia un'eccezione
    else
        throw std::out_of_range("Non esiste figlio destro in NodeVec::RightChild()");
}

/* ************************************************************************** */

// Costruttore che crea un albero binario da un contenitore attraversabile
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& container) {
    // Ridimensiona l'albero per ospitare la dimensione del contenitore
    this->Resize(container.Size());
    // Ridimensiona l'array di nodi per ospitare la dimensione del contenitore
    NodeArray.Resize(container.Size());
    int index = 0;
    // Imposta la dimensione dell'albero alla dimensione del contenitore
    this->size = container.Size();
    // Attraversa il contenitore e crea un nodo per ogni elemento
    container.Traverse(
        [this, &index](const Data& data){
            // Crea un nuovo nodo e lo inserisce nell'array di nodi
            this->NodeArray[index] = new NodeVec(data, index, this);
            // Incrementa l'indice
            index++;
        }
    );
}

/* ************************************************************************** */

// Costruttore che crea un albero binario da un contenitore mappabile tramite movimento
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& container) noexcept {
    // Ridimensiona l'albero per ospitare la dimensione del contenitore
    this->Resize(container.Size());
    // Ridimensiona l'array di nodi per ospitare la dimensione del contenitore
    NodeArray.Resize(container.Size());
    int index = 0;
    // Attraversa il contenitore e crea un nodo per ogni elemento tramite movimento
    container.Map(
        [this, &index](Data& data){
            // Crea un nuovo nodo e lo inserisce nell'array di nodi tramite movimento
            this->NodeArray[index] = new NodeVec(std::move(data), index, this);
            // Incrementa l'indice
            index++;
        }
    );
}

/* ************************************************************************** */

// Costruttore di copia per un albero binario
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& anotherBinaryTree) {
    // Cancella il contenuto dell'albero corrente
    this->Clear();
    // Ridimensiona l'albero per ospitare la dimensione dell'altro albero
    this->Resize(anotherBinaryTree.Size());
    // Ridimensiona l'array di nodi per ospitare la dimensione dell'altro albero
    NodeArray.Resize(anotherBinaryTree.Size());
    // Itera su tutti gli elementi dell'altro albero e crea un nodo per ciascuno di essi
    for(unsigned long int index = 0; index < this->Size(); index++)
        NodeArray[index] = new NodeVec(anotherBinaryTree.elements[index], index, this);
}

/* ************************************************************************** */

// Costruttore di spostamento per un albero binario
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& anotherBinaryTree) noexcept {
    // Scambia la dimensione con quella dell'altro albero
    std::swap(this->size, anotherBinaryTree.size);
    // Scambia gli elementi con quelli dell'altro albero
    std::swap(elements, anotherBinaryTree.elements);
    // Scambia l'array di nodi con quello dell'altro albero
    std::swap(NodeArray, anotherBinaryTree.NodeArray);
    // Itera su tutti gli elementi e imposta il puntatore all'albero binario a this
    for(unsigned long int index = 0; index < size; index++) {
        NodeArray[index]->BT = this;
    }
}

/* ************************************************************************** */

// Distruttore dell'albero binario
template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec(){
    // Itera su tutti gli elementi dell'array di nodi
    for(unsigned long int index = 0; index < NodeArray.Size(); index++){
        // Se il nodo non è nullo, dealloca la memoria
        if(NodeArray[index] != nullptr)
            delete NodeArray[index];
    }
}

/* ************************************************************************** */

// Operatore di assegnamento per un albero binario
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec& anotherBinaryTree) {
    // Ridimensiona l'albero per ospitare la dimensione dell'altro albero
    this->Resize(anotherBinaryTree.Size());
    // Ridimensiona l'array di nodi per ospitare la dimensione dell'altro albero
    NodeArray.Resize(anotherBinaryTree.Size());
    // Itera su tutti gli elementi dell'altro albero e crea un nodo per ciascuno di essi
    for(unsigned long int index = 0; index < this->Size(); index++)
        NodeArray[index] = new NodeVec(anotherBinaryTree.elements[index], index, this);
    return *this;
}

/* ************************************************************************** */

// Operatore di assegnamento tramite movimento per un albero binario
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec &&anotherBinaryTree) noexcept {
    // Scambia gli elementi con quelli dell'altro albero
    std::swap(elements, anotherBinaryTree.elements);
    // Scambia l'array di nodi con quello dell'altro albero
    std::swap(NodeArray, anotherBinaryTree.NodeArray);
    // Scambia la dimensione con quella dell'altro albero
    std::swap(size, anotherBinaryTree.size);
    // Itera su tutti gli elementi e imposta il puntatore all'albero binario a this
    for(unsigned long int index = 0; index < size; index++) {
        NodeArray[index]->BT = this;
    }
    // Itera su tutti gli elementi dell'altro albero e imposta il puntatore all'albero binario a &anotherBinaryTree
    for(unsigned long int index = 0; index < anotherBinaryTree.size; index++) {
        anotherBinaryTree.NodeArray[index]->BT = &anotherBinaryTree;
    }
    return *this;
}

/* ************************************************************************** */

// Restituisce il nodo radice costante dell'albero
template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    // Se l'albero non è vuoto, restituisce il riferimento costante al nodo radice
    if(!this->Empty())
        return *NodeArray[0];
    // Se l'albero è vuoto, lancia un'eccezione
    else
        throw std::length_error("L'albero è vuoto in BinaryTreeVec<Data>::Root()");
}

/* ************************************************************************** */

// Restituisce il nodo radice dell'albero
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() {
    // Se l'albero non è vuoto, restituisce il riferimento al nodo radice
    if(!this->Empty())
        return *NodeArray[0];
    // Se l'albero è vuoto, lancia un'eccezione
    else
        throw std::length_error("L'albero è vuoto in BinaryTreeVec<Data>::Root()");
}

/* ************************************************************************** */

// Cancella tutto il contenuto dell'albero
template <typename Data>
inline void BinaryTreeVec<Data>::Clear(){
    // Itera su tutti gli elementi dell'array di nodi
    for(unsigned long int index = 0; index < this->Size(); index++){
        // Se il nodo non è nullo, dealloca la memoria e imposta il puntatore a nullptr
        if(NodeArray[index] != nullptr){
            delete NodeArray[index];
            NodeArray[index] = nullptr;
        }
    }
    // Cancella tutto il contenuto del vettore
    Vector<Data>::Clear();
}

/* ************************************************************************** */

}
