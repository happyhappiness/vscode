void
connCancelIncompleteRequests(ConnStateData * conn)
{
    ClientSocketContext *context = parseHttpRequestAbort(conn, "error:request-too-large");
    clientStreamNode *node = context->getClientReplyContext();
    assert(!connKeepReadingIncompleteRequest(conn));
    if (conn->in.dechunkingState == ConnStateData::chunkParsing) {
        debugs(33, 1, "Chunked request is too large (" << conn->in.notYetUsed << " bytes)");
        debugs(33, 1, "Config 'chunked_request_body_max_size'= " << Config.maxChunkedRequestBodySize << " bytes.");
    } else {
        debugs(33, 1, "Request header is too large (" << conn->in.notYetUsed << " bytes)");
        debugs(33, 1, "Config 'request_header_max_size'= " << Config.maxRequestHeaderSize << " bytes.");
    }
    clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
    assert (repContext);
    repContext->setReplyToError(ERR_TOO_BIG,
                                HTTP_REQUEST_ENTITY_TOO_LARGE, METHOD_NONE, NULL,
                                conn->peer, NULL, NULL, NULL);
    context->registerWithConn();
    context->pullData();
}