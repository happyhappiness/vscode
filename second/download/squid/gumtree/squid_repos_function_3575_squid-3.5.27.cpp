void
clientSetKeepaliveFlag(ClientHttpRequest * http)
{
    HttpRequest *request = http->request;

    debugs(33, 3, "http_ver = " << request->http_ver);
    debugs(33, 3, "method = " << request->method);

    // TODO: move to HttpRequest::hdrCacheInit, just like HttpReply.
    request->flags.proxyKeepalive = request->persistent();
}