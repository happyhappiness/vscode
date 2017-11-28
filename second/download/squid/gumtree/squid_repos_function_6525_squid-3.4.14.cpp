void
Mgr::ServiceTimesAction::collect()
{
    debugs(16, 5, HERE);
    GetServiceTimesStats(data);
}