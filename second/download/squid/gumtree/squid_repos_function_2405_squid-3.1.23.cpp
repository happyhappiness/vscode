static void
fwdPeerClosed(int fd, void *data)
{
    peer *p = (peer *)data;
    p->stats.conn_open--;
}