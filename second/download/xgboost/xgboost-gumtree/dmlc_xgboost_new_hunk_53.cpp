    /*! \brief size of histogram */
    unsigned size;
    // default constructor
    HistUnit() {}
    // constructor
    HistUnit(const bst_float *cut, TStats *data, unsigned size)
        : cut(cut), data(data), size(size) {}
    /*! \brief add a histogram to data */
    inline void Add(bst_float fv,
                    const std::vector<bst_gpair> &gpair,
                    const MetaInfo &info,
                    const bst_uint ridx) {
      unsigned i = std::upper_bound(cut, cut + size, fv) - cut;
      CHECK_NE(size, 0) << "try insert into size=0";
      CHECK_LT(i, size);
      data[i].Add(gpair, info, ridx);
    }
  };
