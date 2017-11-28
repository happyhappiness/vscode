static void
clientSetKeepaliveFlag(ClientHttpRequest * http)
{
    HttpRequest *request = http->request;
    const HttpHeader *req_hdr = &request->header;

    debugs(33, 3, "clientSetKeepaliveFlag: http_ver = " <<
           request->http_ver.major << "." << request->http_ver.minor);
    debugs(33, 3, "clientSetKeepaliveFlag: method = " <<
           RequestMethodStr(request->method));

    if (httpMsgIsPersistent(request->http_ver, req_hdr))
        request->flags.proxy_keepalive = 1;
}