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

    if (Store::Controller::store_dirs_rebuilding && swap_filen > -1) {
        /* TODO: Teach disk stores to handle releases during rebuild instead. */

        Store::Root().memoryUnlink(*this);

        setPrivateKey(shareable);

        // lock the entry until rebuilding is done
        lock("storeLateRelease");
        setReleaseFlag();
        LateReleaseStack.push(this);
        return;
    }

    storeLog(STORE_LOG_RELEASE, this);
    if (swap_filen > -1 && !EBIT_TEST(flags, KEY_PRIVATE)) {
        // log before unlink() below clears swap_filen
        storeDirSwapLog(this, SWAP_LOG_DEL);
    }

    Store::Root().unlink(*this);
    destroyStoreEntry(static_cast<hash_link *>(this));
    PROF_stop(storeRelease);
}