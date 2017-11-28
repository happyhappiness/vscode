void
TunnelStateData::readServer(char *, size_t len, Comm::Flag errcode, int xerrno)
{
    debugs(26, 3, HERE << server.conn << ", read " << len << " bytes, err=" << errcode);
    server.delayedLoops=0;

    /*
     * Bail out early on Comm::ERR_CLOSING
     * - close handlers will tidy up for us
     */

    if (errcode == Comm::ERR_CLOSING)
        return;

    if (len > 0) {
        server.bytesIn(len);
        statCounter.server.all.kbytes_in += len;
        statCounter.server.other.kbytes_in += len;
    }

    if (keepGoingAfterRead(len, errcode, xerrno, server, client))
        copy(len, server, client, WriteClientDone);
}