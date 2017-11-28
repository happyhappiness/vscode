void
StoreController::get(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
{
    fatal("not implemented");
}

/// updates the collapsed entry with the corresponding on-disk entry, if any
/// In other words, the SwapDir::anchorCollapsed() API applied to all disks.
bool
StoreController::anchorCollapsedOnDisk(StoreEntry &collapsed, bool &inSync)
{
    // TODO: move this loop to StoreHashIndex, just like the one in get().
    if (const int cacheDirs = Config.cacheSwap.n_configured) {
        // ask each cache_dir until the entry is found; use static starting
        // point to avoid asking the same subset of disks more often
        // TODO: coordinate with put() to be able to guess the right disk often
        static int idx = 0;
        for (int n = 0; n < cacheDirs; ++n) {
            idx = (idx + 1) % cacheDirs;
            SwapDir *sd = dynamic_cast<SwapDir*>(INDEXSD(idx));
            if (!sd->active())
                continue;

            if (sd->anchorCollapsed(collapsed, inSync)) {
                debugs(20, 3, "cache_dir " << idx << " anchors " << collapsed);
                return true;
            }
        }
    }

    debugs(20, 4, "none of " << Config.cacheSwap.n_configured <<
           " cache_dirs have " << collapsed);
    return false;
}

void StoreController::markForUnlink(StoreEntry &e)
{
    if (transients && e.mem_obj && e.mem_obj->xitTable.index >= 0)
        transients->markForUnlink(e);
    if (memStore && e.mem_obj && e.mem_obj->memCache.index >= 0)
        memStore->markForUnlink(e);
    if (e.swap_filen >= 0)
        e.store()->markForUnlink(e);
}

// move this into [non-shared] memory cache class when we have one
/// whether e should be kept in local RAM for possible future caching
bool
StoreController::keepForLocalMemoryCache(StoreEntry &e) const
{
    if (!e.memoryCachable())
        return false;

    // does the current and expected size obey memory caching limits?
    assert(e.mem_obj);
