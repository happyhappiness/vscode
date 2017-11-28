bool
Ipc::StoreMapAnchor::sameKey(const cache_key *const aKey) const
{
    const uint64_t *const k = reinterpret_cast<const uint64_t *>(aKey);
    return k[0] == key[0] && k[1] == key[1];
}