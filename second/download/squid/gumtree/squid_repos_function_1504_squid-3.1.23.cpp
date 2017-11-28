void
DelayPools::RegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("delay", "Delay Pool Levels", Stats, 0, 1);
}