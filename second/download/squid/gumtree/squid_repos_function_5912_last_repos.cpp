static void
authenticateNTLMStats(StoreEntry * sentry)
{
    if (ntlmauthenticators)
        ntlmauthenticators->packStatsInto(sentry, "NTLM Authenticator Statistics");
}