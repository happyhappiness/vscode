static void
dnsRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("dns", "Dnsserver Statistics", dnsStats, 0, 1);
}