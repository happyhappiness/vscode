    RType err_mingap, err_maxgap, err_wgap;
    this->FixError(&err_mingap, &err_maxgap, &err_wgap);
    if (err_mingap > tol || err_maxgap > tol || err_wgap > tol) {
      utils::Printf("INFO: mingap=%g, maxgap=%g, wgap=%g\n",
                    err_mingap, err_maxgap, err_wgap);
    }

    utils::Assert(size <= sa.size + sb.size, "bug in combine");
  }
  // helper function to print the current content of sketch
  inline void Print() const {
    for (size_t i = 0; i < this->size; ++i) {
      utils::Printf("[%lu] rmin=%g, rmax=%g, wmin=%g, v=%g\n",
                    i, data[i].rmin, data[i].rmax,
                    data[i].wmin, data[i].value);
    }
  }
  // try to fix rounding error
