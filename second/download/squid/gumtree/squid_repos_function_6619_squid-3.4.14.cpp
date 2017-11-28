void
Mgr::ShutdownAction::dump(StoreEntry* entry)
{
    debugs(16, DBG_CRITICAL, "Shutdown by Cache Manager command.");
    shut_down(SIGTERM);
}