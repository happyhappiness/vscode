void
Mgr::ReconfigureAction::dump(StoreEntry* entry)
{
    debugs(16, DBG_IMPORTANT, "Reconfigure by Cache Manager command.");
    storeAppendPrintf(entry, "Reconfiguring Squid Process ....");
    reconfigure(SIGHUP);
}