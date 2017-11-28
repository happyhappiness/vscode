void
TunnelStateData::ReadServer(int fd, char *buf, size_t len, comm_err_t errcode, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    assert (cbdataReferenceValid (tunnelState));

    assert(fd == tunnelState->server.fd());
    tunnelState->readServer(buf, len, errcode, xerrno);
}