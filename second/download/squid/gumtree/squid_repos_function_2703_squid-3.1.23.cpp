void
TunnelStateData::readClient(char *buf, size_t len, comm_err_t errcode, int xerrno)
{
    /*
     * Bail out early on COMM_ERR_CLOSING
     * - close handlers will tidy up for us
     */

    if (errcode == COMM_ERR_CLOSING)
        return;

    debugs(26, 3, "tunnelReadClient: FD " << client.fd() << ", read " << len << " bytes");

    if (len > 0) {
        client.bytesIn(len);
        kb_incr(&statCounter.client_http.kbytes_in, len);
    }

    copy (len, errcode, xerrno, client, server, WriteServerDone);
}