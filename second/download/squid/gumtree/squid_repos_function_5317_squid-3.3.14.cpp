void
Auth::Digest::Scheme::shutdownCleanup()
{
    if (_instance == NULL)
        return;

    PurgeCredentialsCache();
    authenticateDigestNonceShutdown();

    _instance = NULL;
    debugs(29, DBG_CRITICAL, "Shutdown: Digest authentication.");
}