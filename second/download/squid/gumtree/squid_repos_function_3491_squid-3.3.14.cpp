static void
clientSetKeepaliveFlag(ClientHttpRequest * http)
{
    HttpRequest *request = http->request;

    debugs(33, 3, "clientSetKeepaliveFlag: http_ver = " <<
           request->http_ver.major << "." << request->http_ver.minor);
    debugs(33, 3, "clientSetKeepaliveFlag: method = " <<
           RequestMethodStr(request->method));

    // TODO: move to HttpRequest::hdrCacheInit, just like HttpReply.
    request->flags.proxyKeepalive = request->persistent() ? 1 : 0;
}