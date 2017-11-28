Transients::reference(StoreEntry &)
{
    // no replacement policy (but the cache(s) storing the entry may have one)
}

bool
Transients::dereference(StoreEntry &, bool)
{
    // no need to keep e in the global store_table for us; we have our own map
    return false;
}

int
Transients::callback()
{
    return 0;
}

StoreSearch *
Transients::search(String const, HttpRequest *)
{
    fatal("not implemented");
    return NULL;
}

StoreEntry *
Transients::get(const cache_key *key)
{
    if (!map)
        return NULL;

