#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public ClearableContainer, virtual public LinearContainer<Data>, virtual public DictionaryContainer<Data> {

private:
  // ...

protected:
  using Container::size;

  struct Node {

    Data val;

    Node *next{nullptr};

    Node() = default;

    /* ********************************************************************** */

    // Specific constructors

    explicit Node(const Data &value) : val(value) {}
    explicit Node(Data &&value) { std::swap(val, value); }

    /* ********************************************************************** */

    // Copy constructor
    Node(const Node &other) : val(other.val) {}
    
    // Move constructor
    Node(Node &&other) noexcept {
      std::swap(other.val, val);
      std::swap(other.next, next);
    }

    /* ********************************************************************** */

    // Destructor
    // Destructor
    virtual ~Node() { delete next; }

    /* ********************************************************************** */

    // Comparison operators
    inline bool operator==(const Node &other) const noexcept {
      return val == other.val;
    }
    inline bool operator!=(const Node &other) const noexcept {
      return !((*this) == other);
    }

    /* ********************************************************************** */

    // Specific member functions

    // ...
  };

  Node *head{nullptr};
  Node *tail{nullptr};

public:
  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  // List(argument) specifiers; // A list obtained from a TraversableContainer
  // List(argument) specifiers; // A list obtained from a MappableContainer
  List(const TraversableContainer<Data> &);
  List(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  List(const List &);
  // Move constructor
  List(List &&);

  /* ************************************************************************ */

  // Destructor
  virtual ~List() { delete head; };

  /* ************************************************************************ */

  // Copy assignment
  inline List &operator=(const List &);
  // Move assignment
  inline List &operator=(List &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  inline bool operator==(const List &) const noexcept;
  inline bool operator!=(const List &other) const noexcept {
    return !(*this == other);
  };

  /* ************************************************************************ */

  // Specific member functions
  void InsertAtFront(const Data &); // Copy of the value
  void InsertAtFront(Data &&); // Move of the value
  void RemoveFromFront(); // (must throw std::length_error)
  Data FrontNRemove(); // (must throw std::length_error)
  void InsertAtBack(const Data &); // Copy of the value
  void InsertAtBack(Data &&); // Move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  inline void Clear() override {
    size = 0;
    delete head;
    head = tail = nullptr;
  } // Override ClearableContainer member

  using TestableContainer<Data>::Exists;
  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  inline bool Insert(const Data &dataToInsert) override; // Copy of the value
  inline bool Insert(Data &&dataToInsert) override;      // Move of the value
  // type Remove(argument) specifier;
  bool Remove(const Data &) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)
  // type operator[](argument) specifiers; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  // type operator[](argument) specifiers; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)
  inline const Data &operator[](unsigned long) const override;
  inline Data &operator[](unsigned long) override;

  // type Front() specifiers; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  // type Front() specifiers; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)
  inline const Data &Front() const override;
  inline Data &Front() override;

  // type Back() specifiers; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  // type Back() specifiers; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)
  inline const Data &Back() const override;
  inline Data &Back() override;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  // using typename TraversableContainer<Data>::TraverseFun;
  using typename TraversableContainer<Data>::TraverseFun;
  
  // type Traverse(arguments) specifiers; // Override TraversableContainer member
  inline void Traverse(TraverseFun function) const override {
    PreOrderTraverse(function);
  }

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  // type PreOrderTraverse(arguments) specifiers; // Override PreOrderTraversableContainer member
  inline void PreOrderTraverse(TraverseFun function) const override {
    PreOrderTraverse(function, head);
  }

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)
  inline void PostOrderTraverse(TraverseFun function) const override {
    PostOrderTraverse(function, head);
  }

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFun;

  // Override MappableContainer member
  inline void Map(MapFun function) override {
    PreOrderMap(function);
  } 

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)
  inline void PreOrderMap(MapFun function) override { PreOrderMap(function, head); }

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)
  inline void PostOrderMap(MapFun function) override { PostOrderMap(function, head); }

protected:

  void PreOrderTraverse(TraverseFun, Node *) const;
  void PostOrderTraverse(TraverseFun, Node *) const;
  void PreOrderMap(MapFun, Node *) const;
  void PostOrderMap(MapFun, Node *) const;
};

/* ************************************************************************** */

} 

#include "list.cpp"

#endif
