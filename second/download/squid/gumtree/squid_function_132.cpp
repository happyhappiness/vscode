void
CacheManager::ReconfigureAction::run(StoreEntry * sentry)
{
    debugs(16, DBG_IMPORTANT, "Reconfigure by Cache Manager command.");
    storeAppendPrintf(sentry, "Reconfiguring Squid Process ....");
    reconfigure(SIGHUP);
}