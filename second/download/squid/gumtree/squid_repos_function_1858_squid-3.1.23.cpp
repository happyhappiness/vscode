static int
storeDirSelectSwapDirRoundRobin(const StoreEntry * e)
{
    static int dirn = 0;
    int i;
    int load;
    RefCount<SwapDir> sd;

    ssize_t objsize = e->objectLen();
    if (objsize != -1)
        objsize += e->mem_obj->swap_hdr_sz;

    for (i = 0; i <= Config.cacheSwap.n_configured; i++) {
        if (++dirn >= Config.cacheSwap.n_configured)
            dirn = 0;

        sd = dynamic_cast<SwapDir *>(INDEXSD(dirn));

        if (sd->flags.read_only)
            continue;

        if (sd->cur_size > sd->max_size)
            continue;

        if (!sd->objectSizeIsAcceptable(objsize))
            continue;

        /* check for error or overload condition */
        load = sd->canStore(*e);

        if (load < 0 || load > 1000) {
            continue;
        }

        return dirn;
    }

    return -1;
}