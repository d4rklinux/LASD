/* ************************************************************************** */

#include "htopnadr.hpp"

/* ************************************************************************** */

namespace lasd {

// Costruttore della classe HashTableOpnAdr con dimensione specificata
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long int size) : HashTable<Data>()
{
    // Calcola la dimensione effettiva dell'array per la tabella hash
    array_size = NextPowOf2(size);

    // Alloca memoria per gli elementi della tabella hash e inizializza con valori di default
    Elements = new Data[array_size] {};

    // Alloca memoria per gli stati degli slot della tabella hash e inizializza con valori di default
    flagsArray = new std::bitset<2>[array_size] {};
}

/* ************************************************************************** */

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const MappableContainer<Data>& otherTable) : HashTableOpnAdr(otherTable.Size() * 2) {
    InsertAll(otherTable);
}

/* ************************************************************************** */

// Costruttore della classe HashTableOpnAdr con dimensione specificata e un'altra tabella hash da inserire
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long int size, const MappableContainer<Data>& otherTable) : HashTableOpnAdr(size) {
    // Inserisce tutti gli elementi della tabella hash otherTable nella tabella hash corrente
    InsertAll(otherTable);
}

/* ************************************************************************** */

// Costruttore di spostamento della classe HashTableOpnAdr da un altro contenitore traversabile
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(TraversableContainer<Data>&& otherTable) noexcept : HashTableOpnAdr(otherTable.Size() * 2) {
    // Inserisce tutti gli elementi del contenitore otherTable nella tabella hash corrente utilizzando il movimento
    InsertAll(std::move(otherTable));
}

/* ************************************************************************** */

// Costruttore della classe HashTableOpnAdr con dimensione specificata e un altro contenitore traversabile da inserire
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long int size, TraversableContainer<Data>&& otherTable) noexcept : HashTableOpnAdr(size) {
    // Inserisce tutti gli elementi del contenitore otherTable nella tabella hash corrente utilizzando il movimento
    InsertAll(std::move(otherTable));
}

/* ************************************************************************** */

// Costruttore di copia della classe HashTableOpnAdr da un'altra tabella hash
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& otherTable) : HashTable<Data>(otherTable) {
    // Alloca memoria per gli elementi della tabella hash e inizializza con valori di default
    Elements = new Data[array_size] {};
    // Alloca memoria per gli stati degli slot della tabella hash e inizializza con valori di default
    flagsArray = new std::bitset<2>[array_size] {};
    // Copia gli elementi e gli stati della tabella hash otherTable nella tabella hash corrente
    for(unsigned long int i=0; i<array_size; i++){
        Elements[i] = otherTable.Elements[i];
        flagsArray[i] = otherTable.flagsArray[i];
    }
}

/* ************************************************************************** */

// Costruttore di spostamento della classe HashTableOpnAdr da un'altra tabella hash
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& otherTable) noexcept : HashTable<Data>(std::move(otherTable)) {
    // Scambia i puntatori agli elementi e agli stati della tabella hash corrente con quelli della tabella hash otherTable
    std::swap(Elements, otherTable.Elements);
    std::swap(flagsArray, otherTable.flagsArray);
}

/* ************************************************************************** */

// Operatore di assegnamento dalla classe HashTableOpnAdr da un'altra tabella hash
template <typename Data>
HashTableOpnAdr<Data> &HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr& otherTable){
    // Assegna gli elementi della classe base
    HashTable<Data>::operator=(otherTable);
    // Dealloca la memoria per gli stati degli slot e per gli elementi della tabella hash corrente
    delete [] flagsArray;
    delete [] Elements;
    // Alloca nuova memoria per gli elementi e per gli stati della tabella hash corrente e inizializza con valori di default
    Elements = new Data[array_size] {};
    flagsArray = new std::bitset<2>[array_size] {};
    // Copia gli elementi e gli stati della tabella hash otherTable nella tabella hash corrente
    for(unsigned long int i = 0; i < array_size; i++){
        Elements[i] = otherTable.Elements[i];
        flagsArray[i] = otherTable.flagsArray[i];
    }

    return *this; //Ritorna riferimento a se steso
}

/* ************************************************************************** */

// Operatore di assegnamento: assegna un oggetto di tipo HashTableOpnAdr da un riferimento a un r-value.
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr&& otherTable) noexcept {
    // Chiamata all'operatore di assegnamento della classe base HashTable utilizzando std::move per ottimizzare gli spostamenti.
    HashTable<Data>::operator=(std::move(otherTable));
    // Scambio dei contenuti tra l'oggetto corrente e otherTable.
    std::swap(Elements, otherTable.Elements);
    std::swap(flagsArray, otherTable.flagsArray);

    return *this; // Restituzione di un riferimento all'oggetto corrente.

}

/* ************************************************************************** */

// Operatore di confronto: verifica l'uguaglianza tra due oggetti HashTableOpnAdr.
template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr& otherTable) const noexcept {
    // Verifica delle dimensioni degli array.
    if (size != otherTable.Size())
        return false;
    // Scansione degli elementi dell'array e confronto.
    for (unsigned long int i = 0; i < array_size; ++i) {
        // Verifica se tutti i flag sono impostati e se l'elemento corrente non esiste nell'altro array.
        if (flagsArray[i].all() && !otherTable.Exists(Elements[i]))
            return false;
    }
    
    return true; // Restituzione dell'esito del confronto.
}

/* ************************************************************************** */

// Funzione di inserimento di un elemento nell'hash table.
template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& data) {
    // Inizializzazione del parametro di probing.
    unsigned long int probe = 0;

    // Verifica se è necessario ridimensionare l'array.
    if (size * 2 >= array_size)
        Resize(array_size * 2);
    // Ricerca di un'area vuota nell'array.
    unsigned long int index = FindEmpty(probe, data);
    // Se l'area è vuota...
    if (flagsArray[index][1] == 0) {
        // Inserimento del dato e aggiornamento delle dimensioni.
        Elements[index] = data;
        size++;
        // Aggiornamento del conteggio degli elementi eliminati, se necessario.
        if (flagsArray[index][0] == 1)
            deleted_elements--;
        // Impostazione del flag e tentativo di rimuovere eventuali elementi eliminati.
        flagsArray[index].set();
        return !Remove(++probe, Elements[index]); 
    }
    probe = 0;
    return false; // Se l'area non è vuota, il dato non può essere inserito.

}

/* ************************************************************************** */

// Funzione di inserimento di un elemento r-value nell'hash table.
template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& data) {
    // Inizializzazione del parametro di probing.
    unsigned long int probe = 0;

    // Verifica se è necessario ridimensionare l'array.
    if (size * 2 >= array_size)
        Resize(array_size * 2);
    // Ricerca di un'area vuota nell'array.
    unsigned long int index = FindEmpty(probe, data);
    // Se l'area è vuota...
    if (flagsArray[index][1] == 0) {
        // Scambio dei dati e inserimento nell'array, quindi aggiornamento delle dimensioni.
        std::swap(Elements[index], data);
        size++;
        // Aggiornamento del conteggio degli elementi eliminati, se necessario.
        if (flagsArray[index][0] == 1)
            deleted_elements--;
        // Impostazione del flag e tentativo di rimuovere eventuali elementi eliminati.
        flagsArray[index].set();
        return !Remove(++probe, Elements[index]); 
    }
    // Se l'area non è vuota, il dato non può essere inserito.
    probe = 0;
    return false;
}

/* ************************************************************************** */

// Funzione di rimozione di un elemento dall'hash table.
template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& data) {
    unsigned long int probe = 0;
    
    return Remove(probe, data); // Chiamata alla funzione di rimozione con il parametro di probing inizializzato.
}

/* ************************************************************************** */

// Funzione che verifica se un dato esiste nell'hash table.
template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data &data) const noexcept {
    // Inizializzazione del parametro di probing e calcolo dell'indice hash.
    unsigned long int probe = 0;
    unsigned long int index = HashKey(Hashable<Data>()(data));

    return Find(index, probe, data); // Ricerca del dato utilizzando l'indice hash.
}

/* ************************************************************************** */

// Funzione di ridimensionamento dell'hash table.
template <typename Data>
void HashTableOpnAdr<Data>::Resize(const unsigned long int new_size) {
    // Se la nuova dimensione è 0, esegue la cancellazione.
    if (new_size == 0)
        Clear();

    // Calcola la nuova dimensione dell'array.
    unsigned long int temp_arraySize;
    if (new_size < size)
        temp_arraySize = NextPowOf2(size * 2);
    else
        temp_arraySize = NextPowOf2(new_size);

    // Crea temporanei per gli elementi e gli array dei flag.
    Data* temp_Elements = new Data[temp_arraySize]{};
    std::bitset<2>* temp_flagsArray = new std::bitset<2>[temp_arraySize]{};

    // Scambia le dimensioni degli array e gli array stessi.
    std::swap(temp_arraySize, array_size);
    std::swap(temp_Elements, Elements);
    std::swap(temp_flagsArray, flagsArray);

    // Reimposta le dimensioni e gli elementi eliminati.
    size = 0;
    deleted_elements = 0;
    // Reinserisce gli elementi nell'hash table.
    for (unsigned long int i = 0; i < temp_arraySize; ++i) {
        if (temp_flagsArray[i].all())
            Insert(std::move(temp_Elements[i]));
    }

    // Dealloca gli array temporanei.
    delete[] temp_Elements;
    delete[] temp_flagsArray;
}

/* ************************************************************************** */

// Funzione che cancella tutti gli elementi dall'hash table.
template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
    // Itera attraverso tutti gli elementi dell'array.
    for (unsigned long int i = 0; i < array_size; ++i) {
        // Se l'elemento è presente...
        if (flagsArray[i].all()) {
            // Incrementa il conteggio degli elementi eliminati e reimposta il flag di eliminazione.
            deleted_elements++;
            flagsArray[i][1] = 0;
        }
    }

    // Reimposta la dimensione dell'hash table a 0.
    size = 0;
    // Se il numero di elementi eliminati è maggiore di un quarto della dimensione dell'array, ridimensiona l'array.
    if (deleted_elements > (array_size / 4))
        Resize(array_size);
}

/* ************************************************************************** */

// Funzione per calcolare la chiave hash con probing quadrato per l'hash table.
template <typename Data>
unsigned long int HashTableOpnAdr<Data>::HashKey(unsigned long int& probe, const Data& key) const noexcept {
    // Calcolo dell'indice di partenza utilizzando la funzione hash.
    unsigned long int starting_index = HashKey(Hashable<Data>()(key));
    // Applicazione della tecnica di probing quadrato per calcolare la nuova chiave hash.
    return (starting_index + (((probe * probe) + probe) / 2) + array_size) % array_size; 

}

/* ************************************************************************** */

// Funzione che cerca un elemento nell'hash table.
template <typename Data>
bool HashTableOpnAdr<Data>::Find(unsigned long int& index, unsigned long int& probe, const Data& key) const noexcept {
    // Variabili per il conteggio degli spostamenti e l'indice di scambio.
    unsigned long int jumps = 0;
    unsigned long int index_for_swap = 0;

    // Flag per indicare se è stato trovato il primo elemento disponibile.
    bool first_available = true;

    // Calcola l'indice hash iniziale.
    unsigned long int temp_index = HashKey(probe, key);

    // Ciclo finché non viene trovato l'elemento o non viene esaurito l'array.
    do {
        // Se il numero di spostamenti è uguale alla dimensione dell'array meno 1, l'elemento non è presente.
        if (jumps == (array_size - 1))
            return false;

        // Se l'elemento è presente e non è stato eliminato...
        if ((Elements[temp_index] == key) && (flagsArray[temp_index].all())) {
            // Memorizza l'indice e, se non è il primo elemento disponibile, esegue lo swap.
            index = temp_index;
            if (!first_available) {
                Elements[index_for_swap] = Elements[index];
                std::swap(flagsArray[index_for_swap], flagsArray[temp_index]);
                index = index_for_swap;
            } else {
                index = temp_index;
            }
            return true;
        }

        // Se l'elemento non è presente e c'è spazio disponibile, memorizza l'indice per lo swap.
        if (flagsArray[temp_index][1] == 0 && first_available) {
            index_for_swap = temp_index;
            first_available = false;
        }

        // Calcola il prossimo indice utilizzando il probing e incrementa il contatore degli spostamenti.
        temp_index = HashKey(++probe, key);
        jumps++;
    } while (!flagsArray[temp_index].none()); // Continua finché non viene trovato un elemento vuoto.

    return false; // Se l'elemento non è stato trovato, restituisce false.

}

/* ************************************************************************** */

// Funzione che trova un'area vuota nell'hash table.
template <typename Data>
unsigned long int HashTableOpnAdr<Data>::FindEmpty(unsigned long int& probe, const Data& key) noexcept {
    // Calcola l'indice hash iniziale.
    unsigned long int temp_index = HashKey(probe, key);

    // Continua finché non trova un'area vuota o un'area contenente l'elemento specificato.
    while (flagsArray[temp_index].all() && Elements[temp_index] != key) {
        // Incrementa il parametro di probing e calcola il nuovo indice.
        ++probe;
        temp_index = HashKey(probe, key);
    }

    return temp_index; // Restituisce l'indice dell'area vuota o contenente l'elemento specificato.

}

/* ************************************************************************** */

// Funzione che rimuove un elemento dall'hash table.
template <typename Data>
bool HashTableOpnAdr<Data>::Remove(unsigned long int& probe, const Data& key) {
    // Variabile per memorizzare l'indice dell'elemento da rimuovere.
    unsigned long int temp_index = 0;

    // Se l'elemento è presente...
    if (Find(temp_index, probe, key)) {
        // Imposta il flag di eliminazione, aggiorna le dimensioni e il conteggio degli elementi eliminati.
        flagsArray[temp_index][1] = 0;
        size--;
        deleted_elements++;
        probe = 0;

        // Se la dimensione è inferiore a un quinto della dimensione dell'array e l'array è più grande di 32, ridimensiona.
        if (size < array_size / 5 && array_size > 32)
            Resize(array_size / 2);

        // Se il numero di elementi eliminati è maggiore di un quarto della dimensione dell'array, ridimensiona per eliminarli.
        if (deleted_elements > (array_size / 4))
            Resize(array_size);
        
        return true; // Restituisce true per indicare che l'elemento è stato rimosso.
    }
    // Se l'elemento non è presente, reimposta il parametro di probing e restituisce false.
    probe = 0;
    return false;
}

/* ************************************************************************** */


}