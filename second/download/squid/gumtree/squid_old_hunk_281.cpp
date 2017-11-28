         */
        if (e->swap_filen < 0)
            continue;

        if (opt_store_doublecheck)
            if (storeCleanupDoubleCheck(e))
                store_errors++;

        EBIT_SET(e->flags, ENTRY_VALIDATED);

        /*
         * Only set the file bit if we know its a valid entry
         * otherwise, set it in the validation procedure
         */
        e->store()->updateSize(e->swap_file_sz, 1);

        if ((++validated & 0x3FFFF) == 0)
            /* TODO format the int with with a stream operator */
            debugs(20, 1, "  " << validated << " Entries Validated so far.");
    }

    if (currentSearch->isDone()) {
        debugs(20, 1, "  Completed Validation Procedure");
        debugs(20, 1, "  Validated " << validated << " Entries");
        debugs(20, 1, "  store_swap_size = " << store_swap_size);
        StoreController::store_dirs_rebuilding--;
        assert(0 == StoreController::store_dirs_rebuilding);

        if (opt_store_doublecheck)
            assert(store_errors == 0);

        if (store_digest)
            storeDigestNoteStoreReady();

        currentSearch = NULL;
    } else
