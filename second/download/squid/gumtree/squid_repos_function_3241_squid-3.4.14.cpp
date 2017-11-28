int64_t
MemStore::maxObjectSize() const
{
    return Ipc::Mem::PageSize();
}