bool
Transients::dereference(StoreEntry &, bool)
{
    // no need to keep e in the global store_table for us; we have our own map
    return false;
}