ClientSocketContext *
ConnStateData::abortRequestParsing(const char *const uri)
{
    ClientHttpRequest *http = new ClientHttpRequest(this);
    http->req_sz = in.buf.length();
    http->uri = xstrdup(uri);
    setLogUri (http, uri);
    ClientSocketContext *context = new ClientSocketContext(clientConnection, http);
    StoreIOBuffer tempBuffer;
    tempBuffer.data = context->reqbuf;
    tempBuffer.length = HTTP_REQBUF_SZ;
    clientStreamInit(&http->client_stream, clientGetMoreData, clientReplyDetach,
                     clientReplyStatus, new clientReplyContext(http), clientSocketRecipient,
                     clientSocketDetach, context, tempBuffer);
    return context;
}