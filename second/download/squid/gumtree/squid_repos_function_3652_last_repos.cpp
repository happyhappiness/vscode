void
Adaptation::Icap::Xaction::handleSecuredPeer(Security::EncryptorAnswer &answer)
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

    if (answer.error.get()) {
        if (answer.conn != NULL)
            answer.conn->close();
        debugs(93, 2, typeName <<
               " TLS negotiation to " << service().cfg().uri << " failed");
        service().noteConnectionFailed("failure");
        detailError(ERR_DETAIL_ICAP_XACT_SSL_START);
        throw TexcHere("cannot connect to the TLS ICAP service");
    }

    debugs(93, 5, "TLS negotiation to " << service().cfg().uri << " complete");

    service().noteConnectionUse(answer.conn);

    handleCommConnected();
}