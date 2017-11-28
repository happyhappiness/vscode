void
Ipc::StoreMapSlot::setKey(const cache_key *const aKey)
{
    memcpy(key, aKey, sizeof(key));
}