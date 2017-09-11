inline void SetCombine(const WQSummary &sa,
                         const WQSummary &sb) {
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
        *dst = Entry(a->rmin + bprev_rmin,
                     a->rmax + b->rmax_prev(),
                     a->wmin, a->value);
        aprev_rmin = a->rmin_next();
        ++dst; ++a;
      } else {
        *dst = Entry(b->rmin + aprev_rmin,
                     b->rmax + a->rmax_prev(),
                     b->wmin, b->value);
        bprev_rmin = b->rmin_next();
        ++dst; ++b;
      }
    }
    if (a != a_end) {
      RType brmax = (b_end - 1)->rmax;
      do {
        *dst = Entry(a->rmin + bprev_rmin, a->rmax + brmax, a->wmin, a->value);
        ++dst; ++a;
      } while (a != a_end);
    }
    if (b != b_end) {
      RType armax = (a_end - 1)->rmax;
      do {
        *dst = Entry(b->rmin + aprev_rmin, b->rmax + armax, b->wmin, b->value);
        ++dst; ++b;
      } while (b != b_end);
    }
    this->size = dst - data;
    utils::Assert(size <= sa.size + sb.size, "bug in combine");
  }