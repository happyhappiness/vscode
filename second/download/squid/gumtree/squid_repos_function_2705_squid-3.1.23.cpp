void
TunnelStateData::WriteServerDone(int fd, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    assert (cbdataReferenceValid (tunnelState));

    assert(fd == tunnelState->server.fd());
    tunnelState->writeServerDone(buf, len, flag, xerrno);
}