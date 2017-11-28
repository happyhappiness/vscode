void
MemStore::reference(StoreEntry &)
{
}

bool
MemStore::dereference(StoreEntry &, bool)
{
    // no need to keep e in the global store_table for us; we have our own map
    return false;
}

int
MemStore::callback()
{
    return 0;
}

StoreSearch *
MemStore::search(String const, HttpRequest *)
{
    fatal("not implemented");
    return NULL;
}

StoreEntry *
MemStore::get(const cache_key *key)
{
    if (!map)
        return NULL;

