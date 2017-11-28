void
AuthDigestConfig::registerWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("digestauthenticator",
                   "Digest User Authenticator Stats",
                   authenticateDigestStats, 0, 1);
}