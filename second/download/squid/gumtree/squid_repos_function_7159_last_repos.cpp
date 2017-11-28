sfileno
Ipc::StoreMap::fileNoByKey(const cache_key *const key) const
{
    const int name = nameByKey(key);
    return fileNoByName(name);
}