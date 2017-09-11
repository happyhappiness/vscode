inline void SetCombine(const WQSummary &sa,
                         const WQSummary &sb) {
	utils::Check(sa.Check("BeforeCombine A"), "Check Left error");
    utils::Check(sb.Check("BeforeCombine B"), "Check right error");
    if (sa.size == 0) {
      this->CopyFrom(sb); return;
    }
    if (sb.size == 0) {
      this->CopyFrom(sa); return;
    }
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
	const RType tol = 10;
    RType err_mingap, err_maxgap, err_wgap;
    this->FixError(&err_mingap, &err_maxgap, &err_wgap);
    if (err_mingap > tol || err_maxgap > tol || err_wgap > tol) {
      utils::Printf("INFO: mingap=%g, maxgap=%g, wgap=%g\n",
                    err_mingap, err_maxgap, err_wgap);
    }

    if (!this->Check("AfterCombine")) {
      utils::Printf("-----Left-----\n");
      sa.Print();
      utils::Printf("-----Right-----\n");
      sb.Print();
      utils::Error("Error after combine\n");
    }
    utils::Assert(size <= sa.size + sb.size, "bug in combine");
  }