void
StoreEntry::setPrivateKey()
{
    const cache_key *newkey;

    if (key && EBIT_TEST(flags, KEY_PRIVATE))
        return;                 /* is already private */

    if (key) {
        if (swap_filen > -1)
            storeDirSwapLog(this, SWAP_LOG_DEL);

        hashDelete();
    }

    if (mem_obj != NULL) {
        mem_obj->id = getKeyCounter();
        newkey = storeKeyPrivate(mem_obj->url, mem_obj->method, mem_obj->id);
    } else {
        newkey = storeKeyPrivate("JUNK", Http::METHOD_NONE, getKeyCounter());
    }

    assert(hash_lookup(store_table, newkey) == NULL);
    EBIT_SET(flags, KEY_PRIVATE);
    hashInsert(newkey);
}