static void
xprofRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("cpu_profile", "CPU Profiling Stats", xprof_summary, 0, 1);
}