bool
Ipc::StoreMap::validSlice(const int pos) const
{
    return 0 <= pos && pos < sliceLimit();
}