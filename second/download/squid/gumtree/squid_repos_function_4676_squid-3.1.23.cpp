void
UFSSwapDir::CleanEvent(void *unused)
{
    static int swap_index = 0;
    int i;
    int j = 0;
    int n = 0;
    /*
     * Assert that there are UFS cache_dirs configured, otherwise
     * we should never be called.
     */
    assert(NumberOfUFSDirs);

    if (NULL == UFSDirToGlobalDirMapping) {
        SwapDir *sd;
        /*
         * Initialize the little array that translates UFS cache_dir
         * number into the Config.cacheSwap.swapDirs array index.
         */
        UFSDirToGlobalDirMapping = (int *)xcalloc(NumberOfUFSDirs, sizeof(*UFSDirToGlobalDirMapping));

        for (i = 0, n = 0; i < Config.cacheSwap.n_configured; i++) {
            /* This is bogus, the controller should just clean each instance once */
            sd = dynamic_cast <SwapDir *>(INDEXSD(i));

            if (!UFSSwapDir::IsUFSDir(sd))
                continue;

            UFSSwapDir *usd = dynamic_cast<UFSSwapDir *>(sd);

            assert (usd);

            UFSDirToGlobalDirMapping[n++] = i;

            j += (usd->l1 * usd->l2);
        }

        assert(n == NumberOfUFSDirs);
        /*
         * Start the commonUfsDirClean() swap_index with a random
         * value.  j equals the total number of UFS level 2
         * swap directories
         */
        swap_index = (int) (squid_random() % j);
    }

    /* if the rebuild is finished, start cleaning directories. */
    if (0 == StoreController::store_dirs_rebuilding) {
        n = DirClean(swap_index);
        swap_index++;
    }

    eventAdd("storeDirClean", CleanEvent, NULL,
             15.0 * exp(-0.25 * n), 1);
}