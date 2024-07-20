/* ************************************************************************** */

#include "hashtable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

// Specializzazione della classe template Hashable per il tipo int
template <>
class Hashable<int> {
public:
    // Operatore call che calcola un hash per un valore int
    unsigned long int operator()(const int value) const noexcept {
        // Calcola l'hash del valore incrementato di uno, moltiplicato per il valore stesso
        unsigned long int hash_value = (value + 1) * value;
        
        return hash_value;  // Restituisce l'hash calcolato
    }
};

/* ************************************************************************** */

// Specializzazione della classe template Hashable per il tipo double
template <>
class Hashable<double> {
public:
    // Operatore call che calcola un hash per un valore double
    unsigned long int operator()(const double value) const noexcept {
        // Estrai la parte intera del valore double
        unsigned long int int_part = std::floor(value);
        // Calcola il quadrato della parte intera
        unsigned long int int_square = int_part * int_part;
        // Calcola la differenza tra il valore originale e la parte intera (parte frazionaria)
        double frac_part = value - int_part;
        // Calcola il quadrato della parte frazionaria
        double frac_square = frac_part * frac_part;
        // Calcola l'hash combinando le due parti, sottraendo la parte intera
        unsigned long int hash_value = int_square + frac_square - int_part;
        
        return hash_value; // Restituisce l'hash calcolato

    }
};

/* ************************************************************************** */

// Specializzazione della classe template Hashable per il tipo std::string
template <>
class Hashable<std::string> {
public:
    // Operatore call che calcola un hash per un valore std::string
    unsigned long int operator()(const std::string& value) const noexcept {
        unsigned long int hashValue = 0;

        // Itera attraverso ogni carattere nella stringa
        for (unsigned long int i = 0; i < value.size(); ++i) {
            // Aggiunge il prodotto dell'indice del carattere e il valore del carattere al valore hash
            hashValue += (i * value[i]);
        }

        return hashValue; // Restituisce l'hash calcolato
    }
};

/* ************************************************************************** */

// Costruttore di copia della classe HashTable
template <typename Data>
HashTable<Data>::HashTable(const HashTable<Data>& other) {
    // Copia dei membri dalla tabella hash originale 'other'
    size = other.size;                      // Copia il numero di elementi attualmente presenti nella tabella hash
    array_size = other.array_size;          // Copia la dimensione dell'array che contiene le liste di dati
    hashMultiplier = other.hashMultiplier;  // Copia il moltiplicatore utilizzato nella funzione hash
    hashOffset = other.hashOffset;          // Copia l'offset utilizzato nella funzione hash
}

/* ************************************************************************** */

// Costruttore di spostamento della classe HashTable
template <typename Data>
HashTable<Data>::HashTable(HashTable<Data>&& other) noexcept {
    // Scambia i membri con la tabella hash originale 'other' utilizzando std::swap
    std::swap(size, other.size);                      // Scambia il numero di elementi presenti nella tabella hash
    std::swap(array_size, other.array_size);          // Scambia la dimensione dell'array che contiene le liste di dati
    std::swap(hashMultiplier, other.hashMultiplier);  // Scambia il moltiplicatore utilizzato nella funzione hash
    std::swap(hashOffset, other.hashOffset);          // Scambia l'offset utilizzato nella funzione hash
}

/* ************************************************************************** */

// Operatore di assegnazione della classe HashTable
template <typename Data>
HashTable<Data>& HashTable<Data>::operator=(const HashTable<Data>& other) {
    // Copia i membri dalla tabella hash originale 'other'
    size = other.size;                      // Copia il numero di elementi presenti nella tabella hash
    array_size = other.array_size;          // Copia la dimensione dell'array che contiene le liste di dati
    hashMultiplier = other.hashMultiplier;  // Copia il moltiplicatore utilizzato nella funzione hash
    hashOffset = other.hashOffset;          // Copia l'offset utilizzato nella funzione hash

    return *this; // Restituisce un riferimento a questa istanza della classe

}

/* ************************************************************************** */

// Operatore di assegnazione tramite spostamento della classe HashTable
template <typename Data>
HashTable<Data>& HashTable<Data>::operator=(HashTable<Data>&& other) noexcept {
    // Scambia i membri con la tabella hash originale 'other' utilizzando std::swap
    std::swap(size, other.size);                      // Scambia il numero di elementi presenti nella tabella hash
    std::swap(array_size, other.array_size);          // Scambia la dimensione dell'array che contiene le liste di dati
    std::swap(hashMultiplier, other.hashMultiplier);  // Scambia il moltiplicatore utilizzato nella funzione hash
    std::swap(hashOffset, other.hashOffset);          // Scambia l'offset utilizzato nella funzione hash

    return *this; // Restituisce un riferimento a questa istanza della classe
}

/* ************************************************************************** */

// Metodo di confronto operator== della classe HashTable
template <typename Data>
bool HashTable<Data>::operator==(const HashTable<Data>& other) const noexcept {
    // Se le dimensioni delle due tabelle hash sono diverse, restituisce false
    if (size != other.size)
        return false;
    // Variabile per tenere traccia dell'uguaglianza tra le due tabelle hash
    bool areEqual = true;
    // Funzione per confrontare gli elementi delle due tabelle hash
    // Utilizzando la funzione Exists() dell'altro oggetto HashTable
    this->Map(
        [&areEqual, &other](const Data& element) {
            // Utilizza il metodo Exists() dell'altro oggetto HashTable per verificare l'esistenza di ogni elemento
            // e aggiorna la variabile areEqual di conseguenza
            areEqual &= other.Exists(element);
        }
    );

    return areEqual; // Restituisce true se tutte le coppie di elementi sono uguali, altrimenti false
}

/* ************************************************************************** */

// Metodo per trovare la prossima potenza di due superiore o uguale a un dato numero
template <typename Data>
unsigned long int HashTable<Data>::NextPowOf2(unsigned long int size) {
    // Se la dimensione è minore di 32, restituisce 32 come potenza di due successiva
    if (size < 32)
        return 32;
        
    // Utilizza la funzione std::pow per calcolare 2 elevato alla potenza ceil(log2(size))
    return static_cast <unsigned long int>(std::pow(2, std::ceil(std::log2(size)))); //Restituisce la potenza di due più piccola o uguale a size
}

/* ************************************************************************** */

}
