void
clientReplyContext::sendPreconditionFailedError()
{
    http->logType = LOG_TCP_HIT;
    Ip::Address tmp_noaddr;
    tmp_noaddr.setNoAddr();
    ErrorState *const err =
        clientBuildError(ERR_PRECONDITION_FAILED, Http::scPreconditionFailed,
                         NULL, http->getConn() ? http->getConn()->clientConnection->remote : tmp_noaddr, http->request);
    removeClientStoreReference(&sc, http);
    HTTPMSGUNLOCK(reply);
    startError(err);
}