void
Mem::RegisterWithCacheManager(void)
{
    Mgr::RegisterAction("mem", "Memory Utilization", Mem::Stats, 0, 1);
}