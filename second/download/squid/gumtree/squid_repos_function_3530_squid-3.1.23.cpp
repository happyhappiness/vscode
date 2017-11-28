static void
storeCleanup(void *datanotused)
{
    static int store_errors = 0;
    static StoreSearchPointer currentSearch;
    static int validated = 0;

    if (currentSearch == NULL || currentSearch->isDone())
        currentSearch = Store::Root().search(NULL, NULL);

    size_t statCount = 500;

    while (statCount-- && !currentSearch->isDone() && currentSearch->next()) {
        ++validated;
        StoreEntry *e;

        e = currentSearch->currentItem();

        if (EBIT_TEST(e->flags, ENTRY_VALIDATED))
            continue;

        /*
         * Calling StoreEntry->release() has no effect because we're
         * still in 'store_rebuilding' state
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
        eventAdd("storeCleanup", storeCleanup, NULL, 0.0, 1);
}