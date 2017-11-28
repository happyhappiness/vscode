void
Mgr::ServiceTimesAction::dump(StoreEntry* entry)
{
    debugs(16, 5, HERE);
    Must(entry != NULL);
    DumpServiceTimesStats(data, entry);
}