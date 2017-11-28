static int
storeDirSelectSwapDirLeastLoad(const StoreEntry * e)
{
    int64_t most_free = 0;
    ssize_t least_objsize = -1;
    int least_load = INT_MAX;
    int load;
    int dirn = -1;
    int i;
    RefCount<SwapDir> SD;

    // e->objectLen() is negative at this point when we are still STORE_PENDING
    ssize_t objsize = e->mem_obj->expectedReplySize();

    if (objsize != -1)
        objsize += e->mem_obj->swap_hdr_sz;

    for (i = 0; i < Config.cacheSwap.n_configured; ++i) {
        SD = dynamic_cast<SwapDir *>(INDEXSD(i));
        SD->flags.selected = false;

        if (!SD->canStore(*e, objsize, load))
            continue;

        if (load < 0 || load > 1000)
            continue;

        if (load > least_load)
            continue;

        const int64_t cur_free = SD->maxSize() - SD->currentSize();

        /* If the load is equal, then look in more details */
        if (load == least_load) {
            /* closest max-size fit */

            if (least_objsize != -1)
                if (SD->maxObjectSize() > least_objsize)
                    continue;

            /* most free */
            if (cur_free < most_free)
                continue;
        }

        least_load = load;
        least_objsize = SD->maxObjectSize();
        most_free = cur_free;
        dirn = i;
    }

    if (dirn >= 0)
        dynamic_cast<SwapDir *>(INDEXSD(dirn))->flags.selected = true;

    return dirn;
}