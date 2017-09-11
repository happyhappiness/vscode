inline void SetPrune(const WQSummary<DType, RType> &src, size_t maxsize) {
    if (src.size <= maxsize) {
      this->CopyFrom(src); return;
    }
    RType begin = src.data[0].rmax;
    size_t n = maxsize - 1, nbig = 0;
    RType range = src.data[src.size - 1].rmin - begin;
    // prune off zero weights
    if (range == 0.0f) {
      // special case, contain only two effective data pts
      this->data[0] = src.data[0];
      this->data[1] = src.data[src.size - 1];
      this->size = 2;
      return;
    } else {
      range = std::max(range, static_cast<RType>(1e-3f));
    }
    const RType chunk = 2 * range / n;
    // minimized range
    RType mrange = 0;
    {
      // first scan, grab all the big chunk
      // moving block index
      size_t bid = 0;
      for (size_t i = 1; i < src.size; ++i) {
        if (CheckLarge(src.data[i], chunk)) {
          if (bid != i - 1) {
            mrange += src.data[i].rmax_prev() - src.data[bid].rmin_next();
          }
          bid = i; ++nbig;
        }
      }
      if (bid != src.size - 2) {
        mrange += src.data[src.size-1].rmax_prev() - src.data[bid].rmin_next();
      }
    }
    if (nbig >= n - 1) {
      // see what was the case
      utils::Printf("LOG: check quantile stats, nbig=%lu, n=%lu\n", nbig, n);
      utils::Printf("LOG: srcsize=%lu, maxsize=%lu, range=%g, chunk=%g\n",
                    src.size, maxsize, static_cast<double>(range),
                    static_cast<double>(chunk));
      src.Print();
      utils::Assert(nbig < n - 1, "quantile: too many large chunk");
    }
    this->data[0] = src.data[0];
    this->size = 1;
    // use smaller size
    n = n - nbig;
    // find the rest of point
    size_t bid = 0, k = 1, lastidx = 0;
    for (size_t end = 1; end < src.size; ++end) {
      if (end == src.size - 1 || CheckLarge(src.data[end], chunk)) {
        if (bid != end - 1) {
          size_t i = bid;
          RType maxdx2 = src.data[end].rmax_prev() * 2;
          for (; k < n; ++k) {
            RType dx2 =  2 * ((k * mrange) / n + begin);
            if (dx2 >= maxdx2) break;
            while (i < end &&
                   dx2 >= src.data[i + 1].rmax + src.data[i + 1].rmin) ++i;
            if (i == end) break;
            if (dx2 < src.data[i].rmin_next() + src.data[i + 1].rmax_prev()) {
              if (i != lastidx) {
                this->data[this->size++] = src.data[i]; lastidx = i;
              }
            } else {
              if (i + 1 != lastidx) {
                this->data[this->size++] = src.data[i + 1]; lastidx = i + 1;
              }
            }
          }
        }
        if (lastidx != end) {
          this->data[this->size++] = src.data[end];
          lastidx = end;
        }
        bid = end;
        // shift base by the gap
        begin += src.data[bid].rmin_next() - src.data[bid].rmax_prev();
      }
    }
  }