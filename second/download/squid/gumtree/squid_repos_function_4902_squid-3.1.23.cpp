void
AuthBasicConfig::registerWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("basicauthenticator",
                   "Basic User Authenticator Stats",
                   authenticateBasicStats, 0, 1);
}