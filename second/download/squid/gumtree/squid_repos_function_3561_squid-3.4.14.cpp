static ClientSocketContext *
parseHttpRequestAbort(ConnStateData * csd, const char *uri)
{
    ClientHttpRequest *http;
    ClientSocketContext *context;
    StoreIOBuffer tempBuffer;
    http = new ClientHttpRequest(csd);
    http->req_sz = csd->in.notYetUsed;
    http->uri = xstrdup(uri);
    setLogUri (http, uri);
    context = ClientSocketContextNew(csd->clientConnection, http);
    tempBuffer.data = context->reqbuf;
    tempBuffer.length = HTTP_REQBUF_SZ;
    clientStreamInit(&http->client_stream, clientGetMoreData, clientReplyDetach,
                     clientReplyStatus, new clientReplyContext(http), clientSocketRecipient,
                     clientSocketDetach, context, tempBuffer);
    return context;
}