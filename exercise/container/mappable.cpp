
namespace lasd {

/* ************************************************************************** */
 // PreOrderMappableContainer

  // Specific member function (inherited from MappableContainer)
  template <typename Data>
  inline void PreOrderMappableContainer<Data>::Map(MapFun function)
  {
    PreOrderMap(function);
  }

/* ************************************************************************** */
  // PostOrderMappableContainer

  // Specific member function (inherited from MappableContainer)
  template <typename Data>
  inline void PostOrderMappableContainer<Data>::Map(MapFun function)
  {
    PostOrderMap(function);
  }

/* ************************************************************************** */

// Specific member function (InOrderMappableContainer)
template <typename Data>
inline void InOrderMappableContainer<Data>::Map(MapFun function) {
    InOrderMap(function);
}

/* ************************************************************************** */

// Specific member function (BreadthMappableContainer)
template <typename Data>
inline void BreadthMappableContainer<Data>::Map(MapFun function) {
    BreadthMap(function);
}

/* ************************************************************************** */


}
