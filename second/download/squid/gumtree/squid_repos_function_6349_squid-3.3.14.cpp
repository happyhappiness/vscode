int
Ipc::StoreMap::slotIndexByKey(const cache_key *const key) const
{
    const uint64_t *const k = reinterpret_cast<const uint64_t *>(key);
    // TODO: use a better hash function
    return (k[0] + k[1]) % shared->limit;
}