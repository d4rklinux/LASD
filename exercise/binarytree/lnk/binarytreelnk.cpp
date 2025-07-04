#include "binarytreelnk.hpp"

namespace lasd {

/* ************************************************************************** */

// Costruttore di copia per un nodo di un albero binario
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& nodeLnk){
    // Copia il dato contenuto nel nodo
    elem = nodeLnk.elem;

    // Se il nodo ha un figlio sinistro
    if(nodeLnk.l_child != nullptr)
        // Crea una copia ricorsiva del figlio sinistro
        l_child = new NodeLnk(*nodeLnk.l_child);
    // Se il nodo non ha un figlio sinistro
    else
        // Assegna nullptr al figlio sinistro del nuovo nodo
        l_child = nullptr;

    // Se il nodo ha un figlio destro
    if(nodeLnk.r_child != nullptr)
        // Crea una copia ricorsiva del figlio destro
        r_child = new NodeLnk(*nodeLnk.r_child);
    // Se il nodo non ha un figlio destro
    else
        // Assegna nullptr al figlio destro del nuovo nodo
        r_child = nullptr;
}

/* ************************************************************************** */

// Costruttore di spostamento per un nodo di un albero binario
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk&& nodeLnk) noexcept {
    // Scambia il dato del nodo con quello del nodo riferito
    std::swap(elem, nodeLnk.elem);
    // Scambia il puntatore al figlio sinistro con quello del nodo riferito
    std::swap(l_child, nodeLnk.l_child);
    // Scambia il puntatore al figlio destro con quello del nodo riferito
    std::swap(r_child, nodeLnk.r_child);
}


/* ************************************************************************** */

// Operatore di assegnamento per un nodo di un albero binario
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk &nodeLnk) {
    // Assegna il dato del nodo al dato del nodo riferito
    elem = nodeLnk.elem;
    // Restituisce il riferimento a se stesso
    return *this;
}

/* ************************************************************************** */

// Operatore di assegnamento per un nodo di un albero binario tramite movimento
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk &&nodeLnk) noexcept {
    // Scambia il dato del nodo con quello del nodo riferito
    std::swap(elem, nodeLnk.elem);
    // Restituisce il riferimento a se stesso
    return *this;
}

/* ************************************************************************** */

// Restituisce il figlio destro di un nodo
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild(){
    // Se il nodo ha un figlio destro, restituisce il riferimento ad esso
    if(HasRightChild())
        return *r_child;
    // Se il nodo non ha un figlio destro, lancia un'eccezione
    else
        throw std::out_of_range("NodeLnk non ha figlio destro in RightChild()");
}

/* ************************************************************************** */

// Restituisce il figlio destro costante di un nodo
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
    // Se il nodo ha un figlio destro, restituisce il riferimento costante ad esso
    if(HasRightChild())
        return *r_child;
    // Se il nodo non ha un figlio destro, lancia un'eccezione
    else
        throw std::out_of_range("NodeLnk non ha figlio destro in RightChild()");
}

/* ************************************************************************** */

// Restituisce il figlio sinistro di un nodo
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild(){
    // Se il nodo ha un figlio sinistro, restituisce il riferimento ad esso
    if(HasLeftChild())
        return *l_child;
    // Se il nodo non ha un figlio sinistro, lancia un'eccezione
    else
        throw std::out_of_range("NodeLnk non ha figlio sinistro in LeftChild()");
}

/* ************************************************************************** */

// Restituisce il figlio sinistro costante di un nodo
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
    // Se il nodo ha un figlio sinistro, restituisce il riferimento costante ad esso
    if(HasLeftChild())
        return *l_child;
    // Se il nodo non ha un figlio sinistro, lancia un'eccezione
    else
        throw std::out_of_range("NodeLnk non ha figlio sinistro in LeftChild()");
}

/* ************************************************************************** */

// Costruttore che crea un albero binario da un altro albero traversabile
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data> &anotherBinaryTreeLnk) {
    // Ottiene la dimensione dell'altro albero
    size = anotherBinaryTreeLnk.Size();
    // Crea una coda di puntatori a nodi
    QueueLst<NodeLnk**> queue;
    // Accoda il puntatore alla radice dell'albero
    queue.Enqueue(&root);
    // Attraversa l'altro albero
    anotherBinaryTreeLnk.Traverse(
        [&queue](const Data& newData){
            // Ottiene il puntatore al nodo corrente dalla testa della coda e lo deaccoda
            NodeLnk *& currentNode = *queue.HeadNDequeue();
            // Crea un nuovo nodo con i dati correnti
            currentNode = new NodeLnk(newData);
            // Accoda i puntatori ai figli sinistro e destro del nodo corrente
            queue.Enqueue(&currentNode->l_child);
            queue.Enqueue(&currentNode->r_child);
        }
    );
}

/* ************************************************************************** */

// Costruttore che crea un albero binario da un altro albero mappabile tramite movimento
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data> &&anotherBinaryTreeLnk) noexcept {
    // Ottiene la dimensione dell'altro albero
    size = anotherBinaryTreeLnk.Size();
    // Crea una coda di puntatori a nodi
    QueueLst<NodeLnk**> queue;
    // Accoda il puntatore alla radice dell'albero
    queue.Enqueue(&root);
    // Mappa i dati dell'altro albero
    anotherBinaryTreeLnk.Map(
        [&queue](Data& newData){
            // Ottiene il puntatore al nodo corrente dalla testa della coda e lo deaccoda
            NodeLnk *& currentNode = *queue.HeadNDequeue();
            // Crea un nuovo nodo con i dati correnti tramite movimento
            currentNode = new NodeLnk(std::move(newData));
            // Accoda i puntatori ai figli sinistro e destro del nodo corrente
            queue.Enqueue(&currentNode->l_child);
            queue.Enqueue(&currentNode->r_child);
        }
    );
}

/* ************************************************************************** */

// Costruttore di copia per un albero binario
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk &anotherBinaryTreeLnk){
    // Se l'altro albero non è vuoto
    if(anotherBinaryTreeLnk.root != nullptr) {
        // Crea una copia del nodo radice dell'altro albero
        root = new NodeLnk(*anotherBinaryTreeLnk.root);
        // Assegna la dimensione dell'altro albero
        size = anotherBinaryTreeLnk.Size();
    }   
}

/* ************************************************************************** */

// Costruttore di spostamento per un albero binario
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& anotherBinaryTreeLnk) noexcept {
    // Scambia il puntatore alla radice e la dimensione con quelli dell'altro albero
    std::swap(root, anotherBinaryTreeLnk.root);
    std::swap(size, anotherBinaryTreeLnk.size);
}


/* ************************************************************************** */

// Operatore di assegnamento per un albero binario
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk& anotherBinaryTreeLnk) {
    // Cancella il contenuto dell'albero corrente
    Clear();
    // Se l'altro albero non è vuoto
    if (anotherBinaryTreeLnk.root != nullptr){
        // Crea una copia del nodo radice dell'altro albero
        root = new NodeLnk(*anotherBinaryTreeLnk.root);
        // Assegna la dimensione dell'altro albero
        size = anotherBinaryTreeLnk.Size();
    }
    return *this;
}

/* ************************************************************************** */

// Operatore di assegnamento tramite movimento per un albero binario
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk&& anotherBinaryTreeLnk) noexcept {
    // Scambia il puntatore alla radice e la dimensione con quelli dell'altro albero
    std::swap(root, anotherBinaryTreeLnk.root);
    std::swap(size, anotherBinaryTreeLnk.size);
    return *this;
}

/* ************************************************************************** */

// Restituisce il nodo radice costante dell'albero
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
    // Se l'albero non è vuoto, restituisce il riferimento costante al nodo radice
    if(!(this->Empty()))
        return *root;
    // Se l'albero è vuoto, lancia un'eccezione
    else
        throw std::length_error("L'albero è vuoto in Root()");
};

/* ************************************************************************** */

// Restituisce il nodo radice dell'albero
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() {
    // Se l'albero non è vuoto, restituisce il riferimento al nodo radice
    if(!(this->Empty()))
        return *root;
    // Se l'albero è vuoto, lancia un'eccezione
    else
        throw std::length_error("L'albero è vuoto in Root()");
};

/* ************************************************************************** */

// Cancella tutto il contenuto dell'albero
template <typename Data>
void BinaryTreeLnk<Data>::Clear() noexcept {
    // Se l'albero non è vuoto
    if (root != nullptr){
        // Cancella ricorsivamente il nodo radice e tutti i suoi discendenti
        delete root;
        // Imposta il puntatore alla radice a nullptr
        root = nullptr;
    }
    // Imposta la dimensione dell'albero a 0
    size = 0;
}

/* ************************************************************************** */

}
