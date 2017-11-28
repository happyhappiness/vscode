void
MemStore::reference(StoreEntry &)
{
}

bool
MemStore::dereference(StoreEntry &)
{
    // no need to keep e in the global store_table for us; we have our own map
    return false;
}

StoreEntry *
MemStore::get(const cache_key *key)
{
    if (!map)
        return NULL;

