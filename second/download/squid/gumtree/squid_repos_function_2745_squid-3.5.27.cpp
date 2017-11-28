void
TunnelStateData::readConnectResponseDone(char *buf, size_t len, Comm::Flag errcode, int xerrno)
{
    debugs(26, 3, server.conn << ", read " << len << " bytes, err=" << errcode);
    assert(waitingForConnectResponse());

    if (errcode == Comm::ERR_CLOSING)
        return;

    if (len > 0) {
        connectRespBuf->appended(len);
        server.bytesIn(len);
        kb_incr(&(statCounter.server.all.kbytes_in), len);
        kb_incr(&(statCounter.server.other.kbytes_in), len);
    }

    if (keepGoingAfterRead(len, errcode, xerrno, server, client))
        handleConnectResponse(len);
}