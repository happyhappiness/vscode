void
Auth::Negotiate::Config::registerWithCacheManager(void)
{
    Mgr::RegisterAction("negotiateauthenticator",
                        "Negotiate User Authenticator Stats",
                        authenticateNegotiateStats, 0, 1);
}