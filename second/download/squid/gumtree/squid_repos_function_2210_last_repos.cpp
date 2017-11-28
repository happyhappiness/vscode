void
TunnelStateData::readClient(char *, size_t len, Comm::Flag errcode, int xerrno)
{
    debugs(26, 3, HERE << client.conn << ", read " << len << " bytes, err=" << errcode);
    client.delayedLoops=0;

    /*
     * Bail out early on Comm::ERR_CLOSING
     * - close handlers will tidy up for us
     */

    if (errcode == Comm::ERR_CLOSING)
        return;

    if (len > 0) {
        client.bytesIn(len);
        statCounter.client_http.kbytes_in += len;
    }

    if (keepGoingAfterRead(len, errcode, xerrno, client, server))
        copy(len, client, server, WriteServerDone);
}