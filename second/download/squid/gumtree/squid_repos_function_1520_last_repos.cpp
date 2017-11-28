bool
peerCanOpenMore(const CachePeer *p)
{
    const int effectiveLimit = p->max_conn <= 0 ? Squid_MaxFD : p->max_conn;
    const int remaining = effectiveLimit - p->stats.conn_open;
    debugs(15, 7, remaining << '=' << effectiveLimit << '-' << p->stats.conn_open);
    return remaining > 0;
}