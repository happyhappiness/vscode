void
Mgr::StoreIoAction::dump(StoreEntry* entry)
{
    debugs(16, 5, HERE);
    Must(entry != NULL);
    storeAppendPrintf(entry, "Store IO Interface Stats\n");
    storeAppendPrintf(entry, "create.calls %.0f\n", data.create_calls);
    storeAppendPrintf(entry, "create.select_fail %.0f\n", data.create_select_fail);
    storeAppendPrintf(entry, "create.create_fail %.0f\n", data.create_create_fail);
    storeAppendPrintf(entry, "create.success %.0f\n", data.create_success);
}