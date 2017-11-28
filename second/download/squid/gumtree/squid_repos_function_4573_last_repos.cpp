StoreEntry *
Store::Controller::find(const cache_key *key)
{
    debugs(20, 3, storeKeyText(key));

    if (StoreEntry *e = static_cast<StoreEntry*>(hash_lookup(store_table, key))) {
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

    if (swapDir) {
        if (StoreEntry *e = swapDir->get(key)) {
            debugs(20, 3, "got disk-cached entry: " << *e);
            return e;
        }
    }

    debugs(20, 4, "cannot locate " << storeKeyText(key));
    return nullptr;
}