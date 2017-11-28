void
PeerPoolMgr::handleSecuredPeer(Security::EncryptorAnswer &answer)
{
    Must(securer != NULL);
    securer = NULL;

    if (closer != NULL) {
        if (answer.conn != NULL)
            comm_remove_close_handler(answer.conn->fd, closer);
        else
            closer->cancel("securing completed");
        closer = NULL;
    }

    if (!validPeer()) {
        debugs(48, 3, "peer gone");
        if (answer.conn != NULL)
            answer.conn->close();
        return;
    }

    if (answer.error.get()) {
        if (answer.conn != NULL)
            answer.conn->close();
        // PeerConnector calls peerConnectFailed() for us;
        checkpoint("conn securing failure"); // may retry
        return;
    }

    pushNewConnection(answer.conn);
}