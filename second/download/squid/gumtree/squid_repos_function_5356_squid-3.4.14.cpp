void
Auth::Ntlm::Scheme::shutdownCleanup()
{
    if (_instance == NULL)
        return;

    _instance = NULL;
    debugs(29, DBG_CRITICAL, "Shutdown: NTLM authentication.");
}