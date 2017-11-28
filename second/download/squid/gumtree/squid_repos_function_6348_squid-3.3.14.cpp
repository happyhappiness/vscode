bool
Ipc::StoreMap::valid(const int pos) const
{
    return 0 <= pos && pos < entryLimit();
}