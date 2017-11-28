void
AuthNTLMConfig::registerWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("ntlmauthenticator",
                   "NTLM User Authenticator Stats",
                   authenticateNTLMStats, 0, 1);
}