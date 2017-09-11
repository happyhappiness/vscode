      // find first i such that  d < (rmax[i+1] + rmin[i+1]) / 2
      while (i < src.size - 1
             && dx2 >= src.data[i + 1].rmax + src.data[i + 1].rmin) ++i;
      utils::Assert(i != src.size - 1, "this cannot happen");
      if (dx2 < src.data[i].rmin_next() + src.data[i + 1].rmax_prev()) {
        if (i != lastidx) {
          data[size++] = src.data[i]; lastidx = i;
