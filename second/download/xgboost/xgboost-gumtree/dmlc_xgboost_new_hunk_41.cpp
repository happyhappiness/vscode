    RType err_mingap, err_maxgap, err_wgap;
    this->FixError(&err_mingap, &err_maxgap, &err_wgap);
    if (err_mingap > tol || err_maxgap > tol || err_wgap > tol) {
      LOG(INFO) << "mingap=" << err_mingap
                << ", maxgap=" << err_maxgap
                << ", wgap=" << err_wgap;
    }
    CHECK(size <= sa.size + sb.size) << "bug in combine";
  }
  // helper function to print the current content of sketch
  inline void Print() const {
    for (size_t i = 0; i < this->size; ++i) {
      LOG(INFO) << "[" << i << "] rmin=" << data[i].rmin
                << ", rmax=" << data[i].rmax
                << ", wmin=" << data[i].wmin
                << ", v=" << data[i].value;
    }
  }
  // try to fix rounding error
