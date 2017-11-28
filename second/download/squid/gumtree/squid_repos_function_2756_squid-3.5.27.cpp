void
TunnelStateData::WriteClientDone(const Comm::ConnectionPointer &, char *buf, size_t len, Comm::Flag flag, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    assert (cbdataReferenceValid (tunnelState));
    tunnelState->client.writer = NULL;

    tunnelState->writeClientDone(buf, len, flag, xerrno);
}