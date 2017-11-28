static void
authenticateNTLMStats(StoreEntry * sentry)
{
    helperStatefulStats(sentry, ntlmauthenticators, "NTLM Authenticator Statistics");
}