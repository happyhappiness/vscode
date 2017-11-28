StoreEntry *
Store::Disks::get(const cache_key *key)
{
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
                debugs(20, 7, "cache_dir " << idx << " has: " << *e);
                return e;
            }
        }
    }

    debugs(20, 6, "none of " << Config.cacheSwap.n_configured <<
           " cache_dirs have " << storeKeyText(key));
    return nullptr;
}