void
StoreEntry::hashInsert(const cache_key * someKey)
{
    debugs(20, 3, "StoreEntry::hashInsert: Inserting Entry " << *this << " key '" << storeKeyText(someKey) << "'");
    key = storeKeyDup(someKey);
    hash_join(store_table, this);
}