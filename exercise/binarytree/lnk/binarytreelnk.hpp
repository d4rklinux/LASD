
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public MutableBinaryTree<Data> {    // Must extend MutableBinaryTree<Data>

private:

protected:

using Container::size;

// using BinaryTree<Data>::???;
using typename BinaryTree<Data>::Node;

struct NodeLnk : virtual public MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode

friend class BinaryTreeLnk<Data>;

private:

protected:

public:

Data elem {};
NodeLnk* l_child = nullptr;
NodeLnk* r_child = nullptr;

// Specific constructors
NodeLnk(const Data& newData) : elem(newData) {};
NodeLnk(Data&& newData) noexcept { std::swap(elem , newData); };

// Copy constructor
NodeLnk(const NodeLnk& nodeLnk);

// Move constructor
NodeLnk(NodeLnk&& nodeLnk) noexcept;

// Destructor
inline virtual ~NodeLnk() { delete l_child; delete r_child; };

// Copy Assignament
NodeLnk& operator=(const NodeLnk& nodeLnk);

// Move Assignament
NodeLnk& operator=(NodeLnk&& nodeLnk) noexcept;
    

// Specific member functions
inline virtual Data& Element() noexcept override { return elem; }
inline virtual const Data& Element() const noexcept override { return elem; }

inline virtual bool IsLeaf() const noexcept override { return (!(HasLeftChild() || HasRightChild())); }; 
    
inline virtual bool HasLeftChild() const noexcept override { return l_child!=nullptr; }
inline virtual bool HasRightChild() const noexcept override { return r_child!=nullptr; }

virtual NodeLnk& RightChild() override; // Must throw std::length_error when empty
virtual const NodeLnk& RightChild() const override; // Must throw std::length_error when empty
virtual NodeLnk& LeftChild() override; // Must throw std::length_error when empty
virtual const NodeLnk& LeftChild() const override; // Must throw std::length_error when empty

  };

NodeLnk * root = nullptr;

public:

// Default constructor
 BinaryTreeLnk() = default;  // BinaryTreeLnk() specifiers;

/* ************************************************************************** */

// Specific constructors

// BinaryTreeLnk(argument) specifiers; // A binary tree obtained from a TraversableContainer
// BinaryTreeLnk(argument) specifiers; // A binary tree obtained from a MappableContainer
BinaryTreeLnk(const TraversableContainer<Data>& anotherBinaryTreeLnk);  
BinaryTreeLnk(MappableContainer<Data>&& anotherBinaryTreeLnk) noexcept; 

/* ************************************************************************** */

// Copy constructor
// BinaryTreeLnk(argument) specifiers;
BinaryTreeLnk(const BinaryTreeLnk<Data>& anotherBinaryTreeLnk);  

// Move constructor
// BinaryTreeLnk(argument) specifiers;
BinaryTreeLnk(BinaryTreeLnk<Data>&& anotherBinaryTreeLnk) noexcept;  

/* ************************************************************************** */

// Destructor
// ~BinaryTreeLnk() specifiers;
virtual ~BinaryTreeLnk() { delete root; };  

/* ************************************************************************** */

// Copy assignment
// type operator=(argument) specifiers;
BinaryTreeLnk& operator=(const BinaryTreeLnk& anotherBinaryTreeLnk); 

// Move assignment
// type operator=(argument) specifiers;
BinaryTreeLnk& operator=(BinaryTreeLnk&& anotherBinaryTreeLnk) noexcept; 

/* ************************************************************************** */

// Comparison operators

// type operator==(argument) specifiers;
// type operator!=(argument) specifiers;
inline bool operator==(const BinaryTreeLnk& anotherBinaryTreeLnk) const noexcept { return BinaryTree<Data>::operator==(anotherBinaryTreeLnk); };  
inline bool operator!=(const BinaryTreeLnk& anotherBinaryTreeLnk) const noexcept { return !(operator==(anotherBinaryTreeLnk)); }; 

/* ************************************************************************** */

// Specific member functions (inherited from BinaryTree)

// type Root() specifiers; // Override BinaryTree member (throw std::length_error when empty)
inline virtual const NodeLnk& Root() const override;  

/* ************************************************************************** */

// Specific member function (inherited from MutableBinaryTree)

// type Root() specifiers; // Override MutableBinaryTree member (throw std::length_error when empty)
inline virtual NodeLnk& Root() override; 

/* ************************************************************************** */

// Specific member function (inherited from ClearableContainer)

// type Clear() specifiers; // Override ClearableContainer member
virtual void Clear() noexcept override; 

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif