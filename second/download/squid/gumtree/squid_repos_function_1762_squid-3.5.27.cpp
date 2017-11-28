static void
statAvgDump(StoreEntry * sentry, int minutes, int hours)
{
    Mgr::IntervalActionData stats;
    GetAvgStat(stats, minutes, hours);
    DumpAvgStat(stats, sentry);
}