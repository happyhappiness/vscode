void
FwdState::RegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("forward", "Request Forwarding Statistics", fwdStats, 0, 1);
}