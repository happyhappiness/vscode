void
Ipc::StoreMap::freeEntryByKey(const cache_key *const key)
{
    debugs(54, 5, "marking entry with key " << storeKeyText(key)
           << " to be freed in " << path);

    const int idx = fileNoByKey(key);
    Anchor &s = anchorAt(idx);
    if (s.lock.lockExclusive()) {
        if (s.sameKey(key))
            freeChain(idx, s, true);
        s.lock.unlockExclusive();
    } else if (s.lock.lockShared()) {
        if (s.sameKey(key))
            s.waitingToBeFreed = true; // mark to free it later
        s.lock.unlockShared();
    } else {
        // we cannot be sure that the entry we found is ours because we do not
        // have a lock on it, but we still check to minimize false deletions
        if (s.sameKey(key))
            s.waitingToBeFreed = true; // mark to free it later
    }
}