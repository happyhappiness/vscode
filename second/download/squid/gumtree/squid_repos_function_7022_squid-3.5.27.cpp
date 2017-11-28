bool
Ipc::MemMapSlot::sameKey(const cache_key *const aKey) const
{
    return (memcmp(key, aKey, sizeof(key)) == 0);
}