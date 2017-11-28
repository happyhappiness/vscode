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
            ++lock_count;
            setReleaseFlag();
            LateReleaseStack.push_back(this);
        } else {
            destroyStoreEntry(static_cast<hash_link *>(this));
            // "this" is no longer valid
        }

        PROF_stop(storeRelease);
        return;
    }

    storeLog(STORE_LOG_RELEASE, this);

    if (swap_filen > -1) {
        // log before unlink() below clears swap_filen
        if (!EBIT_TEST(flags, KEY_PRIVATE))
            storeDirSwapLog(this, SWAP_LOG_DEL);

        unlink();
    }

    setMemStatus(NOT_IN_MEMORY);
    destroyStoreEntry(static_cast<hash_link *>(this));
    PROF_stop(storeRelease);
}