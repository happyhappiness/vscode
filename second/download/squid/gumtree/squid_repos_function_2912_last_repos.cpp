void
clientReplyContext::processOnlyIfCachedMiss()
{
    debugs(88, 4, http->request->method << ' ' << http->uri);
    http->al->http.code = Http::scGatewayTimeout;
    Ip::Address tmp_noaddr;
    tmp_noaddr.setNoAddr();
    ErrorState *err = clientBuildError(ERR_ONLY_IF_CACHED_MISS, Http::scGatewayTimeout, NULL,
                                       http->getConn() ? http->getConn()->clientConnection->remote : tmp_noaddr,
                                       http->request);
    removeClientStoreReference(&sc, http);
    startError(err);
}