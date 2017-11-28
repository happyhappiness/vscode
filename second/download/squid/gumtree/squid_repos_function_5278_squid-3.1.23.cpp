void
netdbInit(void)
{
#if USE_ICMP
    int n;

    netdbRegisterWithCacheManager();

    if (addr_table)
        return;

    n = hashPrime(Config.Netdb.high / 4);

    addr_table = hash_create((HASHCMP *) strcmp, n, hash_string);

    n = hashPrime(3 * Config.Netdb.high / 4);

    host_table = hash_create((HASHCMP *) strcmp, n, hash_string);

    eventAddIsh("netdbSaveState", netdbSaveState, NULL, 3600.0, 1);

    netdbReloadState();

#endif
}