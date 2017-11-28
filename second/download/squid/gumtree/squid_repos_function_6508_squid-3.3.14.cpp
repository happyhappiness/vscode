void
Mgr::IoAction::dump(StoreEntry* entry)
{
    debugs(16, 5, HERE);
    Must(entry != NULL);
    DumpIoStats(data, entry);
}