static void
peerProbeConnectDone(const Comm::ConnectionPointer &conn, comm_err_t status, int xerrno, void *data)
{
    CachePeer *p = (CachePeer*)data;

    if (status == COMM_OK) {
        peerConnectSucceded(p);
    } else {
        peerConnectFailedSilent(p);
    }

    -- p->testing_now;
    conn->close();
    // TODO: log this traffic.
}