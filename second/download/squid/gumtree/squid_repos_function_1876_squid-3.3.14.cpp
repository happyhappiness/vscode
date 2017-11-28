static void
peerCountMcastPeersSchedule(CachePeer * p, time_t when)
{
    if (p->mcast.flags.count_event_pending)
        return;

    eventAdd("peerCountMcastPeersStart",
             peerCountMcastPeersStart,
             p,
             (double) when, 1);

    p->mcast.flags.count_event_pending = 1;
}