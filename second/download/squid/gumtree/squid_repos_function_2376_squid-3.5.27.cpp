void
FwdState::RegisterWithCacheManager(void)
{
    Mgr::RegisterAction("forward", "Request Forwarding Statistics", fwdStats, 0, 1);
}