static int
storeDirSelectSwapDirLeastLoad(const StoreEntry * e)
{
    ssize_t objsize;
    ssize_t most_free = 0, cur_free;
    ssize_t least_objsize = -1;
    int least_load = INT_MAX;
    int load;
    int dirn = -1;
    int i;
    RefCount<SwapDir> SD;

    /* Calculate the object size */
    objsize = e->objectLen();

    if (objsize != -1)
        objsize += e->mem_obj->swap_hdr_sz;

    for (i = 0; i < Config.cacheSwap.n_configured; i++) {
        SD = dynamic_cast<SwapDir *>(INDEXSD(i));
        SD->flags.selected = 0;
        load = SD->canStore(*e);

        if (load < 0 || load > 1000) {
            continue;
        }

        if (!SD->objectSizeIsAcceptable(objsize))
            continue;

        if (SD->flags.read_only)
            continue;

        if (SD->cur_size > SD->max_size)
            continue;

        if (load > least_load)
            continue;

        cur_free = SD->max_size - SD->cur_size;

        /* If the load is equal, then look in more details */
        if (load == least_load) {
            /* closest max_objsize fit */

            if (least_objsize != -1)
                if (SD->max_objsize > least_objsize || SD->max_objsize == -1)
                    continue;

            /* most free */
            if (cur_free < most_free)
                continue;
        }

        least_load = load;
        least_objsize = SD->max_objsize;
        most_free = cur_free;
        dirn = i;
    }

    if (dirn >= 0)
        dynamic_cast<SwapDir *>(INDEXSD(dirn))->flags.selected = 1;

    return dirn;
}