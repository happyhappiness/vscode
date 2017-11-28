bool
Ipc::MemMap::full() const
{
    return entryCount() >= entryLimit();
}