void
StoreEntry::release(const bool shareable)
{
    PROF_start(storeRelease);
    debugs(20, 3, "releasing " << *this << ' ' << getMD5Text());
    /* If, for any reason we can't discard this object because of an
     * outstanding request, mark it for pending release */

    if (locked()) {
        expireNow();
        debugs(20, 3, "storeRelease: Only setting RELEASE_REQUEST bit");
        releaseRequest(shareable);
        PROF_stop(storeRelease);
        return;
    }

    Store::Root().memoryUnlink(*this);

    if (StoreController::store_dirs_rebuilding && swap_filen > -1) {
        setPrivateKey(shareable);

        if (swap_filen > -1) {
            // lock the entry until rebuilding is done
            lock("storeLateRelease");
            setReleaseFlag();
            LateReleaseStack.push(this);
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

    destroyStoreEntry(static_cast<hash_link *>(this));
    PROF_stop(storeRelease);
}