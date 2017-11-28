void
StoreEntry::hashDelete()
{
    if (key) { // some test cases do not create keys and do not hashInsert()
        hash_remove_link(store_table, this);
        storeKeyFree((const cache_key *)key);
        key = NULL;
    }
}