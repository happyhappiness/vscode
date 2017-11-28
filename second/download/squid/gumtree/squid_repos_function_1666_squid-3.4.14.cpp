static void
statCountersDump(StoreEntry * sentry)
{
    Mgr::CountersActionData stats;
    GetCountersStats(stats);
    DumpCountersStats(stats, sentry);
}