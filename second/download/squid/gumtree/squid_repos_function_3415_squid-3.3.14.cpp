void
clientReplyContext::sendBodyTooLargeError()
{
    Ip::Address tmp_noaddr;
    tmp_noaddr.SetNoAddr(); // TODO: make a global const
    http->logType = LOG_TCP_DENIED_REPLY;
    ErrorState *err = clientBuildError(ERR_TOO_BIG, HTTP_FORBIDDEN, NULL,
                                       http->getConn() != NULL ? http->getConn()->clientConnection->remote : tmp_noaddr,
                                       http->request);
    removeClientStoreReference(&(sc), http);
    HTTPMSGUNLOCK(reply);
    startError(err);

}