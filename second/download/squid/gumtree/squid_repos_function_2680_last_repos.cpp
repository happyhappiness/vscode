void
fqdncache_init(void)
{
    int n;

    fqdncacheRegisterWithCacheManager();

    if (fqdn_table)
        return;

    debugs(35, 3, "Initializing FQDN Cache...");

    memset(&FqdncacheStats, '\0', sizeof(FqdncacheStats));

    memset(&lru_list, '\0', sizeof(lru_list));

    fqdncache_high = (long) (((float) Config.fqdncache.size *
                              (float) FQDN_HIGH_WATER) / (float) 100);

    fqdncache_low = (long) (((float) Config.fqdncache.size *
                             (float) FQDN_LOW_WATER) / (float) 100);

    n = hashPrime(fqdncache_high / 4);

    fqdn_table = hash_create((HASHCMP *) strcmp, n, hash4);
}