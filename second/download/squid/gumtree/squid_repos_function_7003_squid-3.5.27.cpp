Ipc::MemMap::Slot *
Ipc::MemMap::openForWriting(const cache_key *const key, sfileno &fileno)
{
    debugs(54, 5, "trying to open slot for key " << storeKeyText(key)
           << " for writing in map [" << path << ']');
    const int idx = slotIndexByKey(key);

    if (Slot *slot = openForWritingAt(idx)) {
        fileno = idx;
        return slot;
    }

    return NULL;
}