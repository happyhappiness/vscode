static int
storeDirSelectSwapDirLeastLoad(const StoreEntry * e)
{
    int64_t most_free = 0;
    int64_t best_objsize = -1;
    int least_load = INT_MAX;
    int load;
    int dirn = -1;
    int i;
    RefCount<SwapDir> SD;

    const int64_t objsize = objectSizeForDirSelection(*e);

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
            /* best max-size fit */
            if (best_objsize != -1) {
                // cache_dir with the smallest max-size gets the known-size object
                // cache_dir with the largest max-size gets the unknown-size object
                if ((objsize != -1 && SD->maxObjectSize() > best_objsize) ||
                        (objsize == -1 && SD->maxObjectSize() < best_objsize))
                    continue;
            }

            /* most free */
            if (cur_free < most_free)
                continue;
        }

        least_load = load;
        best_objsize = SD->maxObjectSize();
        most_free = cur_free;
        dirn = i;
    }

    if (dirn >= 0)
        dynamic_cast<SwapDir *>(INDEXSD(dirn))->flags.selected = true;

    return dirn;
}