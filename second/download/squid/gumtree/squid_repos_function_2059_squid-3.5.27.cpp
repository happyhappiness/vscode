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