}

#if USE_CBDATA_DEBUG
void
cbdata::dump(StoreEntry *sentry) const
{
#if WITH_VALGRIND
    void *p = data;
#else
    void *p = (void *)&data;
#endif
    storeAppendPrintf(sentry, "%c%p\t%d\t%d\t%20s:%-5d\n", valid ? ' ' :
                      '!', p, type, locks, file, line);
}
