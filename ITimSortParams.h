enum EWhatMerge {
    WM_NoMerge,
    WM_MergeXY,
    WM_MergeYZ
};

struct ITimSortParams {
    virtual int minRun(int n) const = 0;
    virtual bool needMerge(int lenX, int lenY) const = 0;
    virtual EWhatMerge whatMerge(int lenX, int lenY, int lenZ) const = 0;
    virtual int getGallop() const = 0;
};
struct IDefaultTimSortParams : public ITimSortParams {
    IDefaultTimSortParams() {}
    virtual int minRun(int n) const {
        bool flag = false;
        while (n >= 64) {
            flag |= n & 1;
            n >>= 1;
        }
        return n + flag;
    }
    virtual bool needMerge(int lenX, int lenY) const {
        return lenY <= lenX;
    }
    virtual EWhatMerge whatMerge(int lenX, int lenY, int lenZ) const {
        if (lenZ > lenX + lenY && lenY > lenX)
            return WM_NoMerge;
        if (lenZ <= lenX + lenY)
            return (lenX <= lenZ) ? WM_MergeXY : WM_MergeYZ;
        if (lenY <= lenX)
            return WM_MergeXY;
    }
    virtual int getGallop() const {
        return 7;
    }
};
