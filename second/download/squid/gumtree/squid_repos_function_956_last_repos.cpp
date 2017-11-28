void
PeerPoolMgr::pushNewConnection(const Comm::ConnectionPointer &conn)
{
    Must(validPeer());
    Must(Comm::IsConnOpen(conn));
    peer->standby.pool->push(conn, NULL /* domain */);
    // push() will trigger a checkpoint()
}