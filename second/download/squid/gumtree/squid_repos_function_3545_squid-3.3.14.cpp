void
ConnStateData::checkHeaderLimits()
{
    if (in.notYetUsed < Config.maxRequestHeaderSize)
        return; // can accumulte more header data

    debugs(33, 3, "Request header is too large (" << in.notYetUsed << " > " <<
           Config.maxRequestHeaderSize << " bytes)");

    ClientSocketContext *context = parseHttpRequestAbort(this, "error:request-too-large");
    clientStreamNode *node = context->getClientReplyContext();
    clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
    assert (repContext);
    repContext->setReplyToError(ERR_TOO_BIG,
                                HTTP_BAD_REQUEST, METHOD_NONE, NULL,
                                clientConnection->remote, NULL, NULL, NULL);
    context->registerWithConn();
    context->pullData();
}