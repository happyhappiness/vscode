void
DelayPools::RegisterWithCacheManager(void)
{
    Mgr::RegisterAction("delay", "Delay Pool Levels", Stats, 0, 1);
}