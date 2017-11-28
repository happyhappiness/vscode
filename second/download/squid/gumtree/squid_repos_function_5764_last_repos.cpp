static void
authenticateNegotiateStats(StoreEntry * sentry)
{
    if (negotiateauthenticators)
        negotiateauthenticators->packStatsInto(sentry, "Negotiate Authenticator Statistics");
}