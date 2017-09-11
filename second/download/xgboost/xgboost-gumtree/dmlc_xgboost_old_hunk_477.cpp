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
      const RType max_rank = src.MaxRank();
      this->size = maxsize;
      data[0] = src.data[0];
      RType n = maxsize - 1;
      RType top = 1;
      for (RType i = 1; i < n; ++i) {
        RType k = (i * max_rank) / n;
        while (k > src.data[top + 1].rmax) ++top;
        // assert src.data[top].rmin <= k
        // because k > src.data[top].rmax >= src.data[top].rmin
        if ((k - src.data[top].rmin) < (src.data[top+1].rmax - k)) {
          data[i] = src.data[top];
        } else {
          data[i] = src.data[top + 1];
        }
      }
      data[n] = src.data[src.size - 1];
    }
    inline void SetCombine(const Summary &sa,
                           const Summary &sb) {
      utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge"); 
      const Entry *a = sa.data, *a_end = sa.data + sa.size;
      const Entry *b = sb.data, *b_end = sb.data + sb.size;
      this->size = sa.size + sb.size;
      RType aprev_rmin = 0, bprev_rmin = 0;
      Entry *dst = this->data;
      while (a != a_end && b != b_end) {
        if (a->value < b->value) {
          *dst = Entry(bprev_rmin + a->rmin,
                       a->rmax + b->rmax - 1, a->value);
          aprev_rmin = a->rmin;
          ++dst; ++a;
        } else {
          *dst = Entry(aprev_rmin + b->rmin, 
                       b->rmax + a->rmax - 1, b->value);
          bprev_rmin = b->rmin;
          ++dst; ++b;
        }
      }
      if (a != a_end) {
        RType bprev_rmax = (b_end - 1)->rmax;
        do {
          *dst = Entry(bprev_rmin + a->rmin, bprev_rmax + a->rmax, a->value);
          ++dst; ++a;
        } while (a != a_end);
      }
      if (b != b_end) {
        RType aprev_rmax = (a_end - 1)->rmax;
        do {
          *dst = Entry(aprev_rmin + b->rmin, aprev_rmax + b->rmax, b->value);
          ++dst; ++b;
        } while (b != b_end);
      }
      utils::Assert(dst == data + size, "bug in combine");
    }
  };
  // same as summary, but use STL to backup the space
  struct SummaryContainer : public Summary {
    std::vector<Entry> space;
    /*! \brief reserve space for summary */
    inline void Reserve(size_t size) {
      space.resize(size);
      this->data = BeginPtr(space);
    }
    /*! 
     * \brief set the space to be merge of all Summary arrays
