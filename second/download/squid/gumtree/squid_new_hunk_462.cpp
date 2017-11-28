         * Only set the file bit if we know its a valid entry
         * otherwise, set it in the validation procedure
         */

        if ((++validated & 0x3FFFF) == 0)
            /* TODO format the int with with a stream operator */
            debugs(20, DBG_IMPORTANT, "  " << validated << " Entries Validated so far.");
    }

    if (currentSearch->isDone()) {
        debugs(20, DBG_IMPORTANT, "  Completed Validation Procedure");
        debugs(20, DBG_IMPORTANT, "  Validated " << validated << " Entries");
        debugs(20, DBG_IMPORTANT, "  store_swap_size = " << Store::Root().currentSize() / 1024.0 << " KB");
        --StoreController::store_dirs_rebuilding;
        assert(0 == StoreController::store_dirs_rebuilding);

        if (opt_store_doublecheck && store_errors) {
            fatalf("Quitting after finding %d cache index inconsistencies. " \
                   "Removing cache index will force its slow rebuild. " \
