        *
         * Step 1: make the store rebuilds use a search internally
        * Step 2: change the search logic to use the four modes described
        *         above
        * Step 3: have the hash index walk the searches itself.
         */
        store(i)->init();
    }
}

uint64_t
StoreHashIndex::maxSize() const
{
    uint64_t result = 0;

    for (int i = 0; i < Config.cacheSwap.n_configured; i++)
        result += store(i)->maxSize();

    return result;
}

uint64_t
StoreHashIndex::minSize() const
{
    uint64_t result = 0;

    for (int i = 0; i < Config.cacheSwap.n_configured; i++)
        result += store(i)->minSize();

    return result;
}

void
StoreHashIndex::stat(StoreEntry & output) const
{
    int i;

    /* Now go through each store, calling its stat routine */

    for (i = 0; i < Config.cacheSwap.n_configured; i++) {
        storeAppendPrintf(&output, "\n");
        store(i)->stat(output);
    }
}

void
StoreHashIndex::reference(StoreEntry&)
{}

void
StoreHashIndex::dereference(StoreEntry&)
{}

void
StoreHashIndex::maintain()
{
    int i;
    /* walk each fs */

    for (i = 0; i < Config.cacheSwap.n_configured; i++) {
        /* XXX FixMe: This should be done "in parallell" on the different
         * cache_dirs, not one at a time.
         */
        /* call the maintain function .. */
        store(i)->maintain();
    }
}

void
StoreHashIndex::updateSize(int64_t, int)
{}

void
StoreHashIndex::sync()
{
    for (int i = 0; i < Config.cacheSwap.n_configured; ++i)
        store(i)->sync();
}

