#ifndef MODULE_SEARCH_MAX_M_ELEMENTS_HXX
#define MODULE_SEARCH_MAX_M_ELEMENTS_HXX

// STD includes
#include <functional>
#include <limits>

namespace SHA_Search
{
  /// Max M Elements
  /// Identify the m maximal/minimal values sorted in decreasing/increasing order.
  ///
  /// @details using this algorithm with the size of the vector as the number
  /// of elements to be found will give you a bubble sort algorithm in O(N�).
  ///
  /// @complexity O(N * m * O(f(a, b))) with:
  /// - m number of elements to be looking for
  /// - f(a, b) the compare functor used: O(1) for the default std::greater_equal
  ///
  /// @tparam Container type used to return the elements.
  /// @tparam Iterator type using to go through the collection.
  /// @tparam Compare functor type.
  ///
  /// @param begin,end iterators to the initial and final positions of
  /// the sequence to be sorted. The range used is [first,last), which contains all the elements between
  /// first and last, including the element pointed by first but not the element pointed by last.
  /// @param m the numbers of max elements value to be found.
  ///
  /// @return a vector of sorted in decreasing/increasing order of the m maximum/minimum
  /// elements, an empty array in case of failure.
  template <typename Container, typename Iterator, typename Compare /*= std::greater_equal*/>
  Container MaxMElements(const Iterator& begin, const Iterator& end, const int m)
  {
    if (m < 1 || m > std::distance(begin, end))
      return Container();

    // Initiale values depends on the comparator functor
    const Iterator::value_type limitValue =
      Compare()(0, std::numeric_limits<Iterator::value_type>::lowest()) ?
        std::numeric_limits<Iterator::value_type>::lowest() :
        std::numeric_limits<Iterator::value_type>::max();

    // Allocate the container final size
    Container maxMElements;
    maxMElements.resize(m, limitValue);
    for (Iterator it = begin; it != end; ++it)
    {
      // Insert the value at the right place and bubble down replacement value
      int index = 0;
      Iterator::value_type tmpVal = *it;
      for (Container::iterator subIt = maxMElements.begin(); index < m; ++subIt, ++index)
        if (Compare()(tmpVal, *subIt))
          std::swap(*subIt, tmpVal);
    }

    return maxMElements;
  }
};

#endif() // MODULE_COLLECTIONS_SEARCH_HXX
