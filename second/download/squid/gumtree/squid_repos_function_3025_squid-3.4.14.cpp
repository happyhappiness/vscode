void
StoreEntry::hashDelete()
{
    hash_remove_link(store_table, this);
    storeKeyFree((const cache_key *)key);
    key = NULL;
}