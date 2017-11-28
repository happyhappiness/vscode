bool
MemStore::willFit(int64_t need) const
{
    return need <= static_cast<int64_t>(Ipc::Mem::PageSize());
}