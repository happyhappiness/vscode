const Ipc::StoreMap::Slot *
Ipc::StoreMap::openForReading(const cache_key *const key, sfileno &fileno)
{
    debugs(54, 5, HERE << " trying to open slot for key " << storeKeyText(key)
           << " for reading in map [" << path << ']');
    const int idx = slotIndexByKey(key);
    if (const Slot *slot = openForReadingAt(idx)) {
        if (slot->sameKey(key)) {
            fileno = idx;
            debugs(54, 5, HERE << " opened slot at " << fileno << " for key "
                   << storeKeyText(key) << " for reading in map [" << path <<
                   ']');
            return slot; // locked for reading
        }
        slot->lock.unlockShared();
    }
    debugs(54, 5, HERE << " failed to open slot for key " << storeKeyText(key)
           << " for reading in map [" << path << ']');
    return NULL;
}