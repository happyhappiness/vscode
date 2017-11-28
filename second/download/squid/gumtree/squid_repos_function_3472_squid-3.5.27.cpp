void
clientReplyContext::processOnlyIfCachedMiss()
{
    debugs(88, 4, http->request->method << ' ' << http->uri);
    http->al->http.code = Http::scGatewayTimeout;
    ErrorState *err = clientBuildError(ERR_ONLY_IF_CACHED_MISS, Http::scGatewayTimeout, NULL,
                                       http->getConn()->clientConnection->remote, http->request);
    removeClientStoreReference(&sc, http);
    startError(err);
}