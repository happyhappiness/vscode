uint64_t
MemStore::currentSize() const
{
    return Ipc::Mem::PageLevel(Ipc::Mem::PageId::cachePage) *
           Ipc::Mem::PageSize();
}