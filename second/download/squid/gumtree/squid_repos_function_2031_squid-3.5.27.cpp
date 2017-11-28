static int
storeDirSelectSwapDirRoundRobin(const StoreEntry * e)
{
    // e->objectLen() is negative at this point when we are still STORE_PENDING
    ssize_t objsize = e->mem_obj->expectedReplySize();
    if (objsize != -1)
        objsize += e->mem_obj->swap_hdr_sz;

    // Increment the first candidate once per selection (not once per
    // iteration) to reduce bias when some disk(s) attract more entries.
    static int firstCandidate = 0;
    if (++firstCandidate >= Config.cacheSwap.n_configured)
        firstCandidate = 0;

    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        const int dirn = (firstCandidate + i) % Config.cacheSwap.n_configured;
        const SwapDir *sd = dynamic_cast<SwapDir*>(INDEXSD(dirn));

        int load = 0;
        if (!sd->canStore(*e, objsize, load))
            continue;

        if (load < 0 || load > 1000) {
            continue;
        }

        return dirn;
    }

    return -1;
}