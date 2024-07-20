
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : virtual public PreOrderTraversableContainer<Data>,   // Must extend PreOrderTraversableContainer<Data>,
virtual public PostOrderTraversableContainer<Data>,                     // PostOrderTraversableContainer<Data>,
virtual public InOrderTraversableContainer<Data>,                       // InOrderTraversableContainer<Data>,
virtual public BreadthTraversableContainer<Data> {                      // BreadthTraversableContainer<Data>

private:

protected:

public:

  struct Node {

  protected:

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is possible, but is not visible.
    // type operator!=(argument) specifiers; // Comparison of abstract types is possible, but is not visible.
    inline bool operator==(const Node& Node) const noexcept { return (Element() == Node.Element()); }; 
    inline bool operator!=(const Node& Node) const noexcept { return !(operator==(Node)); }; 

  public:
    
    // friend class BinaryTree<Data>;
    friend class BinaryTree<Data>;  

    /* ********************************************************************** */

    // Destructor
    // ~Node() specifiers
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    Node& operator=(const Node& Node) = delete;  

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.
    Node& operator=(Node&& Node) noexcept = delete;  

    /* ********************************************************************** */

    // Specific member functions
    
    // type Element() specifiers; // Immutable access to the element (concrete function should not throw exceptions)
    virtual const Data& Element() const noexcept = 0; 

    // type IsLeaf() specifiers; // (concrete function should not throw exceptions)
    inline virtual bool IsLeaf() const noexcept { return ((!HasLeftChild()) && (!HasRightChild())); }; 

    // type HasLeftChild() specifiers; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; 

    // type HasRightChild() specifiers; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0; 

    // type LeftChild() specifiers; // (concrete function must throw std::out_of_range when not existent)
    // type RightChild() specifiers; // (concrete function must throw std::out_of_range when not existent)
    virtual const Node& LeftChild() const = 0;  
    virtual const Node& RightChild() const = 0; 

  };

  /* ************************************************************************ */

  // Destructor
  // ~BinaryTree() specifiers
  virtual ~BinaryTree() = default;  

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  BinaryTree& operator=(const BinaryTree& anotherBinaryTree) = delete;  
 
  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  BinaryTree& operator=(BinaryTree&& anotherBinaryTree) noexcept = delete; 

  /* ************************************************************************ */

  // Comparison operators

  // type operator==(argument) specifiers; // Comparison of abstract binary tree is possible.
  // type operator!=(argument) specifiers; // Comparison of abstract binary tree is possible.
  bool operator==(const BinaryTree& anotherBinaryTree) const noexcept;  
  inline bool operator!=(const BinaryTree& anotherBinaryTree) const noexcept{ return !(operator==(anotherBinaryTree)); };  

  /* ************************************************************************ */

  // Specific member functions

  // type Root() specifiers; // (concrete function must throw std::length_error when empty)
  virtual const Node& Root() const = 0; 

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  
  // using typename TraversableContainer<Data>::TraverseFun;
  using typename TraversableContainer<Data>::TraverseFun; 
  
  // type Traverse(arguments) specifiers; // Override TraversableContainer member
  virtual void Traverse(TraverseFun function) const override; 

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  
  // type PreOrderTraverse(arguments) specifiers; // Override PreOrderTraversableContainer member
  virtual void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)
  // type PostOrderTraverse(arguments) specifiers; // Override PostOrderTraversableContainer member
  virtual void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)
  // type InOrderTraverse(arguments) specifiers; // Override InOrderTraversableContainer member
  virtual void InOrderTraverse(TraverseFun) const override; 

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)
  // type BreadthTraverse(arguments) specifiers; // Override BreadthTraversableContainer member
  virtual void BreadthTraverse(TraverseFun) const override; 

  protected:

  /* ************************************************************************ */

  // Auxiliary functions, if necessary!

  // Auxiliary member function (for PreOrderMappableContainer)
  void AuxPreOrderTraversable(const Node *node, TraverseFun function) const; // Accessory function executing from one node of the tree

  // Auxiliary member function (for PostOrderMappableContainer)
  void AuxPostOrderTraversable(const Node *node, TraverseFun function) const; // Accessory function executing from one node of the tree

  // Auxiliary member function (for InOrderMappableContainer)
  void AuxInOrderTraversable(const Node *node, TraverseFun function) const; // Accessory function executing from one node of the tree

  // Auxiliary member function (for BreadthMappableContainer)
  void AuxBreadthTraversable(const Node *node, TraverseFun function) const; // Accessory function executing from one node of the tree

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : virtual public ClearableContainer,  // Must extend ClearableContainer,
virtual public BinaryTree<Data>,                              // BinaryTree<Data>,
virtual public PreOrderMappableContainer<Data>,               // PreOrderMappableContainer<Data>,
virtual public PostOrderMappableContainer<Data>,              // PostOrderMappableContainer<Data>,
virtual public InOrderMappableContainer<Data>,                // InOrderMappableContainer<Data>,
virtual public BreadthMappableContainer<Data> {               // BreadthMappableContainer<Data>

private:

protected:

public:

struct MutableNode : virtual public BinaryTree<Data>::Node {  // Must extend Node

// friend class MutableBinaryTree<Data>
friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    // ~MutableNode() specifiers
    virtual ~MutableNode() = default; 

    /* ********************************************************************** */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    MutableNode& operator=(const MutableNode&) = delete;  

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.
    MutableNode& operator=(MutableNode&&) noexcept = delete;  

    /* ********************************************************************** */

    // Specific member functions

    // type Element() specifiers; // Mutable access to the element (concrete function should not throw exceptions)
    using BinaryTree<Data>::Node::Element;
    virtual Data& Element() noexcept = 0; 

    // type LeftChild() specifiers; // (concrete function must throw std::out_of_range when not existent)
    using BinaryTree<Data>::Node::LeftChild;
    virtual  MutableNode& LeftChild() = 0 ;

    // type RightChild() specifiers; // (concrete function must throw std::out_of_range when not existent)
    using BinaryTree<Data>::Node::RightChild;
    virtual MutableNode& RightChild() = 0;


  };

  /* ************************************************************************ */

  // Destructor
  // ~MutableBinaryTree() specifiers
  virtual ~MutableBinaryTree() = default; 

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  MutableBinaryTree<Data>& operator=(const MutableBinaryTree& anotherBinaryTree) = delete;  

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  MutableBinaryTree<Data>& operator=(MutableBinaryTree&& anotherBinaryTree) = delete; 

  /* ************************************************************************ */

  // Specific member functions
  // type Root() specifiers; // (concrete function must throw std::length_error when empty)
  using BinaryTree<Data>::Root;
  virtual MutableNode& Root() = 0;  

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  // using typename MappableContainer<Data>::MapFun;
  using typename MappableContainer<Data>::MapFun; 
  
  // type Map(argument) specifiers; // Override MappableContainer member
  inline virtual void Map(MapFun function) override { PreOrderMap(function); };  

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  // type PreOrderMap(argument) specifiers; // Override PreOrderMappableContainer member
  virtual void PreOrderMap(MapFun function) override;  

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  // type PostOrderMap(argument) specifiers; // Override PostOrderMappableContainer member
  virtual void PostOrderMap(MapFun function) override; 

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)
  // type InOrderMap(arguments) specifiers; // Override InOrderMappableContainer member
  virtual void InOrderMap(MapFun function) override; 

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  // type BreadthMap(arguments) specifiers; // Override BreadthMappableContainer member
  virtual void BreadthMap(MapFun function) override; 

protected:

  // Auxiliary functions, if necessary!

  // Auxiliary member function (for MutablePreOrderMappableContainer)
  // Accessory function executing from one node of the tree
  void AuxPreOrderMap(MutableNode* node, MapFun function); 

  /* ************************************************************************ */

  // Auxiliary member function (for MutablePostOrderMappableContainer)
  // Accessory function executing from one node of the tree
  void AuxPostOrderMap(MutableNode* node, MapFun function); 

  /* ************************************************************************ */

  // Auxiliary member function (for MutableInOrderMappableContainer)
  // Accessory function executing from one node of the tree
  void AuxInOrderMap(MutableNode* node, MapFun function); 

  /* ************************************************************************ */

  // Auxiliary member function (for MutableBreadthMappableContainer)
  // Accessory function executing from one node of the tree
  void AuxBreadthMap(MutableNode* node, MapFun function); 

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>,  // Must extend ForwardIterator<Data>,
virtual public ResettableIterator<Data> {                         // ResettableIterator<Data>

private:

protected:

  const typename BinaryTree<Data>::Node* root = nullptr;
  const typename BinaryTree<Data>::Node* current = nullptr;
  StackLst<const typename BinaryTree<Data>::Node*> stack;

public:

  // Specific constructors
  // BTPreOrderIterator(argument) specifiers; // An iterator over a given binary tree
  BTPreOrderIterator(const BinaryTree<Data>& anotherBinaryTree);  

  /* ************************************************************************ */

  // Copy constructor
  // BTPreOrderIterator(argument) specifiers;
  BTPreOrderIterator(const BTPreOrderIterator& anotherIterator); 

  // Move constructor
  // BTPreOrderIterator(argument) specifiers;
  BTPreOrderIterator(BTPreOrderIterator&& anotherIterator) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~BTPreOrderIterator() specifiers;
  virtual ~BTPreOrderIterator() = default;  

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTPreOrderIterator& operator=(const BTPreOrderIterator& anotherIterator); 

  // Move assignment
  // type operator=(argument) specifiers;
  BTPreOrderIterator& operator=(BTPreOrderIterator&& anotherIterator) noexcept; 

  /* ************************************************************************ */

  // Comparison operators

  // type operator==(argument) specifiers;
  bool operator==(const BTPreOrderIterator& anotherIterator) const noexcept;  
  // type operator!=(argument) specifiers;
  inline bool operator!=(const BTPreOrderIterator& anotherIterator) const noexcept { return !(operator==(anotherIterator)); };  

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override; 
  
  // type Terminated() specifiers; // (should not throw exceptions)
  inline bool Terminated() const noexcept override { return (current == nullptr); }; 

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  
  // type operator++() specifiers; // (throw std::out_of_range when terminated)
  BTPreOrderIterator<Data>& operator++() override; 

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // type Reset() specifiers; // (should not throw exceptions)
  inline void Reset() noexcept override { stack.Clear(); current = root; }; 

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : virtual public MutableIterator<Data>,   // Must extend MutableIterator<Data>,
virtual public BTPreOrderIterator<Data> {                                 // BTPreOrderIterator<Data>

private:

protected:

public:

  // Specific constructors

  // BTPreOrderMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree
  inline BTPreOrderMutableIterator(MutableBinaryTree<Data>& anotherBinaryTree) : BTPreOrderIterator<Data>(anotherBinaryTree){;};
  /* ************************************************************************ */

  // Copy constructor
  // BTPreOrderMutableIterator(argument) specifiers;
  inline BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data>& anotherIterator) : BTPreOrderIterator<Data>(anotherIterator) {;};

  // Move constructor
  // BTPreOrderMutableIterator(argument) specifiers;
  inline BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data>&& anotherIterator) noexcept : BTPreOrderIterator<Data>(std::move(anotherIterator)) {;};

  /* ************************************************************************ */

  // Destructor
  // ~BTPreOrderMutableIterator() specifiers;
  virtual ~BTPreOrderMutableIterator() = default; 

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  inline BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator& anotherIterator); 

  // Move assignment
  // type operator=(argument) specifiers;
  inline BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator&& anotherIterator) noexcept;  

  /* ************************************************************************ */

  // Comparison operators
  
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  inline bool operator==(const BTPreOrderMutableIterator& anotherIterator) const noexcept { return BTPreOrderIterator<Data>::operator==(anotherIterator); };  
  inline bool operator!=(const BTPreOrderMutableIterator& anotherIterator) const noexcept { return !(operator==(anotherIterator)); };  

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override; 

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>,   // Must extend ForwardIterator<Data>,
virtual public ResettableIterator<Data> { // ResettableIterator<Data>

private:

protected:

  const typename BinaryTree<Data>::Node* root = nullptr;
  const typename BinaryTree<Data>::Node* current = nullptr;
  StackLst<const typename BinaryTree<Data>::Node*> stack;

  const typename BinaryTree<Data>::Node* DeepestLeftLeaf(const typename BinaryTree<Data>::Node* actual);

public:

  // Specific constructors
  // BTPostOrderIterator(argument) specifiers; // An iterator over a given binary tree
  BTPostOrderIterator(const BinaryTree<Data>& anotherBinaryTree); 

  /* ************************************************************************ */

  // Copy constructor
  // BTPostOrderIterator(argument) specifiers;
  BTPostOrderIterator(const BTPostOrderIterator& anotherIterator);  

  // Move constructor
  // BTPostOrderIterator(argument) specifiers;
  BTPostOrderIterator(BTPostOrderIterator&& anotherIterator) noexcept;  

  /* ************************************************************************ */

  // Destructor
  // ~BTPostOrderIterator() specifiers;
  ~BTPostOrderIterator() = default; 

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTPostOrderIterator& operator=(const BTPostOrderIterator<Data>& anotherIterator); 

  // Move assignment
  // type operator=(argument) specifiers;
  BTPostOrderIterator& operator=(BTPostOrderIterator<Data>&& anotherIterator) noexcept; 

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  bool operator==(const BTPostOrderIterator& anotherIterator) const noexcept;  
  inline bool operator!=(const BTPostOrderIterator& anotherIterator) const noexcept { return !(operator==(anotherIterator)); }; 

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override;  

  // type Terminated() specifiers; // (should not throw exceptions)
  inline bool Terminated() const noexcept override { return (current == nullptr); };  

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  
  // type operator++() specifiers; // (throw std::out_of_range when terminated)
  BTPostOrderIterator<Data>& operator++() override; 

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // type Reset() specifiers; // (should not throw exceptions)
  inline void Reset() noexcept override { stack.Clear(); current=DeepestLeftLeaf(root); };  

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator: virtual public MutableIterator<Data>,   // Must extend MutableIterator<Data>,
virtual public BTPostOrderIterator<Data> {                                // BTPostOrderIterator<Data>

private:

protected:

public:

  // Specific constructors
  // BTPostOrderMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree
  inline BTPostOrderMutableIterator(MutableBinaryTree<Data>& anotherBinaryTree) : BTPostOrderIterator<Data>(anotherBinaryTree) {;}; 

  /* ************************************************************************ */

  // Copy constructor
  // BTPostOrderMutableIterator(argument) specifiers;
  inline BTPostOrderMutableIterator(const BTPostOrderMutableIterator& anotherIterator) : BTPostOrderIterator<Data>(anotherIterator){;}; 

  // Move constructor
  // BTPostOrderMutableIterator(argument) specifiers;
  inline BTPostOrderMutableIterator(BTPostOrderMutableIterator&& anotherIterator) noexcept : BTPostOrderIterator<Data>(std::move(anotherIterator)) {;};  

  /* ************************************************************************ */

  // Destructor
  // ~BTPostOrderMutableIterator() specifiers;
  ~BTPostOrderMutableIterator() = default;  

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  inline BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator& anotherIterator);  

  // Move assignment
  // type operator=(argument) specifiers;
  inline BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator&& anotherIterator) noexcept;  
  
  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  inline bool operator==(const BTPostOrderMutableIterator& anotherIterator) const noexcept { return BTPostOrderIterator<Data>::operator==(anotherIterator); };  
  inline bool operator!=(const BTPostOrderMutableIterator& anotherIterator) const noexcept { return !(operator==(anotherIterator)); };  

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override; 

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>,   // Must extend ForwardIterator<Data>,
virtual public ResettableIterator<Data> {                         // ResettableIterator<Data>

private:

protected:

  const typename BinaryTree<Data>::Node* current = nullptr;
  const typename BinaryTree<Data>::Node* root = nullptr;
  StackLst<const typename BinaryTree<Data>::Node*> stack;

  const typename BinaryTree<Data>::Node* FindDeepestLeftLeaf(const typename BinaryTree<Data>::Node*);


public:

  // Specific constructors
  // BTInOrderIterator(argument) specifiers; // An iterator over a given binary tree
  BTInOrderIterator(const BinaryTree<Data>& anotherBinaryTree);   

  /* ************************************************************************ */

  // Copy constructor
  // BTInOrderIterator(argument) specifiers;
  BTInOrderIterator(const BTInOrderIterator& anotherIterator);  

  // Move constructor
  // BTInOrderIterator(argument) specifiers;
  BTInOrderIterator(BTInOrderIterator&& anotherIterator) noexcept;  

  /* ************************************************************************ */

  // Destructor
  // ~BTInOrderIterator() specifiers;
  virtual ~BTInOrderIterator() = default; 

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTInOrderIterator& operator=(const BTInOrderIterator& anotherIterator); 

  // Move assignment
  // type operator=(argument) specifiers;
  BTInOrderIterator& operator=(BTInOrderIterator&& anotherIterator) noexcept; 

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  bool operator==(const BTInOrderIterator& anotherIterator) const noexcept; 
  inline bool operator!=(const BTInOrderIterator& anotherIterator) const noexcept { return !(operator==(anotherIterator)); }; 

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  
  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override; 
  // type Terminated() specifiers; // (should not throw exceptions)
  inline bool Terminated() const noexcept override { return (current == nullptr); }; 

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // type operator++() specifiers; // (throw std::out_of_range when terminated)
  BTInOrderIterator<Data>& operator++() override; 

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  
  // type Reset() specifiers; // (should not throw exceptions)
  inline void Reset() noexcept override { stack.Clear(); current = FindDeepestLeftLeaf(root); }; 

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator : virtual public MutableIterator<Data>, // Must extend MutableIterator<Data>,
virtual public BTInOrderIterator<Data> {                               // BTInOrderIterator<Data>

private:

protected:

public:

  // Specific constructors
  // BTInOrderMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree
  inline BTInOrderMutableIterator(MutableBinaryTree<Data>& anotherBinaryTree) : BTInOrderIterator<Data>(anotherBinaryTree) {;}; 
  /* ************************************************************************ */

  // Copy constructor
  // BTInOrderMutableIterator(argument) specifiers;
  inline BTInOrderMutableIterator(const BTInOrderMutableIterator& anotherIterator) : BTInOrderIterator<Data>(anotherIterator) {;};  

  // Move constructor
  // BTInOrderMutableIterator(argument) specifiers;
  inline BTInOrderMutableIterator(BTInOrderMutableIterator&& anotherIterator) noexcept : BTInOrderIterator<Data>(std::move(anotherIterator)) {;}; 
  /* ************************************************************************ */

  // Destructor
  // ~BTInOrderMutableIterator() specifiers;
  virtual ~BTInOrderMutableIterator() = default;  

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  inline BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator& anotherIterator);  

  // Move assignment
  // type operator=(argument) specifiers;
  inline BTInOrderMutableIterator& operator=(BTInOrderMutableIterator&& anotherIterator) noexcept;  

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  inline bool operator==(const BTInOrderMutableIterator& anotherIterator) const noexcept { return BTInOrderIterator<Data>::operator==(anotherIterator); };  
  inline bool operator!=(const BTInOrderMutableIterator& anotherIterator) const noexcept { return !(operator==(anotherIterator)); };  

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  
  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override;  

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>,   // Must extend ForwardIterator<Data>,
virtual public ResettableIterator<Data> {                         // ResettableIterator<Data>

private:

protected:

  const typename BinaryTree<Data>::Node* current = nullptr;
  const typename BinaryTree<Data>::Node* root = nullptr;
  QueueLst<const typename BinaryTree<Data>::Node*> queue;

public:

  // Specific constructors
  // BTBreadthIterator(argument) specifiers; // An iterator over a given binary tree
  BTBreadthIterator(const BinaryTree<Data>& anotherBinaryTree);   

  /* ************************************************************************ */

  // Copy constructor
  // BTBreadthIterator(argument) specifiers;
  BTBreadthIterator(const BTBreadthIterator& anotherIterator);  

  // Move constructor
  // BTBreadthIterator(argument) specifiers;
  BTBreadthIterator(BTBreadthIterator&& anotherIterator) noexcept;  

  /* ************************************************************************ */

  // Destructor
  // ~BTBreadthIterator() specifiers;
  virtual ~BTBreadthIterator() = default; 

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTBreadthIterator& operator=(const BTBreadthIterator& anotherIterator);   

  // Move assignment
  // type operator=(argument) specifiers;
  BTBreadthIterator& operator=(BTBreadthIterator&& anotherIterator) noexcept;   

  /* ************************************************************************ */

  // Comparison operators

  // type operator==(argument) specifiers;
  bool operator==(const BTBreadthIterator& anotherIterator) const noexcept; 
  // type operator!=(argument) specifiers;  
  inline bool operator!=(const BTBreadthIterator& anotherIterator) const noexcept { return !(operator==(anotherIterator)); }    

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  
  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override;   
 
  // type Terminated() specifiers; // (should not throw exceptions)
  inline bool Terminated() const noexcept override { return (current == nullptr); }; 

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  
  // type operator++() specifiers; // (throw std::out_of_range when terminated)
  BTBreadthIterator& operator++() override;   

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // type Reset() specifiers; // (should not throw exceptions)
  inline void Reset() noexcept override { queue.Clear(); current = root; };   

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : virtual public MutableIterator<Data>,   // Must extend MutableIterator<Data>,
virtual public BTBreadthIterator<Data> {                                 // BTBreadthIterator<Data>

private:

protected:

public:

  // Specific constructors// BTBreadthMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree
  inline BTBreadthMutableIterator(MutableBinaryTree<Data>& anotherBinaryTree) : BTBreadthIterator<Data>(anotherBinaryTree) {;}; 

  /* ************************************************************************ */

  // Copy constructor
   // BTBreadthMutableIterator(argument) specifiers;
  inline BTBreadthMutableIterator(const BTBreadthMutableIterator& anotherIterator) : BTBreadthIterator<Data>(anotherIterator) {;}; 

  // Move constructor
  // BTBreadthMutableIterator(argument) specifiers;
  inline BTBreadthMutableIterator(BTBreadthMutableIterator&& anotherIterator) noexcept : BTBreadthIterator<Data>(std::move(anotherIterator)) {;};   

  /* ************************************************************************ */

  // Destructor
  // ~BTBreadthMutableIterator() specifiers;
  ~BTBreadthMutableIterator() = default;   

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  inline BTBreadthMutableIterator& operator=(const BTBreadthMutableIterator& anotherIterator);  

  // Move assignment
  // type operator=(argument) specifiers;
  inline BTBreadthMutableIterator& operator=(BTBreadthMutableIterator&& anotherIterator) noexcept;  

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  inline bool operator==(const BTBreadthMutableIterator& anotherIterator) const noexcept { return BTBreadthIterator<Data>::operator==(anotherIterator); };  
  inline bool operator!=(const BTBreadthMutableIterator& anotherIterator) const noexcept { return !(operator==(anotherIterator)); };  

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  
  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override;   

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
