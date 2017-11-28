void
FwdState::connectDone(const Comm::ConnectionPointer &conn, comm_err_t status, int xerrno)
{
    if (status != COMM_OK) {
        ErrorState *const anErr = makeConnectingError(ERR_CONNECT_FAIL);
        anErr->xerrno = xerrno;
        fail(anErr);

        /* it might have been a timeout with a partially open link */
        if (conn != NULL) {
            if (conn->getPeer())
                peerConnectFailed(conn->getPeer());

            conn->close();
        }
        retryOrBail();
        return;
    }

    serverConn = conn;
    flags.connected_okay = true;

    debugs(17, 3, HERE << serverConnection() << ": '" << entry->url() << "'" );

    comm_add_close_handler(serverConnection()->fd, fwdServerClosedWrapper, this);

    if (serverConnection()->getPeer())
        peerConnectSucceded(serverConnection()->getPeer());

#if USE_SSL
    if (!request->flags.pinned) {
        if ((serverConnection()->getPeer() && serverConnection()->getPeer()->use_ssl) ||
                (!serverConnection()->getPeer() && request->protocol == AnyP::PROTO_HTTPS) ||
                request->flags.sslPeek) {
            initiateSSL();
            return;
        }
    }
#endif

    dispatch();
}