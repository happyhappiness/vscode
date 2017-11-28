void
PeerPoolMgr::checkpoint(const char *reason)
{
    if (!validPeer()) {
        debugs(48, 3, reason << " and peer gone");
        return; // nothing to do after our owner dies; the job will quit
    }

    const int count = peer->standby.pool->count();
    const int limit = peer->standby.limit;
    debugs(48, 7, reason << " with " << count << " ? " << limit);

    if (count < limit)
        openNewConnection();
    else if (count > limit)
        closeOldConnections(count - limit);
}