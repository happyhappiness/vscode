StoreEntry *
StoreController::find(const cache_key *key)
{
    if (StoreEntry *e = swapDir->get(key)) {
        // TODO: ignore and maybe handleIdleEntry() unlocked intransit entries
        // because their backing store slot may be gone already.
        debugs(20, 3, HERE << "got in-transit entry: " << *e);
        return e;
    }

    // Must search transients before caches because we must sync those we find.
    if (transients) {
        if (StoreEntry *e = transients->get(key)) {
            debugs(20, 3, "got shared in-transit entry: " << *e);
            bool inSync = false;
            const bool found = anchorCollapsed(*e, inSync);
            if (!found || inSync)
                return e;
            assert(!e->locked()); // ensure release will destroyStoreEntry()
            e->release(); // do not let others into the same trap
            return NULL;
        }
    }

    if (memStore) {
        if (StoreEntry *e = memStore->get(key)) {
            debugs(20, 3, HERE << "got mem-cached entry: " << *e);
            return e;
        }
    }

    // TODO: this disk iteration is misplaced; move to StoreHashIndex when
    // the global store_table is no longer used for in-transit objects.
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

            if (StoreEntry *e = sd->get(key)) {
                debugs(20, 3, HERE << "cache_dir " << idx <<
                       " got cached entry: " << *e);
                return e;
            }
        }
    }

    debugs(20, 4, HERE << "none of " << Config.cacheSwap.n_configured <<
           " cache_dirs have " << storeKeyText(key));
    return NULL;
}