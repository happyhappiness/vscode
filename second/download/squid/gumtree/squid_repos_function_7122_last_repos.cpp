Ipc::StoreMap::Anchor *
Ipc::StoreMap::openForWriting(const cache_key *const key, sfileno &fileno)
{
    debugs(54, 5, "opening entry with key " << storeKeyText(key)
           << " for writing " << path);
    const int idx = fileNoByKey(key);

    if (Anchor *anchor = openForWritingAt(idx)) {
        fileno = idx;
        return anchor;
    }

    return NULL;
}