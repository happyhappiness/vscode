static void
peerProbeConnectDone(const Comm::ConnectionPointer &conn, Comm::Flag status, int xerrno, void *data)
{
    CachePeer *p = (CachePeer*)data;

    if (status == Comm::OK) {
        peerConnectSucceded(p);
    } else {
        peerConnectFailedSilent(p);
    }

    -- p->testing_now;
    conn->close();
    // TODO: log this traffic.
}