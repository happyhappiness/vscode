StoreEntry *
StoreController::get(const cache_key *key)
{
    if (StoreEntry *e = find(key)) {
        // this is not very precise: some get()s are not initiated by clients
        e->touch();
        return e;
    }
    return NULL;
}