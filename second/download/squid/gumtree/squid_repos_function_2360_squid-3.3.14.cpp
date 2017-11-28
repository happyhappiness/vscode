void
redirectRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("redirector", "URL Redirector Stats", redirectStats, 0, 1);
}