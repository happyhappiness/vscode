inline void Add(bst_float fv,
                    bst_gpair gstats) {
      while (istart < hist.size && !(fv < hist.cut[istart])) ++istart;
      utils::Assert(istart != hist.size, "the bound variable must be max");
      hist.data[istart].Add(gstats);
    }