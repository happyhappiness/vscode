
            if (j > 100)
                fatal ("too much io\n");
        }
    } while (j > 0);

    ndir++;

    return result;
}

void
StoreHashIndex::create()
{
    for (int i = 0; i < Config.cacheSwap.n_configured; i++)
        store(i)->create();
}

/* Lookup an object in the cache.
 * return just a reference to object, don't start swapping in yet. */
StoreEntry *

StoreHashIndex::get
(const cache_key *key)
{
    PROF_start(storeGet);
    debugs(20, 3, "storeGet: looking up " << storeKeyText(key));
    StoreEntry *p = static_cast<StoreEntry *>(hash_lookup(store_table, key));
    PROF_stop(storeGet);
    return p;
}

void

StoreHashIndex::get
(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
{
    fatal("not implemented");
}

void
StoreHashIndex::init()
{
    /* Calculate size of hash table (maximum currently 64k buckets).  */
    /* this is very bogus, its specific to the any Store maintaining an
     * in-core index, not global */
    size_t buckets = (Store::Root().maxSize() + ( Config.memMaxSize >> 10)) / Config.Store.avgObjectSize;
    debugs(20, 1, "Swap maxSize " << Store::Root().maxSize() <<
           " + " << ( Config.memMaxSize >> 10) << " KB, estimated " << buckets << " objects");
    buckets /= Config.Store.objectsPerBucket;
    debugs(20, 1, "Target number of buckets: " << buckets);
    /* ideally the full scan period should be configurable, for the
     * moment it remains at approximately 24 hours.  */
    store_hash_buckets = storeKeyHashBuckets(buckets);
    debugs(20, 1, "Using " << store_hash_buckets << " Store buckets");
    debugs(20, 1, "Max Mem  size: " << ( Config.memMaxSize >> 10) << " KB");
    debugs(20, 1, "Max Swap size: " << Store::Root().maxSize() << " KB");

    store_table = hash_create(storeKeyHashCmp,
                              store_hash_buckets, storeKeyHashHash);

    for (int i = 0; i < Config.cacheSwap.n_configured; i++) {
        /* this starts a search of the store dirs, loading their
         * index. under the new Store api this should be
         * driven by the StoreHashIndex, not by each store.
        *
        * That is, the HashIndex should perform a search of each dir it is
        * indexing to do the hash insertions. The search is then able to
