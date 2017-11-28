void
Comm::Connection::noteClosure()
{
    if (isOpen()) {
        fd = -1;
        if (CachePeer *p=getPeer())
            peerConnClosed(p);
    }
}