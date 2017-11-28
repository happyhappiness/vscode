void
PconnPool::dumpHash(StoreEntry *e) const
{
    hash_table *hid = table;
    hash_first(hid);

    int i = 0;
    for (hash_link *walker = hash_next(hid); walker; walker = hash_next(hid)) {
        storeAppendPrintf(e, "\t item %d:\t%s\n", i, (char *)(walker->key));
        ++i;
    }
}