void
storeRebuildStart(void)
{
    memset(&counts, '\0', sizeof(counts));
    rebuild_start = current_time;
    /*
     * Note: store_dirs_rebuilding is initialized to 1.
     *
     * When we parse the configuration and construct each swap dir,
     * the construction of that raises the rebuild count.
     *
     * This prevents us from trying to write clean logs until we
     * finished rebuilding - including after a reconfiguration that opens an
     * existing swapdir.  The corresponding decrement * occurs in
     * storeCleanup(), when it is finished.
     */
    RebuildProgress = (store_rebuild_progress *)xcalloc(Config.cacheSwap.n_configured,
                      sizeof(store_rebuild_progress));
}