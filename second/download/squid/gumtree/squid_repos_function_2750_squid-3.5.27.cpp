void
TunnelStateData::ReadClient(const Comm::ConnectionPointer &, char *buf, size_t len, Comm::Flag errcode, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    assert (cbdataReferenceValid (tunnelState));

    tunnelState->readClient(buf, len, errcode, xerrno);
}