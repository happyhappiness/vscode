void
clientReplyContext::sendPreconditionFailedError()
{
    http->logType = LOG_TCP_HIT;
    ErrorState *const err =
        clientBuildError(ERR_PRECONDITION_FAILED, Http::scPreconditionFailed,
                         NULL, http->getConn()->clientConnection->remote, http->request);
    removeClientStoreReference(&sc, http);
    HTTPMSGUNLOCK(reply);
    startError(err);
}