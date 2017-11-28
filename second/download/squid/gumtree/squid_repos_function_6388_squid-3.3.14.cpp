size_t
Ipc::Mem::PagePool::level(const int purpose) const
{
    Must(0 <= purpose && purpose < PageId::maxPurpose);
    return theLevels[purpose];
}