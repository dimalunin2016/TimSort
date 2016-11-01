template <class it, class Compare>
  void runsMerge(vector<pair <it, int> > &runs, Compare comp, const ITimSortParams& params) {
        int n = runs.size();
        if (n == 1)
            return;
        pair<it, int> x = runs.back();
        runs.pop_back();
        pair<it, int> y = runs.back();
        runs.pop_back();
        pair<it, int> z;
        while(!runs.empty())
        {
            z = runs.back();
            runs.pop_back();
            EWhatMerge  condition= params.whatMerge(x.second, y.second, z.second);
            if(condition == WM_MergeXY) {
                int size = x.second + y.second;
                inplaceMerge(y.first, x.first + x.second, y.second, comp, params);
                x = y;
                x.second = size;
                y = z;
            }
            else if(condition == WM_MergeYZ) {
                int size = z.second + y.second;
                inplaceMerge(z.first, y.first + y.second, z.second, comp, params);
                y = z;
                y.second = size;
            } else if(condition == WM_NoMerge) {
                runs.push_back(z);
                break;
            }

        }
        if(params.needMerge(x.second, y.second)) {
            int size = x.second + y.second;
            inplaceMerge(y.first, x.first + x.second, y.second, comp, params);
            y.second = size;
            runs.push_back(y);
        } else {
            runs.push_back(y);
            runs.push_back(x);
        }
 }
template <class RandomAccessIterator, class Compare>
  void mergeEverything(RandomAccessIterator first, RandomAccessIterator last, vector<int> &len, Compare comp, const ITimSortParams& params) {
        vector<pair <RandomAccessIterator, int> > runs;
        int size = len.size();
        RandomAccessIterator i = first;
        for (int ind = 0; ind < size; ++ind) {
            runs.push_back(std::make_pair(i, len[ind]));
            i += (len[ind]);
            if (runs.size() >= 2) {
                runsMerge(runs, comp, params);
            }
        }
        if(runs.size() <= 1)
            return;
        RandomAccessIterator finale = runs.back().first + runs.back().second;
        while(runs.size() > 1) {
            runs.pop_back();
            RandomAccessIterator start = runs.back().first;
            int mid = runs.back().second;
            inplaceMerge(start, finale, mid, comp, params);
        }
  }
