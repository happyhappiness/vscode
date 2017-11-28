StoreEntry *
StoreHashIndex::get(const cache_key *key)
{
    PROF_start(storeGet);
    debugs(20, 3, "storeGet: looking up " << storeKeyText(key));
    StoreEntry *p = static_cast<StoreEntry *>(hash_lookup(store_table, key));
    PROF_stop(storeGet);
    return p;
}