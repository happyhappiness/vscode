inline void CheckValid(RType eps) const {
    for (size_t i = 0; i < size; ++i) {
      data[i].CheckValid(eps);
      if (i != 0) {
        utils::Assert(data[i].rmin >= data[i - 1].rmin + data[i - 1].wmin, "rmin range constraint");
        utils::Assert(data[i].rmax >= data[i - 1].rmax + data[i].wmin, "rmax range constraint");
      }
    }
  }