template <class RandomAccessIterator, class Compare>
 RandomAccessIterator galop(RandomAccessIterator start, RandomAccessIterator finish, RandomAccessIterator a, Compare comp) {
    RandomAccessIterator l = start;
    RandomAccessIterator r = finish;
    while (1 < r - l) {
        RandomAccessIterator x = l + (r - l) / 2;
        if (comp(*x, *a)) {
            l = x;
        } else {
            r = x;
        }
    }
    return l;
 }

template <class RandomAccessIterator, class Compare>
 void merge(RandomAccessIterator start, RandomAccessIterator fin, RandomAccessIterator mid, RandomAccessIterator finish, RandomAccessIterator buffer, Compare comp, const ITimSortParams& params) {
    int a, b = 0;
    for (int i = 0, j = 0, ind = 0; start + i != fin || mid + j != finish; ) {
        if (start + i != fin && mid + j != finish) {
            if (comp(start[i], mid[j])) {
                a++;
                b = 0;
                if (a >= params.getGallop()) {
                    a = 0;
                    RandomAccessIterator r = galop(start + i, fin, mid + j, comp);
                    for (;start + i != r;) {
                        swap(start[i++], buffer[ind++]);
                    }
                } else {
                    swap(buffer[ind++], start[i++]);
                }
            } else {
                b++;
                a = 0;
                if(b >= params.getGallop())
                {
                    b = 0;
                    RandomAccessIterator r = galop(mid + j, finish, start + i, comp);
                    for (;mid + j != r;) {
                        swap(mid[j++], buffer[ind++]);
                    }
                } else {
                    swap(buffer[ind++], mid[j++]);
                }
            }
        } else {
            if (start + i == fin) {
                swap(buffer[ind++], mid[j++]);
            } else {
                swap(buffer[ind++], start[i++]);
            }
        }
    }
 }
template <class RandomAccessIterator, class Compare>
 void inplaceMerge(RandomAccessIterator start, RandomAccessIterator finish, int k, Compare comp, const ITimSortParams& params) {
    const int n = finish - start;
    const int p = sqrt(n);
    int x = k % p;
    int z = n - n % p;
    std::swap_ranges(start + k - x, start + k - x + p, start + z - p);
    z -= p;
    for(int i = 0; i < z; i += p)
    {
        for(int j = i + p; j < z; j += p) {
            if(comp(start[j], start[i]) || (!comp(start[j], start[i]) && !comp(start[i], start[j]) && comp(start[j + p - 1], start[i + p - 1]))) {
                std::swap_ranges(start + i, start + i + p, start + j);
            }
        }
    }
    RandomAccessIterator buffer = start + z, it1, it2;
    for(int i = 0; i < z - 2 * p; i+=p) {
        it1 = start + i;
        it2 = start + p + i;
        std::swap_ranges(it1, it2, buffer);
        merge(buffer, buffer + p, it2, it2 + p, it1, comp, params);
    }
    int s = n - z;
    buffer = finish - s;
    insertionSort(buffer - s, finish, buffer - s, comp);
    for (int i = n - 2 * s; i >= s; i -= s) {
        it1 = start + i - s;
        it2 = start + i;
        std::swap_ranges(it1, it2, buffer);
        merge(buffer, finish, it2, it2 + s, it1, comp, params);
    }
    insertionSort(start, start + 2 * s, start, comp);
    insertionSort(buffer - s, finish, buffer - s, comp);
 }
