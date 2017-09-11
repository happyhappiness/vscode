    }
    // check invariant
    size_t n = (1UL << nlevel);
    utils::Assert(n * limit_size >= maxn, "invalid init parameter");
    utils::Assert(nlevel <= limit_size * eps, "invalid init parameter");
    // lazy reserve the space, if there is only one value, no need to allocate space
    inqueue.queue.resize(1);
    inqueue.qtail = 0;
