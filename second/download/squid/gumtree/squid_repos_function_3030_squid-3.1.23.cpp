static void
peerSourceHashRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("sourcehash", "peer sourcehash information",
                   peerSourceHashCachemgr, 0, 1);
}