Transients::reference(StoreEntry &)
{
    // no replacement policy (but the cache(s) storing the entry may have one)
}

bool
Transients::dereference(StoreEntry &)
{
    // no need to keep e in the global store_table for us; we have our own map
    return false;
}

StoreEntry *
Transients::get(const cache_key *key)
{
    if (!map)
        return NULL;

