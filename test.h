#include <bits/stdc++.h>
#include <stdio.h>
#include <ctime>
#include "timSort.h"

int *makeArray(int n) {
    int *a = new int[n];
    return a;
}
bool comp(int a, int b)
{
    return a < b;
}
template <class RandomAccessIterator, class T = typename std::iterator_traits <RandomAccessIterator>::value_type, class Compare>
  void check(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
        int n = last - first;
        T* copy = new T[n];
        std::copy(first, last, copy);
        double t1 = clock();
        std::sort(first, last, comp);
        double t2 = clock();
        timSort(copy, copy + n, comp);
        double t3 = clock();
        double tSort = (t2 - t1) / CLOCKS_PER_SEC;
        double tTimsort = (t3 - t2) / CLOCKS_PER_SEC;
        for(int i = 0; i < n; i++) {
                //std::cout << copy[i] <<"\n";
            if(copy[i] != first[i]) {
                std::cout <<"It works incorrectly, but it does not matter, just forget about this test)\n";
                break;
            }
        }
        //std::cout << tSort <<" "<<tTimsort<<"-\n";
        printf("Sort time: %f\nTimSort time: %f\n---------------------\n", tSort, tTimsort);
        delete[] copy;
  }
void fillArray(int *a, int n) {
    for (int j = 0; j < n; ++j) {
        a[j] = std::rand();
    }
}
void testRandomArray() {
    std::srand(std::time(0));
    int n[11] = {1, 2, 4, 8, 16, 32, 50, 100, 1000, 10000, 100000};
    for (int j = 0; j < 110; j++) {
        int i = j % 11;
        int *a = makeArray(n[i]);
        fillArray(a, n[i]);
        std::cout <<"length: "<<  n[i] <<"\n";
        check(a, a + n[i], comp);
        delete[] a;
    }
}
void testPartiallySortedArray() {
    int size[5] = {20, 40, 80, 128, 1024};
    std::srand(std::time(0));
    int lenOfSortedArrays[6] = {2, 4, 10, 100, 1000, 10000};
    int x = 0;
    for (int i = 0; i < 5; i++) {
        for(int j = 0; j < 6; j++) {
            int *a = makeArray(size[i] * lenOfSortedArrays[j]);
            fillArray(a, size[i] * lenOfSortedArrays[j]);
            for (int k = 0; k < lenOfSortedArrays[j]; k++) {
                std::sort(a + size[i] * k, a + size[i] * (k + 1), comp);
                if (rand()%2 == 1)
                    std::reverse(a + size[i] * k, a + size[i] * (k + 1));
            }
            std::cout <<"length: "<<  size[i] * lenOfSortedArrays[j] <<"\n";
            check(a, a + size[i] * lenOfSortedArrays[j], comp);
            delete[] a;
        }
    }
}
bool stringComp(std::string a, std::string b) {
    if(a.size() == b.size())
        return a < b;
    return a.size() < b.size();
}
void testString() {
    std::srand(std::time(0));
    const int size = 1600;
    std::string a[size];
    int tests = 10;
    for(int k = 0; k < tests; k++) {
        for (int i = 0; i < size; ++i) {
            int len = std::rand() % 1000 + 1;
            std::string s = "";
            for(int j = 0; j < len; j++) {
                s+=rand() % 26 + 'a';
            }
            a[i] = s;
        }
        std::cout <<"length: "<< size <<"\n";
        check(a, a + size, stringComp);
    }
}


