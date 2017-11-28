int
refreshCheckHTCP(const StoreEntry * entry, HttpRequest * request)
{
    int reason = refreshCheck(entry, request, 10);
    refreshCounts[rcHTCP].total++;
    refreshCounts[rcHTCP].status[reason]++;
    return (reason < 200) ? 0 : 1;
}