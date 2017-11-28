static int
peerSelectIcpPing(HttpRequest * request, int direct, StoreEntry * entry)
{
    int n;
    assert(entry);
    assert(entry->ping_status == PING_NONE);
    assert(direct != DIRECT_YES);
    debugs(44, 3, "peerSelectIcpPing: " << entry->url());

    if (!request->flags.hierarchical && direct != DIRECT_NO)
        return 0;

    if (EBIT_TEST(entry->flags, KEY_PRIVATE) && !neighbors_do_private_keys)
        if (direct != DIRECT_NO)
            return 0;

    n = neighborsCount(request);

    debugs(44, 3, "peerSelectIcpPing: counted " << n << " neighbors");

    return n;
}