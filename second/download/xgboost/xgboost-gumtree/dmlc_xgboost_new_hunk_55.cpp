     */
    inline void Add(bst_float fv,
                    const std::vector<bst_gpair> &gpair,
                    const MetaInfo &info,
                    const bst_uint ridx) {
      while (istart < hist.size && !(fv < hist.cut[istart])) ++istart;
      CHECK_NE(istart, hist.size);
      hist.data[istart].Add(gpair, info, ridx);
    }
    /*!
