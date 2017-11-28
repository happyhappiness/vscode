Ipc::StoreMap::Anchor &
Ipc::StoreMap::anchorByKey(const cache_key *const key)
{
    return anchorAt(fileNoByKey(key));
}