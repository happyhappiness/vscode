    nlevel = 1;
    while (true) {
      limit_size = static_cast<size_t>(ceil(nlevel / eps)) + 1;
	  size_t n = (1UL << nlevel);
      if (n * limit_size >= maxn) break;
      ++nlevel;
    }
    // check invariant
	size_t n = (1UL << nlevel);
    utils::Assert(n * limit_size >= maxn, "invalid init parameter");
    utils::Assert(nlevel <= limit_size * eps, "invalid init parameter");
    // lazy reserve the space, if there is only one value, no need to allocate space
