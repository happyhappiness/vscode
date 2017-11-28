void
StoreHashIndex::maintain()
{
    int i;
    /* walk each fs */

    for (i = 0; i < Config.cacheSwap.n_configured; ++i) {
        /* XXX FixMe: This should be done "in parallell" on the different
         * cache_dirs, not one at a time.
         */
        /* call the maintain function .. */
        store(i)->maintain();
    }
}