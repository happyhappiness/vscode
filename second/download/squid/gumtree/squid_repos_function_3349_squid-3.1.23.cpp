void
clientGetMoreData(clientStreamNode * aNode, ClientHttpRequest * http)
{
    /* Test preconditions */
    assert(aNode != NULL);
    assert(cbdataReferenceValid(aNode));
    assert(aNode->node.prev == NULL);
    assert(aNode->node.next != NULL);
    clientReplyContext *context = dynamic_cast<clientReplyContext *>(aNode->data.getRaw());
    assert (context);
    assert(context->http == http);


    clientStreamNode *next = ( clientStreamNode *)aNode->node.next->data;

    if (!context->ourNode)
        context->ourNode = aNode;

    /* no cbdatareference, this is only used once, and safely */
    if (context->flags.storelogiccomplete) {
        StoreIOBuffer tempBuffer;
        tempBuffer.offset = next->readBuffer.offset + context->headers_sz;
        tempBuffer.length = next->readBuffer.length;
        tempBuffer.data = next->readBuffer.data;

        storeClientCopy(context->sc, http->storeEntry(),
                        tempBuffer, clientReplyContext::SendMoreData, context);
        return;
    }

    if (context->http->request->method == METHOD_PURGE) {
        context->purgeRequest();
        return;
    }

    // OPTIONS with Max-Forwards:0 handled in clientProcessRequest()

    if (context->http->request->method == METHOD_TRACE) {
        if (context->http->request->header.getInt64(HDR_MAX_FORWARDS) == 0) {
            context->traceReply(aNode);
            return;
        }

        /* continue forwarding, not finished yet. */
        http->logType = LOG_TCP_MISS;

        context->doGetMoreData();
    } else
        context->identifyStoreObject();
}