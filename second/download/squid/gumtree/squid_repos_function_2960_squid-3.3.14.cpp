void
StoreEntry::makePublic()
{
    /* This object can be cached for a long time */

    if (EBIT_TEST(flags, ENTRY_CACHABLE))
        setPublicKey();
}