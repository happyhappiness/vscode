void
Mgr::IntervalAction::dump(StoreEntry* entry)
{
    debugs(16, 5, HERE);
    Must(entry != NULL);
    DumpAvgStat(data, entry);
}