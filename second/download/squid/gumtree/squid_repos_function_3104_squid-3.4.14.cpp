static void
peerUserHashRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("userhash", "peer userhash information", peerUserHashCachemgr,
                        0, 1);
}