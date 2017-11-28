const Ipc::StoreMap::Anchor *
Ipc::StoreMap::openForReading(const cache_key *const key, sfileno &fileno)
{
    debugs(54, 5, "opening entry with key " << storeKeyText(key)
           << " for reading " << path);
    const int idx = anchorIndexByKey(key);
    if (const Anchor *slot = openForReadingAt(idx)) {
        if (slot->sameKey(key)) {
            fileno = idx;
            return slot; // locked for reading
        }
        slot->lock.unlockShared();
        debugs(54, 7, "closed entry " << idx << " for reading " << path);
    }
    return NULL;
}