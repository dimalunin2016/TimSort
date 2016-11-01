template <class RandomAccessIterator, class Compare>
  void insertionSort(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator begin, Compare comp) {
        for (RandomAccessIterator i = begin; i != last; ++i) {
            RandomAccessIterator l = first - 1, r = i;
            int u = r - l;
            while(1 < u)
            {
                RandomAccessIterator x = l + u/2;
                if(comp(*x, *i)) {
                    l = x;
                }
                else
                {
                    r = x;
                }
                u = r - l;
            }
            RandomAccessIterator j = i;
            for (; j != r; --j) {
                swap(*j, *(j - 1));
            }
        }

  }
