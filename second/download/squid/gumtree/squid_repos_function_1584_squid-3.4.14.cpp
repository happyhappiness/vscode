void
DelayPools::Init()
{
    LastUpdate = getCurrentTime();
    RegisterWithCacheManager();
}