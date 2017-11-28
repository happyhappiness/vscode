void
TunnelStateData::ReadClient(int fd, char *buf, size_t len, comm_err_t errcode, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    assert (cbdataReferenceValid (tunnelState));

    assert(fd == tunnelState->client.fd());
    tunnelState->readClient(buf, len, errcode, xerrno);
}