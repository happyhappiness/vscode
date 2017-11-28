void
Mgr::CountersAction::collect()
{
    debugs(16, 5, HERE);
    GetCountersStats(data);
}