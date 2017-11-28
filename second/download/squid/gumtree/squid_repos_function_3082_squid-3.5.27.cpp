int
StoreEntry::checkNegativeHit() const
{
    if (!EBIT_TEST(flags, ENTRY_NEGCACHED))
        return 0;

    if (expires <= squid_curtime)
        return 0;

    if (store_status != STORE_OK)
        return 0;

    return 1;
}