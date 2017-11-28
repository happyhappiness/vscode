static void
peerUserHashRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("userhash", "peer userhash information", peerUserHashCachemgr,
                   0, 1);
}