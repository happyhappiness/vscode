void
Ftp::Relay::dataChannelConnected(const CommConnectCbParams &io)
{
    debugs(9, 3, status());
    data.opener = NULL;

    if (io.flag != Comm::OK) {
        debugs(9, 2, "failed to connect FTP server data channel");
        forwardError(ERR_CONNECT_FAIL, io.xerrno);
        return;
    }

    debugs(9, 2, "connected FTP server data channel: " << io.conn);

    data.opened(io.conn, dataCloser());

    sendCommand();
}