void
clientReplyContext::processOnlyIfCachedMiss()
{
    ErrorState *err = NULL;
    debugs(88, 4, "clientProcessOnlyIfCachedMiss: '" <<
           RequestMethodStr(http->request->method) << " " << http->uri << "'");
    http->al.http.code = HTTP_GATEWAY_TIMEOUT;
    err = clientBuildError(ERR_ONLY_IF_CACHED_MISS, HTTP_GATEWAY_TIMEOUT, NULL, http->getConn()->peer, http->request);
    removeClientStoreReference(&sc, http);
    startError(err);
}