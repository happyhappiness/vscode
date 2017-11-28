void
Mgr::OfflineToggleAction::dump(StoreEntry* entry)
{
    Config.onoff.offline = !Config.onoff.offline;
    debugs(16, DBG_IMPORTANT, "offline_mode now " << (Config.onoff.offline ? "ON" : "OFF") << " by Cache Manager request.");

    storeAppendPrintf(entry, "offline_mode is now %s\n",
                      Config.onoff.offline ? "ON" : "OFF");
}