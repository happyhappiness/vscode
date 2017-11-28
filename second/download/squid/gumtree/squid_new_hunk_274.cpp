
            if (j > 100)
                fatal ("too much io\n");
        }
    } while (j > 0);

    ++ndir;

    return result;
}

void
StoreHashIndex::create()
{
    if (Config.cacheSwap.n_configured == 0) {
        debugs(0, DBG_PARSE_NOTE(DBG_CRITICAL), "No cache_dir stores are configured.");
    }

    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        if (dir(i).active())
            store(i)->create();
    }
}

/* Lookup an object in the cache.
 * return just a reference to object, don't start swapping in yet. */
StoreEntry *
StoreHashIndex::get(const cache_key *key)
{
    PROF_start(storeGet);
    debugs(20, 3, "storeGet: looking up " << storeKeyText(key));
    StoreEntry *p = static_cast<StoreEntry *>(hash_lookup(store_table, key));
    PROF_stop(storeGet);
    return p;
}

void
StoreHashIndex::get(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
{
    fatal("not implemented");
}

void
StoreHashIndex::init()
{
    if (Config.Store.objectsPerBucket <= 0)
        fatal("'store_objects_per_bucket' should be larger than 0.");

    if (Config.Store.avgObjectSize <= 0)
        fatal("'store_avg_object_size' should be larger than 0.");

    /* Calculate size of hash table (maximum currently 64k buckets).  */
    /* this is very bogus, its specific to the any Store maintaining an
     * in-core index, not global */
    size_t buckets = (Store::Root().maxSize() + Config.memMaxSize) / Config.Store.avgObjectSize;
    debugs(20, 1, "Swap maxSize " << (Store::Root().maxSize() >> 10) <<
           " + " << ( Config.memMaxSize >> 10) << " KB, estimated " << buckets << " objects");
    buckets /= Config.Store.objectsPerBucket;
    debugs(20, 1, "Target number of buckets: " << buckets);
    /* ideally the full scan period should be configurable, for the
     * moment it remains at approximately 24 hours.  */
    store_hash_buckets = storeKeyHashBuckets(buckets);
    debugs(20, 1, "Using " << store_hash_buckets << " Store buckets");
    debugs(20, 1, "Max Mem  size: " << ( Config.memMaxSize >> 10) << " KB" <<
           (Config.memShared ? " [shared]" : ""));
    debugs(20, 1, "Max Swap size: " << (Store::Root().maxSize() >> 10) << " KB");

    store_table = hash_create(storeKeyHashCmp,
                              store_hash_buckets, storeKeyHashHash);

    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        /* this starts a search of the store dirs, loading their
         * index. under the new Store api this should be
         * driven by the StoreHashIndex, not by each store.
        *
        * That is, the HashIndex should perform a search of each dir it is
        * indexing to do the hash insertions. The search is then able to
