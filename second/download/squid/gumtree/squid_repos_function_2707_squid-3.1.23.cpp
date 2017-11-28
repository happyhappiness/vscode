void
TunnelStateData::WriteClientDone(int fd, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    assert (cbdataReferenceValid (tunnelState));

    assert(fd == tunnelState->client.fd());
    tunnelState->writeClientDone(buf, len, flag, xerrno);
}