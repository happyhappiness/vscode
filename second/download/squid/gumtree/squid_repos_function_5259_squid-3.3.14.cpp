void
Auth::Ntlm::Config::registerWithCacheManager(void)
{
    Mgr::RegisterAction("ntlmauthenticator",
                        "NTLM User Authenticator Stats",
                        authenticateNTLMStats, 0, 1);
}