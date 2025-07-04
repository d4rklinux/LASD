#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../container/container.hpp"
#include "../../container/traversable.hpp"
#include "../../container/mappable.hpp"
#include "../../container/linear.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data> ,   // Must extend MutableBinaryTree<Data>
virtual protected Vector<Data> {

private:

protected:

  struct NodeVec : virtual MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode

  friend class BinaryTreeVec<Data>;

  private:

    BinaryTreeVec<Data>* BT = nullptr;
    unsigned long int index;

  protected:

  public:

  /* ************************************************************************ */

    // Specific constructor
    NodeVec(const Data &data, unsigned long int index, BinaryTreeVec<Data>* BT);
    NodeVec(Data&& data, unsigned long int index, BinaryTreeVec<Data>* BT) noexcept;

  /* ************************************************************************ */

    // Destructor
    inline virtual ~NodeVec() = default;

  /* ************************************************************************ */

    // Copy assignment
    inline NodeVec& operator=(const NodeVec& nodeVec) {
    // Verifica se l'oggetto stesso non è uguale all'oggetto che si sta cercando di assegnare
      if (this != &nodeVec) {
      // Copia il dato dall'oggetto 'noteVec' all'oggetto corrente, utilizzando gli indici e i puntatori appropriati
      BT->data[index] = nodeVec.BT->data[nodeVec.index];
      // Copia l'indice dall'oggetto 'noteVec' all'oggetto corrente
      index = nodeVec.index;
      // Copia il puntatore al 'BinaryTreeVec' dall'oggetto 'noteVec' all'oggetto corrente
      BT = nodeVec.BT;
      }
      return *this;;// Restituisce un riferimento a se stesso
    }

    // Move assignment
    inline NodeVec& operator=(NodeVec&& nodeVec) noexcept {
    // Scambia i dati tra l'oggetto corrente e l'oggetto temporaneo 'noteVec'
    std::swap(BT->data[index], nodeVec.data[index]);
    // Scambia gli indici tra l'oggetto corrente e l'oggetto temporaneo 'noteVec'
    std::swap(index, nodeVec.index);
    // Scambia i puntatori 'BT' tra l'oggetto corrente e l'oggetto temporaneo 'noteVec'
    std::swap(BT, nodeVec.BT);
      return *this; // Restituisce un riferimento a se stesso
   }

  /* ************************************************************************ */

    // Specific member functions
    inline virtual Data& Element() noexcept override { return BT->elements[index]; }
    inline virtual const Data& Element() const noexcept override { return BT->elements[index]; }

    virtual bool HasLeftChild() const noexcept override;
    virtual bool HasRightChild() const noexcept override;

    virtual NodeVec& LeftChild() override;
    virtual const NodeVec& LeftChild() const override;

    virtual NodeVec& RightChild() override;
    virtual const NodeVec& RightChild() const override;

  };

  using Container::size;
  using Vector<Data>::elements;
  Vector<NodeVec*> NodeArray = Vector<NodeVec*>(0);

public:

  // Default constructor
  BinaryTreeVec() = default;   // BinaryTreeVec() specifiers;

  /* ************************************************************************ */

  // Specific constructors

  // BinaryTreeVec(argument) specifiers; // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(const TraversableContainer<Data>& anotherTraversableContainer);  

  // BinaryTreeVec(argument) specifiers; // A binary tree obtained from a MappableContainer
  BinaryTreeVec(MappableContainer<Data>&& anotherMappableContainer) noexcept;   

  /* ************************************************************************ */

  // Copy constructor
  // BinaryTreeVec(argument) specifiers;
  BinaryTreeVec(const BinaryTreeVec<Data>& anotherBinaryTree);  
  
  // Move constructor
  // BinaryTreeVec(argument) specifiers;
  BinaryTreeVec(BinaryTreeVec<Data>&& anotherrBinaryTree) noexcept;  

  /* ************************************************************************ */

  // Destructor
  // ~BinaryTreeVec() specifiers;
  virtual ~BinaryTreeVec();  

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BinaryTreeVec& operator=(const BinaryTreeVec& anotherBinaryTree); 

  // Move assignment
  // type operator=(argument) specifiers;

  BinaryTreeVec& operator=(BinaryTreeVec&& anotherBinaryTree) noexcept; 
  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  inline bool operator==(const BinaryTreeVec& anotherBinaryTree) const noexcept { return Vector<Data>::operator==(anotherBinaryTree); };  
  inline bool operator!=(const BinaryTreeVec& anotherBinaryTree) const noexcept { return !(operator==(anotherBinaryTree)); };   

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  // type Root() specifiers; // Override BinaryTree member (throw std::length_error when empty)
  virtual const NodeVec& Root() const override; 

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  // type Root() specifiers; // Override MutableBinaryTree member (throw std::length_error when empty)
  virtual NodeVec& Root() override;   

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  
  // type Clear() specifiers; // Override ClearableContainer member 
  virtual void Clear() override;   

  /* ************************************************************************ */

  using typename MappableContainer<Data>::MapFun;
  using typename TraversableContainer<Data>::TraverseFun;

  // Specific member function (inherited from BreadthTraversableContainer)
  
  // type BreadthTraverse(arguments) specifiers; // Override BreadthTraversableContainer member
  inline void BreadthTraverse(const TraverseFun function) const override { BinaryTree<Data>::BreadthTraverse(function); };  
  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  
  // type BreadthMap(arguments) specifiers; // Override BreadthMappableContainer member
  inline void BreadthMap(const MapFun function) override { MutableBinaryTree<Data>::BreadthMap(function); }; 

  //Override per la scelta delle Fold e delle Map 
  inline void Traverse(const TraverseFun function) const override { BinaryTree<Data>::Traverse(function); };

  inline void PreOrderTraverse(TraverseFun function) const override { BinaryTree<Data>::PreOrderTraverse(function); };
  inline void PostOrderTraverse(TraverseFun function) const override { BinaryTree<Data>::PostOrderTraverse(function); };
  inline void InOrderTraverse(TraverseFun function) const override { BinaryTree<Data>::InOrderTraverse(function); };

  inline void PreOrderMap(MapFun function) override { MutableBinaryTree<Data>::PreOrderMap(function); };
  inline void PostOrderMap(MapFun function) override { MutableBinaryTree<Data>::PostOrderMap(function); };
  inline void Map(MapFun function) override { MutableBinaryTree<Data>::Map(function); };

protected:


};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
