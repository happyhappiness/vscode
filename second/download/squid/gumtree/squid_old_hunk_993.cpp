}

#if USE_CBDATA_DEBUG
void
cbdata::dump(StoreEntry *sentry) const
{
#if HASHED_CBDATA
    void *p = (void *)hash.key;
#else
    void *p = (void *)&data;
#endif
    storeAppendPrintf(sentry, "%c%p\t%d\t%d\t%20s:%-5d\n", valid ? ' ' :
                      '!', p, type, locks, file, line);
}
