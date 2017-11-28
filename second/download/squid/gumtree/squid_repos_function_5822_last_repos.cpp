static void
authenticateBasicStats(StoreEntry * sentry)
{
    if (basicauthenticators)
        basicauthenticators->packStatsInto(sentry, "Basic Authenticator Statistics");
}