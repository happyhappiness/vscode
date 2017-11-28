void
esiStreamRead (clientStreamNode *thisNode, ClientHttpRequest *http)
{
    clientStreamNode *next;
    /* Test preconditions */
    assert (thisNode != NULL);
    assert (cbdataReferenceValid (thisNode));
    /* we are not in the chain until ESI is detected on a data callback */
    assert (thisNode->node.prev != NULL);
    assert (thisNode->node.next != NULL);

    ESIContext::Pointer context = dynamic_cast<ESIContext *>(thisNode->data.getRaw());
    assert (context.getRaw() != NULL);

    if (context->flags.passthrough) {
        /* passthru mode - read into supplied buffers */
        next = thisNode->next();
        clientStreamRead (thisNode, http, next->readBuffer);
        return;
    }

    context->flags.clientwantsdata = 1;
    debugs(86, 5, "esiStreamRead: Client now wants data");

    /* Ok, not passing through */

    switch (context->kick ()) {

    case ESIContext::ESI_KICK_FAILED:
    /* this can not happen - processing can't fail until we have data,
     * and when we come here we have sent data to the client
     */

    case ESIContext::ESI_KICK_SENT:

    case ESIContext::ESI_KICK_INPROGRESS:
        return;

    case ESIContext::ESI_KICK_PENDING:
        break;
    }

    /* Nothing to send */

    if (context->flags.oktosend && (context->flags.finishedtemplate
                                    || context->cachedASTInUse) &&
            ! context->flags.finished) {
        /* we've started sending, finished reading, but not finished
         * processing. stop here, a callback will resume the stream
         * flow
         */
        debugs(86, 5, "esiStreamRead: Waiting for async resume of esi processing");
        return;
    }

    if (context->flags.oktosend && context->flags.finished && context->outbound.getRaw()) {
        debugs(86, 5, "all processing complete, but outbound data still buffered");
        assert (!context->flags.clientwantsdata);
        /* client MUST be processing the last reply */
        return;
    }

    if (context->flags.oktosend && context->flags.finished) {
        StoreIOBuffer tempBuffer;
        assert (!context->outbound.getRaw());
        /* We've finished processing, and there is no more data buffered */
        debugs(86, 5, "Telling recipient EOF on READ");
        clientStreamCallback (thisNode, http, NULL, tempBuffer);
        return;
    }

    if (context->reading())
        return;

    /* no data that is ready to send, and still reading? well, lets get some */
    /* secure a buffer */
    if (!context->incoming.getRaw()) {
        /* create a new buffer segment */
        context->buffered = new ESISegment;
        context->incoming = context->buffered;
    }

    assert (context->incoming.getRaw() && context->incoming->len != HTTP_REQBUF_SZ);
    {
        StoreIOBuffer tempBuffer;
        tempBuffer.offset =  context->readpos;
        tempBuffer.length = context->incoming->len - HTTP_REQBUF_SZ;
        tempBuffer.data = &context->incoming->buf[context->incoming->len];
        context->startRead();
        clientStreamRead (thisNode, http, tempBuffer);
    }
}