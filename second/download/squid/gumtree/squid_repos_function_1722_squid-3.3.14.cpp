static void
dnsStats(StoreEntry * sentry)
{
    storeAppendPrintf(sentry, "Dnsserver Statistics:\n");
    helperStats(sentry, dnsservers);
}