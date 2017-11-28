void
peerConnClosed(CachePeer *p)
{
    --p->stats.conn_open;
    if (p->standby.waitingForClose && peerCanOpenMore(p)) {
        p->standby.waitingForClose = false;
        PeerPoolMgr::Checkpoint(p->standby.mgr, "conn closed");
    }
}