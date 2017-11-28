void CacheManager::ShutdownAction::run(StoreEntry *sentry)
{
    debugs(16, DBG_CRITICAL, "Shutdown by Cache Manager command.");
    shut_down(0);
}