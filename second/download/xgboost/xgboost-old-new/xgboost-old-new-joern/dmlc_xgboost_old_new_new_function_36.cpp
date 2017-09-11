inline void Init(size_t maxn, double eps) {
    nlevel = 1;
    while (true) {
      limit_size = static_cast<size_t>(ceil(nlevel / eps)) + 1;
      size_t n = (1UL << nlevel);
      if (n * limit_size >= maxn) break;
      ++nlevel;
    }
    // check invariant
    size_t n = (1UL << nlevel);
    CHECK(n * limit_size >= maxn) << "invalid init parameter";
    CHECK(nlevel <= limit_size * eps) << "invalid init parameter";
    // lazy reserve the space, if there is only one value, no need to allocate space
    inqueue.queue.resize(1);
    inqueue.qtail = 0;
    data.clear();
    level.clear();
  }