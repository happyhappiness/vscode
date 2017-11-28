int
refreshCheckICP(const StoreEntry * entry, HttpRequest * request)
{
    int reason = refreshCheck(entry, request, 30);
    ++ refreshCounts[rcICP].total;
    ++ refreshCounts[rcICP].status[reason];
    return (reason < 200) ? 0 : 1;
}