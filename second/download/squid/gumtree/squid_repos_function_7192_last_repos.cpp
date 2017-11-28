bool
Ipc::MemMap::valid(const int pos) const
{
    return 0 <= pos && pos < entryLimit();
}