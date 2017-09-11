inline void Add(bst_float fv,
                    bst_gpair gstats) {
      while (istart < hist.size && !(fv < hist.cut[istart])) ++istart;
      CHECK_NE(istart, hist.size);
      hist.data[istart].Add(gstats);
    }