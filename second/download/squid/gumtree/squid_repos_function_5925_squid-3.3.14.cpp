void
esiProcessStream (clientStreamNode *thisNode, ClientHttpRequest *http, HttpReply *rep, StoreIOBuffer receivedData)
{
    /* test preconditions */
    assert (thisNode != NULL);
    /* ESI TODO: handle thisNode rather than asserting - it should only ever
     * happen if we cause an abort and the callback chain
     * loops back to here, so we can simply return. However, that itself
     * shouldn't happen, so it stays as an assert for now. */
    assert (cbdataReferenceValid (thisNode));
    /*
     * if data is NULL thisNode is the first entrance. If rep is also NULL,
     * something is wrong.
     * */
    assert (thisNode->data.getRaw() != NULL || rep);
    assert (thisNode->node.next != NULL);

    if (!thisNode->data.getRaw())
        /* setup ESI context from reply headers */
        thisNode->data = ESIContextNew(rep, thisNode, http);

    ESIContext::Pointer context = dynamic_cast<ESIContext *>(thisNode->data.getRaw());

    assert (context.getRaw() != NULL);

    context->finishRead();

    /* Skipping all ESI processing. All remaining data gets untouched.
     * Mainly used when an error or other non-ESI processable entity
     * has been detected to prevent ESI processing the error body
     */
    if (context->flags.passthrough) {
        clientStreamCallback (thisNode, http, rep, receivedData);
        return;
    }

    debugs(86, 3, "esiProcessStream: Processing thisNode " << thisNode <<
           " context " << context.getRaw() << " offset " <<
           (int) receivedData.offset << " length " <<
           (unsigned int)receivedData.length);

    /* once we finish the template, we *cannot* return here */
    assert (!context->flags.finishedtemplate);
    assert (!context->cachedASTInUse);

    /* Can we generate any data ?*/

    if (receivedData.data) {
        /* Increase our buffer area with incoming data */
        assert (receivedData.length <= HTTP_REQBUF_SZ);
        assert (thisNode->readBuffer.offset == receivedData.offset);
        debugs (86,5, "esiProcessStream found " << receivedData.length << " bytes of body data at offset " << receivedData.offset);
        /* secure the data for later use */

        if (!context->incoming.getRaw()) {
            /* create a new buffer segment */
            debugs(86, 5, "esiProcessStream: Setting up incoming buffer");
            context->buffered = new ESISegment;
            context->incoming = context->buffered;
        }

        if (receivedData.data != &context->incoming->buf[context->incoming->len]) {
            /* We have to copy the data out because we didn't supply thisNode buffer */
            size_t space = HTTP_REQBUF_SZ - context->incoming->len;
            size_t len = min (space, receivedData.length);
            debugs(86, 5, "Copying data from " << receivedData.data << " to " <<
                   &context->incoming->buf[context->incoming->len] <<
                   " because our buffer was not used");

            memcpy(&context->incoming->buf[context->incoming->len], receivedData.data, len);
            context->incoming->len += len;

            if (context->incoming->len == HTTP_REQBUF_SZ) {
                /* append another buffer */
                context->incoming->next = new ESISegment;
                context->incoming = context->incoming->next;
            }

            if (len != receivedData.length) {
                /* capture the remnants */
                memcpy(context->incoming->buf, &receivedData.data[len], receivedData.length - len);
                context->incoming->len = receivedData.length - len;
            }

            /* and note where we are up to */
            context->readpos += receivedData.length;
        } else {
            /* update our position counters, and if needed assign a new buffer */
            context->incoming->len += receivedData.length;
            assert (context->incoming->len <= HTTP_REQBUF_SZ);

            if (context->incoming->len > HTTP_REQBUF_SZ * 3 / 4) {
                /* allocate a new buffer - to stop us asking for ridiculously small amounts */
                context->incoming->next = new ESISegment;
                context->incoming = context->incoming->next;
            }

            context->readpos += receivedData.length;
        }
    }

    /* EOF / Read error /  aborted entry */
    if (rep == NULL && receivedData.data == NULL && receivedData.length == 0 && !context->flags.finishedtemplate) {
        /* TODO: get stream status to test the entry for aborts */
        /* else flush the esi processor */
        debugs(86, 5, "esiProcess: " << context.getRaw() << " Finished reading upstream data");
        /* This is correct */
        context->flags.finishedtemplate = 1;
    }

    switch (context->kick()) {

    case ESIContext::ESI_KICK_FAILED:
        /* thisNode can not happen - processing can't fail until we have data,
         * and when we come here we have sent data to the client
         */
        return;

    case ESIContext::ESI_KICK_SENT:

    case ESIContext::ESI_KICK_INPROGRESS:
        return;

    case ESIContext::ESI_KICK_PENDING:
        break;
    }

    /* ok.. no data sent, try to pull more data in from upstream.
     * FIXME: Don't try thisNode if we have finished reading the template
     */
    if (!context->flags.finishedtemplate && !context->reading()
            && !context->cachedASTInUse) {
        StoreIOBuffer tempBuffer;
        assert (context->incoming.getRaw() && context->incoming->len < HTTP_REQBUF_SZ);
        tempBuffer.offset = context->readpos;
        tempBuffer.length =  HTTP_REQBUF_SZ - context->incoming->len;
        tempBuffer.data = &context->incoming->buf[context->incoming->len];
        context->startRead();
        clientStreamRead (thisNode, http, tempBuffer);
        return;
    }

    debugs(86, 3, "esiProcessStream: no data to send, no data to read, awaiting a callback");
}