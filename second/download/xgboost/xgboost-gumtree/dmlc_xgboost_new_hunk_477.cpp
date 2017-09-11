    inline void Clear(void) {
      size = 0;
    }
    /*!
     * \brief copy content from src
     * \param src source sketch
     */
    inline void CopyFrom(const Summary &src) {
      size = src.size;
      std::memcpy(data, src.data, sizeof(Entry) * size);
    }
    /*!
     * \brief set current summary to be pruned summary of src
     *        assume data field is already allocated to be at least maxsize
     * \param src source summary
     * \param maxsize size we can afford in the pruned sketch
     */
    inline void SetPrune(const Summary &src, RType maxsize) {
      if (src.size <= maxsize) {
        this->CopyFrom(src); return;
      }
      const RType max_rank = src.MaxRank();
      const size_t n = maxsize - 1;
      data[0] = src.data[0];
      this->size = 1;
      // lastidx is used to avoid duplicated records
      size_t i = 0, lastidx = 0;
      for (RType k = 1; k < n; ++k) {
        RType d2 = (k * max_rank) / n * 2;
        // find first i such that  d < (rmax[i+1] + rmin[i+1]) / 2 
        while (i < src.size - 1 &&
               d2 < src.data[i + 1].rmax + src.data[i + 1].rmin) ++i;
        if (i == src.size - 1) break;
        if (d2 < src.data[i].rmin_next() + src.data[i + 1].rmax_prev()) {
          if (i != lastidx) {
            data[size++] = src.data[i]; lastidx = i;
          }
        } else {
          if (i + 1 != lastidx) {
            data[size++] = src.data[i + 1]; lastidx = i + 1;
          }
        }
      }
      if (lastidx != src.size - 1) {
        data[size++] = src.data[src.size - 1];
      }
    }
    inline void SetCombine(const Summary &sa,
                           const Summary &sb) {
      utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge"); 
      const Entry *a = sa.data, *a_end = sa.data + sa.size;
      const Entry *b = sb.data, *b_end = sb.data + sb.size;
      // extended rmin value
      RType aprev_rmin = 0, bprev_rmin = 0;
      Entry *dst = this->data;
      while (a != a_end && b != b_end) {
        // duplicated value entry
        if (a->value == b->value) {
          *dst = Entry(a->rmin + b->rmin,
                       a->rmax + b->rmax,
                       a->wmin + b->wmin, a->value);
          aprev_rmin = a->rmin_next();
          bprev_rmin = b->rmin_next();
          ++dst; ++a; ++b;
        } else if (a->value < b->value) {
          *dst = Entry(bprev_rmin + a->rmin,
                       a->rmax + b->rmax_prev(),
                       a->wmin, a->value);
          aprev_rmin = a->rmin_next();
          ++dst; ++a;
        } else {
          *dst = Entry(aprev_rmin + b->rmin,
                       b->rmax + a->rmax_prev(),
                       b->wmin, b->value);
          bprev_rmin = b->rmin_next();
          ++dst; ++b;
        }
      }
      if (a != a_end) {
        RType brmax = (b_end - 1)->rmax;
        do {
          *dst = Entry(bprev_rmin + a->rmin, brmax + a->rmax, a->wmin, a->value);
          ++dst; ++a;
        } while (a != a_end);
      }
      if (b != b_end) {
        RType armax = (a_end - 1)->rmax;
        do {
          *dst = Entry(aprev_rmin + b->rmin, armax + b->rmax, b->wmin, b->value);
          ++dst; ++b;
        } while (b != b_end);
      }
      this->size = dst - data;
      utils::Assert(size <= sa.size + sb.size, "bug in combine");
    }
  };
  // same as summary, but use STL to backup the space
  struct SummaryContainer : public Summary {
    std::vector<Entry> space;
    /*! \brief reserve space for summary */
    inline void Reserve(size_t size) {
      if (size > space.size()) {
        space.resize(size);
        this->data = BeginPtr(space);
      }
    }
    /*! 
     * \brief set the space to be merge of all Summary arrays
