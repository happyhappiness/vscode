void
StoreEntry::release()
{
    PROF_start(storeRelease);
    debugs(20, 3, "storeRelease: Releasing: '" << getMD5Text() << "'");
    /* If, for any reason we can't discard this object because of an
     * outstanding request, mark it for pending release */

    if (locked()) {
        expireNow();
        debugs(20, 3, "storeRelease: Only setting RELEASE_REQUEST bit");
        releaseRequest();
        PROF_stop(storeRelease);
        return;
    }

    if (StoreController::store_dirs_rebuilding && swap_filen > -1) {
        setPrivateKey();

        if (mem_obj)
            destroyMemObject();

        if (swap_filen > -1) {
            /*
             * Fake a call to StoreEntry->lock()  When rebuilding is done,
             * we'll just call StoreEntry->unlock() on these.
             */
            lock_count++;
            setReleaseFlag();
            LateReleaseStack.push_back(this);
            PROF_stop(storeRelease);
            return;
        } else {
            destroyStoreEntry(static_cast<hash_link *>(this));
        }
    }

    storeLog(STORE_LOG_RELEASE, this);

    if (swap_filen > -1) {
        unlink();

        if (swap_status == SWAPOUT_DONE)
            if (EBIT_TEST(flags, ENTRY_VALIDATED))
                store()->updateSize(swap_file_sz, -1);

        if (!EBIT_TEST(flags, KEY_PRIVATE))
            storeDirSwapLog(this, SWAP_LOG_DEL);

#if 0
        /* From 2.4. I think we do this in storeUnlink? */
        storeSwapFileNumberSet(this, -1);

#endif

    }

    setMemStatus(NOT_IN_MEMORY);
    destroyStoreEntry(static_cast<hash_link *>(this));
    PROF_stop(storeRelease);
}