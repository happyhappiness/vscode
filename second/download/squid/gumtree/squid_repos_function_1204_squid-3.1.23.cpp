void
Mem::RegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->registerAction("mem", "Memory Utilization",
            Mem::Stats, 0, 1);
}