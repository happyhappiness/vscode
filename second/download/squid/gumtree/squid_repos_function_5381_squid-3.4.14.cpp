void
Auth::Digest::Config::registerWithCacheManager(void)
{
    Mgr::RegisterAction("digestauthenticator",
                        "Digest User Authenticator Stats",
                        authenticateDigestStats, 0, 1);
}