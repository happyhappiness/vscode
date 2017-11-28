void
Ftp::Server::setReply(const int code, const char *msg)
{
    ClientSocketContext::Pointer context = getCurrentContext();
    ClientHttpRequest *const http = context->http;
    assert(http != NULL);
    assert(http->storeEntry() == NULL);

    HttpReply *const reply = Ftp::HttpReplyWrapper(code, msg, Http::scNoContent, 0);

    setLogUri(http, urlCanonicalClean(http->request));

    clientStreamNode *const node = context->getClientReplyContext();
    clientReplyContext *const repContext =
        dynamic_cast<clientReplyContext *>(node->data.getRaw());
    assert(repContext != NULL);

    RequestFlags reqFlags;
    reqFlags.cachable = false; // force releaseRequest() in storeCreateEntry()
    reqFlags.noCache = true;
    repContext->createStoreEntry(http->request->method, reqFlags);
    http->storeEntry()->replaceHttpReply(reply);
}