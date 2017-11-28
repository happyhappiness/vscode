static void
authenticateNegotiateStats(StoreEntry * sentry)
{
    helperStatefulStats(sentry, negotiateauthenticators, "Negotiate Authenticator Statistics");
}