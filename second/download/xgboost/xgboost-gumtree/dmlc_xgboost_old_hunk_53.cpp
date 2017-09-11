    /*! \brief size of histogram */
    unsigned size;
    // default constructor
    HistUnit(void) {}
    // constructor
    HistUnit(const bst_float *cut, TStats *data, unsigned size)
        : cut(cut), data(data), size(size) {}
    /*! \brief add a histogram to data */
    inline void Add(bst_float fv,
                    const std::vector<bst_gpair> &gpair,
                    const BoosterInfo &info,
                    const bst_uint ridx) {
      unsigned i = std::upper_bound(cut, cut + size, fv) - cut;
      utils::Assert(size != 0, "try insert into size=0");
      utils::Assert(i < size,
                    "maximum value must be in cut, fv = %g, cutmax=%g", fv, cut[size-1]);
      data[i].Add(gpair, info, ridx);
    }
  };
