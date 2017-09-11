inline static void ReduceInner(const void *src_, void *dst_, int len_) {
    const int *psrc = reinterpret_cast<const int*>(src_);
    int *pdst = reinterpret_cast<int*>(dst_);
    DType tdst, tsrc;
    utils::Assert(len_ % kUnit == 0, "length not divide by size");
    for (size_t i = 0; i < len_; i += kUnit) {
      // use memcpy to avoid alignment issue
      std::memcpy(&tdst, pdst + i, sizeof(tdst));
      std::memcpy(&tsrc, psrc + i, sizeof(tsrc));
      tdst.Reduce(tsrc);
      std::memcpy(pdst + i, &tdst, sizeof(tdst));      
    }
  }