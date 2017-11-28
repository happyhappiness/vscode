void
Ftp::Gateway::dataChannelConnected(const CommConnectCbParams &io)
{
    debugs(9, 3, HERE);
    data.opener = NULL;

    if (io.flag != Comm::OK) {
        debugs(9, 2, HERE << "Failed to connect. Retrying via another method.");

        // ABORT on timeouts. server may be waiting on a broken TCP link.
        if (io.xerrno == Comm::TIMEOUT)
            writeCommand("ABOR\r\n");

        // try another connection attempt with some other method
        ftpSendPassive(this);
        return;
    }

    data.opened(io.conn, dataCloser());
    ftpRestOrList(this);
}