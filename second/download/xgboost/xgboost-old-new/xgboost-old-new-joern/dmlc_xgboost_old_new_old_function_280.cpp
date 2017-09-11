inline void Init(size_t maxn, double eps) {
    nlevel = 1;
    while (true) {
      limit_size = ceil(nlevel / eps) + 1;
      if ((1 << nlevel)  * limit_size >= maxn) break;
      ++nlevel;
    }
    // check invariant
    utils::Assert((1 << nlevel) * limit_size >= maxn, "invalid init parameter");
    utils::Assert(nlevel <= limit_size * eps, "invalid init parameter");
    // lazy reserve the space, if there is only one value, no need to allocate space
    inqueue.queue.resize(1);
    inqueue.qtail = 0;
    data.clear();
    level.clear();
  }