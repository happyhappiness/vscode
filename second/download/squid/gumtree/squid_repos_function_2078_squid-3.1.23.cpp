static void
xprofRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("cpu_profile", "CPU Profiling Stats", xprof_summary, 0, 1);
}