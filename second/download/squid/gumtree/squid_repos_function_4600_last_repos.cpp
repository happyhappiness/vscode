void
Ftp::Server::doProcessRequest()
{
    // zero pipelinePrefetchMax() ensures that there is only parsed request
    Must(pipeline.count() == 1);
    Http::StreamPointer context = pipeline.front();
    Must(context != nullptr);

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
        clientProcessRequest(this, Http1::RequestParserPointer(), context.getRaw());
    } else {
        debugs(33, 4, "will resume processing later");
    }
}