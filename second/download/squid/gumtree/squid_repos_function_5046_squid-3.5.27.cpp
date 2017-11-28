void
Ftp::Server::connectedForData(const CommConnectCbParams &params)
{
    connector = NULL;

    if (params.flag != Comm::OK) {
        /* it might have been a timeout with a partially open link */
        if (params.conn != NULL)
            params.conn->close();
        setReply(425, "Cannot open data connection.");
        ClientSocketContext::Pointer context = getCurrentContext();
        Must(context->http);
        Must(context->http->storeEntry() != NULL);
    } else {
        Must(dataConn == params.conn);
        Must(Comm::IsConnOpen(params.conn));
        fd_note(params.conn->fd, "active client ftp data");
    }

    doProcessRequest();
}