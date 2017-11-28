bool
storeRebuildKeepEntry(const StoreEntry &tmpe, const cache_key *key, StoreRebuildData &stats)
{
    /* this needs to become
     * 1) unpack url
     * 2) make synthetic request with headers ?? or otherwise search
     * for a matching object in the store
     * TODO FIXME change to new async api
     * TODO FIXME I think there is a race condition here with the
     * async api :
     * store A reads in object foo, searchs for it, and finds nothing.
     * store B reads in object foo, searchs for it, finds nothing.
     * store A gets called back with nothing, so registers the object
     * store B gets called back with nothing, so registers the object,
     * which will conflict when the in core index gets around to scanning
     * store B.
     *
     * this suggests that rather than searching for duplicates, the
     * index rebuild should just assume its the most recent accurate
     * store entry and whoever indexes the stores handles duplicates.
     */
    if (StoreEntry *e = Store::Root().get(key)) {

        if (e->lastref >= tmpe.lastref) {
            /* key already exists, old entry is newer */
            /* keep old, ignore new */
            ++stats.dupcount;

            // For some stores, get() creates/unpacks a store entry. Signal
            // such stores that we will no longer use the get() result:
            e->lock();
            e->unlock();

            return false;
        } else {
            /* URL already exists, this swapfile not being used */
            /* junk old, load new */
            e->release();	/* release old entry */
            ++stats.dupcount;
        }
    }

    return true;
}