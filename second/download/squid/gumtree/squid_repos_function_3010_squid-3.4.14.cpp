void
StoreEntry::cacheNegatively()
{
    /* This object may be negatively cached */
    negativeCache();

    if (EBIT_TEST(flags, ENTRY_CACHABLE))
        setPublicKey();
}