void
StoreEntry::forcePublicKey(const cache_key *newkey)
{
    if (StoreEntry *e2 = (StoreEntry *)hash_lookup(store_table, newkey)) {
        assert(e2 != this);
        debugs(20, 3, "Making old " << *e2 << " private.");

        // TODO: check whether there is any sense in keeping old entry
        // shareable here. Leaving it non-shareable for now.
        e2->setPrivateKey(false);
        e2->release(false);
    }

    if (key)
        hashDelete();

    clearPrivate();

    hashInsert(newkey);

    if (swap_filen > -1)
        storeDirSwapLog(this, SWAP_LOG_ADD);
}