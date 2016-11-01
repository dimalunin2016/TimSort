template <class RandomAccessIterator, class Compare>
  void makeRuns(RandomAccessIterator first, RandomAccessIterator last, int minrun, vector<int> &len, Compare comp) {
        for (RandomAccessIterator i = first; i != last;) {
            int run = 0;
            RandomAccessIterator begin = i;
            if(i + 1 != last && comp (*i, *(i + 1)))
            {
                while (i != last - 1 && comp(*i, *(i + 1))) {
                    run++;
                    ++i;
                }
                ++i;
            }
            else
            {
                while (i != last - 1 && !comp(*i, *(i + 1))) {
                    run++;
                    ++i;
                }
                ++i;
                std::reverse(begin, i);
            }
            if (run < minrun || last - i <= minrun)
            {
                RandomAccessIterator start = i;
                for (;i != last && i != (begin + minrun); ++i) {
                        ++run;
                }
                if (last - i <= minrun) {
                    for (;i != last; ++i) {
                        ++run;
                    }
                }
                insertionSort(begin, i, start, comp);
            }
            len.push_back(run + 1);
        }
  }
