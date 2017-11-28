void
ipcache_init(void)
{
    int n;
    debugs(14, DBG_IMPORTANT, "Initializing IP Cache...");
    memset(&IpcacheStats, '\0', sizeof(IpcacheStats));
    memset(&lru_list, '\0', sizeof(lru_list));
    memset(&static_addrs, '\0', sizeof(ipcache_addrs));

    static_addrs.in_addrs = static_cast<Ip::Address *>(xcalloc(1, sizeof(Ip::Address)));
    static_addrs.in_addrs->setEmpty(); // properly setup the Ip::Address!
    static_addrs.bad_mask = (unsigned char *)xcalloc(1, sizeof(unsigned char));
    ipcache_high = (long) (((float) Config.ipcache.size *
                            (float) Config.ipcache.high) / (float) 100);
    ipcache_low = (long) (((float) Config.ipcache.size *
                           (float) Config.ipcache.low) / (float) 100);
    n = hashPrime(ipcache_high / 4);
    ip_table = hash_create((HASHCMP *) strcmp, n, hash4);

    ipcacheRegisterWithCacheManager();
}