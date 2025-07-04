#include "htclsadr.hpp"

namespace lasd {

/* ************************************************************************** */

// Costruttore per inizializzare un'hash table con liste di collisione.
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long int new_size) {
    // Calcola la dimensione dell'array come potenza di due successiva a new_size.
    array_size = NextPowOf2(new_size);
    // Alloca l'array di liste di collisione e lo inizializza con liste vuote.
    array = new List<Data>[array_size] {};
}

/* ************************************************************************** */

// Costruttore per inizializzare un'hash table con liste di collisione utilizzando un contenitore mappabile.
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const MappableContainer<Data>& otherTable) : HashTableClsAdr(otherTable.Size()){
    // Inserisce tutti gli elementi del contenitore mappabile nell'hash table.
    InsertAll(otherTable);
}

/* ************************************************************************** */

// Costruttore per inizializzare un'hash table con liste di collisione utilizzando un contenitore mappabile e specificando una nuova dimensione.
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long int new_size, const MappableContainer<Data>& otherTable) : HashTableClsAdr(new_size) {
    // Inserisce tutti gli elementi del contenitore mappabile nell'hash table.
    InsertAll(otherTable);
}

/* ************************************************************************** */

// Costruttore di spostamento per inizializzare un'hash table con liste di collisione utilizzando un contenitore attraversabile.
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(TraversableContainer<Data>&& otherTable) noexcept : HashTableClsAdr(otherTable.Size()){
    // Inserisce tutti gli elementi del contenitore attraversabile nell'hash table.
    InsertAll(std::move(otherTable));
}

/* ************************************************************************** */

// Costruttore di spostamento per inizializzare un'hash table con liste di collisione utilizzando un contenitore attraversabile e specificando una nuova dimensione.
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long int new_size, TraversableContainer<Data>&& otherTable) noexcept : HashTableClsAdr(new_size) {
    // Inserisce tutti gli elementi del contenitore attraversabile nell'hash table.
    InsertAll(std::move(otherTable));
}

/* ************************************************************************** */

// Costruttore di copia per inizializzare un'hash table con liste di collisione utilizzando un'altra hash table come modello.
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& otherTable) : HashTable<Data>(otherTable){
    // Alloca un nuovo array di liste di collisione e lo inizializza con le liste di collisione dell'altro oggetto.
    array = new List<Data>[array_size] {};
    std::copy(otherTable.array, otherTable.array + array_size, array);
}

/* ************************************************************************** */

// Costruttore di spostamento per inizializzare un'hash table con liste di collisione utilizzando un'altra hash table tramite spostamento.
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& otherTable) noexcept : HashTable<Data>(std::move(otherTable)) {
    // Scambia l'array di liste di collisione con quello dell'altro oggetto.
    std::swap(array, otherTable.array);
}

/* ************************************************************************** */

// Operatore di assegnamento per copiare un'hash table con liste di collisione da un'altra.
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr& otherTable){
    // Chiama l'operatore di assegnamento della classe base e dealloca l'array esistente.
    HashTable<Data>::operator=(otherTable);
    delete[] array;
    // Alloca un nuovo array e copia le liste di collisione dall'altro oggetto.
    array = new List<Data>[array_size] {};
    for (unsigned long int i = 0; i < array_size; i++)
        array[i] = otherTable.array[i];
    
    return *this; // Restituisce un riferimento all'oggetto corrente.
}

/* ************************************************************************** */

// Operatore di assegnamento per spostare un'hash table con liste di collisione da un'altra.
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr&& otherTable) noexcept {
    // Chiama l'operatore di assegnamento della classe base e scambia l'array con quello dell'altro oggetto.
    HashTable<Data>::operator=(std::move(otherTable));
    std::swap(array, otherTable.array);
    return *this;
}

/* ************************************************************************** */

// Operatore di confronto per verificare l'uguaglianza tra due hash table con liste di collisione.
template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr& otherTable) const noexcept {
    // Verifica se le dimensioni delle hash table sono diverse.
    if (otherTable.size != this->size)
        return false;
    // Variabile per memorizzare il risultato del confronto.
    bool result = true; 
    // Scansione di tutte le liste di collisione dell'hash table corrente.
    for (unsigned long int i = 0; i < this->array_size; i++) {
        // Iterazione su tutti gli elementi della lista di collisione corrente.
        array[i].Traverse(
            // Funzione lambda per confrontare se ogni elemento della lista di collisione corrente esiste nell'altra hash table.
            [&otherTable, &result](const Data& data){
                result &= otherTable.Exists(data);
            }
        );
        // Se il risultato diventa falso, le hash table non sono uguali.
        if (result == false)
            return false;
    }
    return true; // Se tutte le liste di collisione sono uguali, le hash table sono uguali.

}

/* ************************************************************************** */

// Funzione per inserire un elemento nell'hash table con liste di collisione.
template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& element){
    // Calcola l'indice hash dell'elemento.
    unsigned long int index = this->HashKey(Hashable<Data>()(element));

    // Inserisce l'elemento nella lista di collisione corrispondente all'indice calcolato.
    if(array[index].Insert(element)){
        // Incrementa le dimensioni dell'hash table.
        size++;
        // Se il fattore di carico supera 0.8 o la lunghezza della lista supera la radice quadrata della dimensione dell'array,
        // raddoppia la dimensione dell'array.
        if(((float)size / array_size) > 0.8 || array[index].Size() > (floor(sqrt(array_size))))
            Resize(array_size * 2);    
        
        return true;
    }
    
    return false; // Restituisce false se l'inserimento non è riuscito.

}

/* ************************************************************************** */

// Funzione per inserire un elemento r-value nell'hash table con liste di collisione.
template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& element) noexcept {
    // Calcola l'indice hash dell'elemento.
    unsigned long int index = this->HashKey(Hashable<Data>()(element));

    // Inserisce l'elemento nella lista di collisione corrispondente all'indice calcolato utilizzando il forwarding di r-value.
    if(array[index].Insert(std::move(element))){
        // Incrementa le dimensioni dell'hash table.
        size++;

        // Se il fattore di carico supera 0.8 o la lunghezza della lista supera la radice quadrata della dimensione dell'array,
        // raddoppia la dimensione dell'array.
        if(((float)size / array_size) > 0.8 || array[index].Size() > (floor(sqrt(array_size))))
            Resize(array_size * 2); 
        return true;
    }
    
    return false; // Restituisce false se l'inserimento non è riuscito.
}

/* ************************************************************************** */

// Funzione per rimuovere un elemento dall'hash table con liste di collisione.
template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data& element){
    // Calcola l'indice hash dell'elemento.
    unsigned long int index = this->HashKey(Hashable<Data>()(element));
    // Rimuove l'elemento dalla lista di collisione corrispondente all'indice calcolato.
    if(array[index].List<Data>::Remove(element)){
        // Decrementa le dimensioni dell'hash table.
        size--;
        // Se le dimensioni dell'hash table sono inferiori a un quinto della dimensione dell'array e l'array non è di dimensione 32,
        // dimezza la dimensione dell'array.
        if(size < (array_size / 5) && array_size != 32)
            Resize(array_size / 2);
        
        return true;
    }
    
    return false; // Restituisce false se la rimozione non è riuscita.

}

/* ************************************************************************** */

// Funzione per verificare se un elemento esiste nell'hash table con liste di collisione.
template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data &element) const noexcept {
    // Calcola l'indice hash dell'elemento.
    unsigned long int index = this->HashKey(Hashable<Data>()(element));
    // Verifica se l'elemento esiste nella lista di collisione corrispondente all'indice calcolato.
    if(array[index].Exists(element))
        return true;
    
    return false; // Restituisce false se l'elemento non è stato trovato.

}

/* ************************************************************************** */

// Funzione per ridimensionare l'hash table con liste di collisione.
template <typename Data>
void HashTableClsAdr<Data>::Resize(const unsigned long int new_size){
    // Se la nuova dimensione è 0, esegue la cancellazione e ridimensiona a 32.
    if(new_size == 0){
        Clear();
        Resize(32);
        return;
    }
    // Calcola la nuova dimensione dell'array come potenza di due successiva alla nuova dimensione.
    unsigned long int temp_size = NextPowOf2(new_size);
    // Resetta le dimensioni dell'hash table.
    this->size = 0;

    // Alloca un nuovo array temporaneo.
    List<Data>* temp_vec = new List<Data>[temp_size] {};

    // Scambia l'array corrente con il nuovo array temporaneo.
    std::swap(temp_vec, array);
    std::swap(temp_size, array_size);

    // Inserisce tutti gli elementi dall'array temporaneo nell'hash table.
    for(unsigned long int i = 0; i < temp_size; i++)
        InsertAll(temp_vec[i]);

    // Dealloca l'array temporaneo.
    delete [] temp_vec;
}

/* ************************************************************************** */

// Funzione per cancellare tutti gli elementi dall'hash table con liste di collisione.
template <typename Data>
void HashTableClsAdr<Data>::Clear(){
    // Dealloca l'array corrente e crea un nuovo array di liste di collisione vuote con la stessa dimensione.
    delete [] array;
    array = new List<Data>[array_size];
    // Reimposta le dimensioni dell'hash table a 0.
    size = 0;
}

/* ************************************************************************** */

}
