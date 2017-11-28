int
Ipc::MemMap::slotIndexByKey(const cache_key *const key) const
{
    const unsigned char *k = reinterpret_cast<const unsigned char *>(key);
    return hash_key(k, MEMMAP_SLOT_KEY_SIZE, shared->limit);
}