static int
storeDirSelectSwapDirRoundRobin(const StoreEntry * e)
{
    static int dirn = 0;
    int i;
    int load;
    RefCount<SwapDir> sd;

    // e->objectLen() is negative at this point when we are still STORE_PENDING
    ssize_t objsize = e->mem_obj->expectedReplySize();
    if (objsize != -1)
        objsize += e->mem_obj->swap_hdr_sz;

    for (i = 0; i < Config.cacheSwap.n_configured; ++i) {
        if (++dirn >= Config.cacheSwap.n_configured)
            dirn = 0;

        sd = dynamic_cast<SwapDir *>(INDEXSD(dirn));

        if (!sd->canStore(*e, objsize, load))
            continue;

        if (load < 0 || load > 1000) {
            continue;
        }

        return dirn;
    }

    return -1;
}