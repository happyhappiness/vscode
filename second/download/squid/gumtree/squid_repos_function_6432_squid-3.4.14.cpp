bool
Ipc::StoreMap::full() const
{
    return entryCount() >= entryLimit();
}