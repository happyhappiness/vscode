static void
neighborAliveHtcp(CachePeer * p, const MemObject * mem, const HtcpReplyData * htcp)
{
    peerAlive(p);
    ++ p->stats.pings_acked;
    ++ p->htcp.counts[htcp->hit ? 1 : 0];
    p->htcp.version = htcp->version;
}