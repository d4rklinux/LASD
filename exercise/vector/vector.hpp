
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

  template <typename Data>
  class Vector : virtual public ResizableContainer, virtual public LinearContainer<Data>
  {

  private:
    // ...

  protected:
    using Container::size;

    Data *elements = nullptr;

  public:
    // Default constructor
    Vector() = default;

/* ************************************************************************** */

    // Specific constructors
    explicit Vector(const unsigned long initSize)
    {
      size = initSize;
      elements = new Data[initSize]();
    }; // A vector with a given initial dimension
    inline Vector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
    inline Vector(MappableContainer<Data> &&);         // A vector obtained from a MappableContainer

/* ************************************************************************** */

    // Copy constructor
    inline explicit Vector(const Vector<Data> &);
    // Move constructor
    inline explicit Vector(Vector<Data> &&) noexcept;

/* ************************************************************************** */

    // Destructor
    virtual ~Vector() { delete[] elements; };

/* ************************************************************************** */

    // Copy assignment
    inline Vector<Data> &operator=(const Vector<Data> &);
    // Move assignment
    inline Vector<Data> &operator=(Vector<Data> &&) noexcept;

/* ************************************************************************** */

    // Comparison operators
    bool operator==(const Vector<Data> &) const noexcept;
    inline bool operator!=(const Vector<Data> &) const noexcept;

/* ************************************************************************** */

    // Specific member function (inherited from ClearableContainer)
    inline void Clear() override; // Override ClearableContainer member

/* ************************************************************************** */

    // Specific member function (inherited from ResizableContainer)
    void Resize(unsigned long) override; // Override ResizableContainer member

/* ************************************************************************** */

    // Specific member functions (inherited from LinearContainer)

    // Override (NonMutable) LinearContainer member 
    inline const Data &operator[](unsigned long) const override;
    // Override (Mutable) LinearContainer member  
    inline Data &operator[](unsigned long) override;             

    // Override (NonMutable) LinearContainer member 
    inline const Data &Front() const override; 
    // Override (Mutable) LinearContainer member
    inline Data &Front() override;              

    // Override (NonMutable) LinearContainer member 
    inline const Data &Back() const override; 
    // Override (Mutable) LinearContainer member 
    inline Data &Back() override;             

  protected:
    // Auxiliary functions, if necessary!
  };

/* ************************************************************************** */

  template <typename Data>
  class SortableVector final : virtual public Vector<Data>, virtual public SortableLinearContainer<Data>
  {

  private:
    // ...

  protected:
    using Container::size;

  public:
    // Default constructor

    // SortableVector() specifiers;
    SortableVector() = default;

/* ************************************************************************** */

    // Specific constructors
   
    // SortableVector(argument) specifiers; // A vector with a given initial dimension
    // SortableVector(argument) specifiers; // A vector obtained from a TraversableContainer
    // SortableVector(argument) specifiers; // A vector obtained from a MappableContainer
    inline SortableVector(unsigned long s) : Vector<Data>::Vector(s){};
    inline SortableVector(const TraversableContainer<Data> &con) : Vector<Data>::Vector(con){};
    inline SortableVector(MappableContainer<Data> &&con) : Vector<Data>::Vector(std::move(con)){};
/* ************************************************************************** */

    // Copy constructor
    inline explicit SortableVector(const SortableVector<Data> &con) : Vector<Data>::Vector(con){};
   
    // Move constructor
    inline explicit SortableVector(SortableVector<Data> &&con) noexcept : Vector<Data>::Vector(std::move(con)){};

/* ************************************************************************** */

    // Destructor
    // ~SortableVector() specifiers;
    virtual ~SortableVector() = default;

/* ************************************************************************** */

    // Copy assignment
    inline SortableVector<Data> &operator=(const SortableVector<Data> &con);
    
    // Move assignment
    inline SortableVector<Data> &operator=(SortableVector<Data> &&con) noexcept;

    // Copy assignment
    // type operator=(argument) specifiers;

    // Move assignment
    // type operator=(argument) specifiers;

    // using Vector<Data>::operator[];

  protected:
    // Auxiliary functions, if necessary!
  };

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
