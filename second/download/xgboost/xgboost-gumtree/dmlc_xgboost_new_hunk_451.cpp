   * \param reducer the reducer function
   */
  inline void AllReduce(DType *sendrecvbuf, size_t count) {
    handle.AllReduce(sendrecvbuf, kUnit, count);
  }

 private:
  // unit size 
  static const size_t kUnit = sizeof(DType) / sizeof(int);
  // inner implementation of reducer
  inline static void ReduceInner(const void *src_, void *dst_, int len_, const MPI::Datatype &dtype) {
    const int *psrc = reinterpret_cast<const int*>(src_);
    int *pdst = reinterpret_cast<int*>(dst_);
    DType tdst, tsrc;
    for (size_t i = 0; i < len_; ++i) {
      // use memcpy to avoid alignment issue
      std::memcpy(&tdst, pdst + i * kUnit, sizeof(tdst));
      std::memcpy(&tsrc, psrc + i * kUnit, sizeof(tsrc));
      tdst.Reduce(tsrc);
      std::memcpy(pdst + i * kUnit, &tdst, sizeof(tdst));      
    }
  }
  // function handle
