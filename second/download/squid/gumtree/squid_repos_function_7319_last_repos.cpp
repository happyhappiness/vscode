void
Mgr::CountersAction::dump(StoreEntry* entry)
{
    debugs(16, 5, HERE);
    Must(entry != NULL);
    DumpCountersStats(data, entry);
}