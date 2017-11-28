void
Ftp::Server::doProcessRequest()
{
    // zero pipelinePrefetchMax() ensures that there is only parsed request
    ClientSocketContext::Pointer context = getCurrentContext();
    Must(context != NULL);
    Must(getConcurrentRequestCount() == 1);

    ClientHttpRequest *const http = context->http;
    assert(http != NULL);

    HttpRequest *const request = http->request;
    Must(http->storeEntry() || request);
    const bool mayForward = !http->storeEntry() && handleRequest(request);

    if (http->storeEntry() != NULL) {
        debugs(33, 4, "got an immediate response");
        clientSetKeepaliveFlag(http);
        context->pullData();
    } else if (mayForward) {
        debugs(33, 4, "forwarding request to server side");
        assert(http->storeEntry() == NULL);
        clientProcessRequest(this, NULL /*parser*/, context.getRaw(),
                             request->method, request->http_ver);
    } else {
        debugs(33, 4, "will resume processing later");
    }
}