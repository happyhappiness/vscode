bool
Ipc::StoreMap::validEntry(const int pos) const
{
    return 0 <= pos && pos < entryLimit();
}