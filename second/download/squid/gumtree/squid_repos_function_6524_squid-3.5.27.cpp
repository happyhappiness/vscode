size_t
ESIContext::send ()
{
    debugs(86, 5, "ESIContext::send: this=" << this);
    /* send any processed data */

    trimBlanks();

    if (!flags.clientwantsdata) {
        debugs(86, 5, "ESIContext::send: Client does not want data - not sending anything");
        return 0;
    }

    if (tree.getRaw() && tree->mayFail()) {
        debugs(86, 5, "ESIContext::send: Tree may fail. Not sending.");
        return 0;
    } else
        flags.oktosend = 1;

#if 0

    if (!flags.oktosend) {

        fatal("ESIContext::send: Not OK to send.\n");
        return 0;
    }

#endif

    if (!(rep != NULL || (outbound.getRaw() &&
                          outbound->len && (outbound_offset <= outbound->len)))) {
        debugs(86, 5, "ESIContext::send: Nothing to send.");
        return 0;
    }

    debugs(86, 5, "ESIContext::send: Sending something...");
    /* Yes! Send it without asking for more upstream */
    /* memcopying because the client provided the buffer */
    /* TODO: skip data until pos == next->readoff; */
    assert (thisNode->data == this);
    clientStreamNode *next = thisNode->next();
    ESIContext *templock = cbdataReference (this);
    size_t len = 0;

    if (outbound.getRaw())
        len = min (next->readBuffer.length, outbound->len - outbound_offset);

    /* prevent corruption on range requests, even though we don't support them yet */
    assert (pos == next->readBuffer.offset);

    /* We must send data or a reply */
    assert (len != 0 || rep != NULL);

    if (len) {
        memcpy(next->readBuffer.data, &outbound->buf[outbound_offset], len);

        if (len + outbound_offset == outbound->len) {
            ESISegment::Pointer temp = outbound->next;
            /* remove the used buffer */
            outbound_offset = 0;
            outbound = temp;
        }

        pos += len;

        if (!outbound.getRaw())
            outboundtail = NULL;

        trimBlanks();
    }

    flags.clientwantsdata = 0;
    debugs(86, 5, "ESIContext::send: this=" << this << " Client no longer wants data ");
    /* Deal with re-entrancy */
    HttpReply::Pointer temprep = rep;
    rep = NULL; /* freed downstream */

    if (temprep != NULL && varState)
        varState->buildVary(temprep.getRaw());

    {
        StoreIOBuffer tempBuffer;
        tempBuffer.length = len;
        tempBuffer.offset = pos - len;
        tempBuffer.data = next->readBuffer.data;
        clientStreamCallback (thisNode, http, temprep.getRaw(), tempBuffer);
    }

    if (len == 0)
        len = 1; /* tell the caller we sent something (because we sent headers */

    cbdataReferenceDone (templock);

    debugs (86,5,"ESIContext::send: this=" << this << " sent " << len);

    return len;
}