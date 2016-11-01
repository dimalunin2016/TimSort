#include <bits/stdc++.h>

using std::pair;
using std::swap;
using std::min;
using std::vector;

#include "ITimSortParams.h"
#include "insertionSort.h"
#include "inplaceMerge.h"
#include "makeRuns.h"
#include "mergeRuns.h"


const IDefaultTimSortParams DefaultTimSortParams;
bool comporator(int a, int b) {
    return a < b;
}
template <class RandomAccessIterator, class Compare>
  void timSort(RandomAccessIterator first, RandomAccessIterator last, Compare comp, const ITimSortParams& params = DefaultTimSortParams)
  {
        int n = last - first;
        if (n <= 64) {
            insertionSort(first, last, first, comp);
            return;
        }
        int minrun = params.minRun(n);
        vector<int> len;
        makeRuns(first, last, minrun, len, comp);
        mergeEverything(first, last, len, comp, params);
  }
template <class RandomAccessIterator>
  void timSort(RandomAccessIterator first, RandomAccessIterator last, const ITimSortParams& params = DefaultTimSortParams)
  {
        timSort(first, last, comporator, params);
  }
