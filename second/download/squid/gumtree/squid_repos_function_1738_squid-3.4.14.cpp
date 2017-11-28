static void
dnsRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("dns", "Dnsserver Statistics", dnsStats, 0, 1);
}