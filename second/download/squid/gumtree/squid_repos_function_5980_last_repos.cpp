static void
authenticateDigestStats(StoreEntry * sentry)
{
    if (digestauthenticators)
        digestauthenticators->packStatsInto(sentry, "Digest Authenticator Statistics");
}