sfileno
Ipc::StoreMap::nameByKey(const cache_key *const key) const
{
    const uint64_t *const k = reinterpret_cast<const uint64_t *>(key);
    // TODO: use a better hash function
    const int hash = (k[0] + k[1]) % entryLimit();
    return hash;
}