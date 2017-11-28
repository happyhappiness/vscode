void
StoreEntry::setPrivateKey(const bool shareable)
{
    const cache_key *newkey;

    if (key && EBIT_TEST(flags, KEY_PRIVATE)) {
        // The entry is already private, but it may be still shareable.
        if (!shareable)
            shareableWhenPrivate = false;
        return;
    }

    if (key) {
        setReleaseFlag(); // will markForUnlink(); all caches/workers will know

        // TODO: move into SwapDir::markForUnlink() already called by Root()
        if (swap_filen > -1)
            storeDirSwapLog(this, SWAP_LOG_DEL);

        hashDelete();
    }

    if (mem_obj && mem_obj->hasUris()) {
        mem_obj->id = getKeyCounter();
        newkey = storeKeyPrivate(mem_obj->storeId(), mem_obj->method, mem_obj->id);
    } else {
        newkey = storeKeyPrivate("JUNK", Http::METHOD_NONE, getKeyCounter());
    }

    assert(hash_lookup(store_table, newkey) == NULL);
    EBIT_SET(flags, KEY_PRIVATE);
    shareableWhenPrivate = shareable;
    hashInsert(newkey);
}