     */
    inline void Add(bst_float fv,
                    const std::vector<bst_gpair> &gpair,
                    const BoosterInfo &info,
                    const bst_uint ridx) {
      while (istart < hist.size && !(fv < hist.cut[istart])) ++istart;
      utils::Assert(istart != hist.size, "the bound variable must be max");
      hist.data[istart].Add(gpair, info, ridx);
    }
    /*!
