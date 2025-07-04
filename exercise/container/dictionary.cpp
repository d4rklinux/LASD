#include "dictionary.hpp" 

namespace lasd {

/* ************************************************************************** */

// Funzione per inserire tutti gli elementi da un TraversableContainer nel dizionario
template<typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &container) {
    bool result = true; // Inizializza il risultato come vero
    container.Traverse([this,&result](const Data & dat){ // Attraversa il contenitore e applica una funzione lambda a ogni elemento
        result &= Insert(dat); // Inserisci l'elemento nel dizionario e aggiorna il risultato
    
    }
    );
    return result; // Restituisci il risultato finale
}

/* ************************************************************************** */

// Funzione per inserire tutti gli elementi da un MappableContainer nel dizionario
template<typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> &&container){ 
    bool result = true; // Inizializza il risultato come vero
    container.Map([this,&result](Data& dat){ // Mappa il contenitore e applica una funzione lambda a ogni elemento
        result &= Insert(std::move(dat)); // Inserisci l'elemento nel dizionario e aggiorna il risultato
    
    }
    );
    return result; // Restituisci il risultato finale
}

/* ************************************************************************** */

// Funzione per rimuovere tutti gli elementi dal dizionario che sono presenti nel TraversableContainer
template<typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> &container) {
    bool result = true; // Inizializza il risultato come vero
    container.Traverse([this,&result](const Data & dat){ // Attraversa il contenitore e applica una funzione lambda a ogni elemento
        result &= Remove(dat); // Rimuovi l'elemento dal dizionario e aggiorna il risultato
    
    }
    );
    return result; // Restituisci il risultato finale
}

/* ************************************************************************** */

// Funzione per inserire alcuni elementi da un TraversableContainer nel dizionario
template<typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &container) {
    bool some = false; // Inizializza un flag che indica se almeno un elemento è stato inserito
    container.Traverse([this,&some](const Data & dat){ // Attraversa il contenitore e applica una funzione lambda a ogni elemento
        some &= Insert(dat); // Inserisci l'elemento nel dizionario e aggiorna il flag
    
    }
    );
    return some; // Restituisci se almeno un elemento è stato inserito
}

/* ************************************************************************** */

// Funzione per inserire alcuni elementi da un MappableContainer nel dizionario
template<typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> && container){ 
    bool some = false; // Inizializza un flag che indica se almeno un elemento è stato inserito
    container.Map([this,&some]( Data& dat){ // Mappa il contenitore e applica una funzione lambda a ogni elemento
        some &= Insert(std::move(dat)); // Inserisci l'elemento nel dizionario e aggiorna il flag
    
    }
    );
    return some; // Restituisci se almeno un elemento è stato inserito
}

/* ************************************************************************** */

// Funzione per rimuovere alcuni elementi dal dizionario che sono presenti nel TraversableContainer
template<typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &container) {
    bool some = false; // Inizializza un flag che indica se almeno un elemento è stato rimosso
    container.Traverse([this,&some](const Data & dat){ // Attraversa il contenitore e applica una funzione lambda a ogni elemento
        some &= Remove(dat); // Rimuovi l'elemento dal dizionario e aggiorna il flag
    
    }
    );
    return some; // Restituisci se almeno un elemento è stato rimosso
}

/* ************************************************************************** */

}
