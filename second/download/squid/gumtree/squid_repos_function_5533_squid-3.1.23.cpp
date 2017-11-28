void
esiBufferRecipient (clientStreamNode *node, ClientHttpRequest *http, HttpReply *rep, StoreIOBuffer receivedData)
{
    /* Test preconditions */
    assert (node != NULL);
    /* ESI TODO: handle thisNode rather than asserting
     * - it should only ever happen if we cause an
     * abort and the callback chain loops back to
     * here, so we can simply return. However, that
     * itself shouldn't happen, so it stays as an
     * assert for now. */
    assert (cbdataReferenceValid (node));
    assert (node->node.next == NULL);
    assert (http->getConn() == NULL);

    ESIStreamContext::Pointer esiStream = dynamic_cast<ESIStreamContext *>(node->data.getRaw());
    assert (esiStream.getRaw() != NULL);
    /* If segments become more flexible, ignore thisNode */
    assert (receivedData.length <= sizeof(esiStream->localbuffer->buf));
    assert (!esiStream->finished);

    debugs (86,5, HERE << "rep " << rep << " body " << receivedData.data << " len " << receivedData.length);
    assert (node->readBuffer.offset == receivedData.offset || receivedData.length == 0);

    /* trivial case */

    if (http->out.offset != 0) {
        assert(rep == NULL);
    } else {
        if (rep) {
            if (rep->sline.status != HTTP_OK) {
                rep = NULL;
                esiStream->include->fail (esiStream);
                esiStream->finished = 1;
                httpRequestFree (http);
                return;
            }

#if HEADERS_LOG
            /* should be done in the store rather than every recipient?  */
            headersLog(0, 0, http->request->method, rep);

#endif
            rep = NULL;
        }
    }

    if (receivedData.data && receivedData.length) {
        http->out.offset += receivedData.length;

        if (receivedData.data >= esiStream->localbuffer->buf &&
                receivedData.data < &esiStream->localbuffer->buf[sizeof(esiStream->localbuffer->buf)]) {
            /* original static buffer */

            if (receivedData.data != esiStream->localbuffer->buf) {
                /* But not the start of it */
                xmemmove (esiStream->localbuffer->buf, receivedData.data, receivedData.length);
            }

            esiStream->localbuffer->len = receivedData.length;
        } else {
            assert (esiStream->buffer.getRaw() != NULL);
            esiStream->buffer->len = receivedData.length;
        }
    }

    /* EOF / Read error /  aborted entry */
    if (rep == NULL && receivedData.data == NULL && receivedData.length == 0) {
        /* TODO: get stream status to test the entry for aborts */
        debugs(86, 5, HERE << "Finished reading upstream data in subrequest");
        esiStream->include->subRequestDone (esiStream, true);
        esiStream->finished = 1;
        httpRequestFree (http);
        return;
    }


    /* after the write to the user occurs, (ie here, or in a callback)
     * we call */
    if (clientHttpRequestStatus(-1, http)) {
        /* TODO: Does thisNode if block leak htto ? */
        /* XXX when reviewing ESI this is the first place to look */
        node->data = NULL;
        esiStream->finished = 1;
        esiStream->include->fail (esiStream);
        return;
    };

    switch (clientStreamStatus (node, http)) {

    case STREAM_UNPLANNED_COMPLETE: /* fallthru ok */

    case STREAM_COMPLETE: /* ok */
        debugs(86, 3, "ESI subrequest finished OK");
        esiStream->include->subRequestDone (esiStream, true);
        esiStream->finished = 1;
        httpRequestFree (http);
        return;

    case STREAM_FAILED:
        debugs(86, 1, "ESI subrequest failed transfer");
        esiStream->include->fail (esiStream);
        esiStream->finished = 1;
        httpRequestFree (http);
        return;

    case STREAM_NONE: {
        StoreIOBuffer tempBuffer;

        if (!esiStream->buffer.getRaw()) {
            esiStream->buffer = esiStream->localbuffer;
        }

        esiStream->buffer = esiStream->buffer->tail();

        if (esiStream->buffer->len) {
            esiStream->buffer->next = new ESISegment;
            esiStream->buffer = esiStream->buffer->next;
        }

        tempBuffer.offset = http->out.offset;
        tempBuffer.length = sizeof (esiStream->buffer->buf);
        tempBuffer.data = esiStream->buffer->buf;
        /* now just read into 'buffer' */
        clientStreamRead (node, http, tempBuffer);
        debugs(86, 5, HERE << "Requested more data for ESI subrequest");
    }

    break;

    default:
        fatal ("Hit unreachable code in esiBufferRecipient\n");
    }

}