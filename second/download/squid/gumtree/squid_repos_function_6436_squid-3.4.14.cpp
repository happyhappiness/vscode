Ipc::StoreMap::Slot &
Ipc::StoreMap::slotByKey(const cache_key *const key)
{
    return shared->slots[slotIndexByKey(key)];
}