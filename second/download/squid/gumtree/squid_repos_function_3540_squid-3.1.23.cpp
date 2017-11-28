int
refreshCheckHTTP(const StoreEntry * entry, HttpRequest * request)
{
    int reason = refreshCheck(entry, request, 0);
    refreshCounts[rcHTTP].total++;
    refreshCounts[rcHTTP].status[reason]++;
    request->flags.stale_if_hit = refreshIsStaleIfHit(reason);
    return (Config.onoff.offline || reason < 200) ? 0 : 1;
}