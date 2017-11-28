void
AuthNegotiateConfig::registerWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("negotiateauthenticator",
                   "Negotiate User Authenticator Stats",
                   authenticateNegotiateStats, 0, 1);
}