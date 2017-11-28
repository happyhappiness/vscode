static void
peerSourceHashRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("sourcehash", "peer sourcehash information",
                        peerSourceHashCachemgr, 0, 1);
}