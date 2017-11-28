void
clientReplyContext::processOnlyIfCachedMiss()
{
    debugs(88, 4, "clientProcessOnlyIfCachedMiss: '" <<
           RequestMethodStr(http->request->method) << " " << http->uri << "'");
    http->al->http.code = HTTP_GATEWAY_TIMEOUT;
    ErrorState *err = clientBuildError(ERR_ONLY_IF_CACHED_MISS, HTTP_GATEWAY_TIMEOUT, NULL,
                                       http->getConn()->clientConnection->remote, http->request);
    removeClientStoreReference(&sc, http);
    startError(err);
}