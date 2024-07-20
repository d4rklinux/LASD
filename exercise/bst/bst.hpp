#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public ClearableContainer,  // Must extend ClearableContainer, DictionaryContainer<Data>, BinaryTree<Data>, BinaryTreeLnk<Data>
virtual public DictionaryContainer<Data>, 
virtual public BinaryTree<Data>,  
virtual public BinaryTreeLnk<Data>  { 
  
private:

protected:

  using Container::size;
  using BinaryTreeLnk<Data>::root; // using BinaryTreeLnk<Data>::???;
  using typename BinaryTreeLnk<Data>::NodeLnk;

public:

  using MutableBinaryTree<Data>::Map;
  using MutableBinaryTree<Data>::PreOrderMap;
  using MutableBinaryTree<Data>::PostOrderMap;
  using MutableBinaryTree<Data>::InOrderMap;
  using MutableBinaryTree<Data>::BreadthMap;
  using BinaryTree<Data>::Root;

  // Default constructor
  // BST() specifiers;
  BST() = default;  
  /* ************************************************************************ */

  // Specific constructors

  // BST(argument) specifiers; // A bst obtained from a TraversableContainer
  // BST(argument) specifiers; // A bst obtained from a MappableContainer
  BST(const TraversableContainer<Data>& inputData);  
  BST(MappableContainer<Data>&& inputData) noexcept; 

  /* ************************************************************************ */

  // Copy constructor
  // BST(argument) specifiers;
  BST(const BST& inputData);  

  // Move constructor
  // BST(argument) specifiers;
  BST(BST&& inputData) noexcept;  

  /* ************************************************************************ */

  // Destructor
  ~BST() = default; // ~BST() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BST& operator=(const BST& inputData); 

  // Move assignment
  // type operator=(argument) specifiers;
  BST& operator=(BST&& inputData) noexcept; 

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  bool operator==(const BST& inputData) const noexcept; 
  inline bool operator!=(const BST& inputData) const noexcept { return (!(operator==(inputData))); };   

  /* ************************************************************************ */

  // Specific member functions

  // type Min(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type MinNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type RemoveMin(argument) specifiers; // (concrete function must throw std::length_error when empty)
  const Data& Min() const; 
  Data MinNRemove();  
  void RemoveMin(); 

  // type Max(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type MaxNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type RemoveMax(argument) specifiers; // (concrete function must throw std::length_error when empty)
  const Data& Max() const;  
  Data MaxNRemove(); 
  void RemoveMax(); 

  // type Predecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  // type PredecessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
  // type RemovePredecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  const Data& Predecessor(const Data& element) const; 
  Data PredecessorNRemove(const Data& element);   
  void RemovePredecessor(const Data& element);  

  // type Successor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  // type SuccessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
  // type RemoveSuccessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  const Data& Successor(const Data& element) const; 
  Data SuccessorNRemove(const Data& element);   
  void RemoveSuccessor(const Data& element);  

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)
  using BinaryTreeLnk<Data>::Root;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  // type Insert(argument) specifiers; // Override DictionaryContainer member (Copy of the value)
  // type Insert(argument) specifiers; // Override DictionaryContainer member (Move of the value)
  // type Remove(argument) specifiers; // Override DictionaryContainer member
  bool Insert(const Data& element) override;  
  bool Insert(Data&& element) override;   
  bool Remove(const Data& element) override;  

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  // type Exists(argument) specifiers; // Override TestableContainer member
  bool Exists(const Data& element) const noexcept override;   

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear(argument) specifiers; // Override ClearableContainer member
  inline virtual void Clear() noexcept override { BinaryTreeLnk<Data>::Clear(); };  

  protected:

  // Auxiliary functions, if necessary!
  
  // type DataNDelete(argument) specifiers;
  Data DataNDelete(NodeLnk* node); 
  // type Detach(argument) specifiers;
  NodeLnk* Detach(NodeLnk*& node) noexcept; 
  
  // type DetachMin(argument) specifiers;
  // type DetachMax(argument) specifiers;
  NodeLnk* DetachMin(NodeLnk *&) noexcept; 
  NodeLnk* DetachMax(NodeLnk *&) noexcept; 
  
  // type Skip2Left(argument) specifiers;
  // type Skip2Right(argument) specifiers;
  NodeLnk* Skip2Left(NodeLnk *&) noexcept;  
  NodeLnk* Skip2Right(NodeLnk *&) noexcept; 

  // type FindPointerToMin(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk* const &FindPointerToMin(NodeLnk *const &node) const noexcept; 
  NodeLnk*& FindPointerToMin(NodeLnk *&node) noexcept;
  
  // type FindPointerToMax(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk* const &FindPointerToMax(NodeLnk *const &node) const noexcept;
  NodeLnk*& FindPointerToMax(NodeLnk *&node) noexcept;
  
  // type FindPointerTo(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk* const& FindPointerTo(NodeLnk *const &node, Data element) const noexcept;
  NodeLnk*& FindPointerTo(NodeLnk *&node, Data element) noexcept;   

  // type FindPointerToPredecessor(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk* const& FindPointerToPredecessor(NodeLnk *const &node, Data element) const noexcept;
  NodeLnk*& FindPointerToPredecessor(NodeLnk *&node, Data element) noexcept; 

  // type FindPointerToSuccessor(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk* const& FindPointerToSuccessor(NodeLnk *const &node, Data element) const noexcept;
  NodeLnk*& FindPointerToSuccessor(NodeLnk *&node, Data element) noexcept; 

};

  /* ************************************************************************ */

}

#include "bst.cpp"

#endif
