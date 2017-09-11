  };
  /*! 
   * \brief intialize the quantile sketch, given the performance specification
   * \param maxn maximum number of data points can be encountered
   * \param eps accuracy level of summary
   */
  inline void Init(RType maxn, double eps) {
    nlevel = 0;
    size_t b = std::max(floor(log2(eps * maxn) / eps), 8.0);
    // check for small n case
    while (b < maxn) {
      nlevel = ceil(log2(maxn / b)) + 1;
      if (nlevel < eps * b) break;
      ++b;
    }
    nlevel += 1;
    limit_size = (b + 1) / 2 + 1;
    // lazy reserve the space, if there is only one value, no need to allocate space
    inqueue.resize(1);
    qtail = 0;
