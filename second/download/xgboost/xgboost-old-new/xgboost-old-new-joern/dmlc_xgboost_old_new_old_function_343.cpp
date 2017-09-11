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