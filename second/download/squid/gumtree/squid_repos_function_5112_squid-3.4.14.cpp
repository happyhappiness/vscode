void
Comm::Connection::close()
{
    if (isOpen()) {
        comm_close(fd);
        fd = -1;
        if (CachePeer *p=getPeer())
            -- p->stats.conn_open;
    }
}