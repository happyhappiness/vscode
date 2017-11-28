Ipc::MemMap::Slot &
Ipc::MemMap::slotByKey(const cache_key *const key)
{
    return shared->slots[slotIndexByKey(key)];
}