inline void Init(size_t maxn, double eps) {
    nlevel = std::max(ceil(maxn * eps), 1.0);
    limit_size = ceil(nlevel / eps);
    // check invariant
    utils::Assert((1 << nlevel)  * limit_size > maxn, "invalid init parameter");
    utils::Assert(nlevel <= limit_size * eps, "invalid init parameter");
    // lazy reserve the space, if there is only one value, no need to allocate space
    inqueue.resize(1);
    qtail = 0;
    data.clear();
    level.clear();
  }