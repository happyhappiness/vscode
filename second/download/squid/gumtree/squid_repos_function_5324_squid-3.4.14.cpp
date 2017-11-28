void
Auth::Basic::Config::registerWithCacheManager(void)
{
    Mgr::RegisterAction("basicauthenticator",
                        "Basic User Authenticator Stats",
                        authenticateBasicStats, 0, 1);
}