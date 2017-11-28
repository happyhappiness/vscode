clientStream_status_t
esiStreamStatus (clientStreamNode *thisNode, ClientHttpRequest *http)
{
    /* Test preconditions */
    assert (thisNode != NULL);
    assert (cbdataReferenceValid (thisNode));
    /* we are not in the chain until ESI is detected on a data callback */
    assert (thisNode->node.prev != NULL);
    assert (thisNode->node.next != NULL);

    ESIContext::Pointer context = dynamic_cast<ESIContext *>(thisNode->data.getRaw());
    assert (context.getRaw() != NULL);

    if (context->flags.passthrough)
        return clientStreamStatus (thisNode, http);

    if (context->flags.oktosend && context->flags.finished &&
            !(context->outbound.getRaw() && context->outbound_offset < context->outbound->len)) {
        debugs(86, 5, "Telling recipient EOF on STATUS");
        return STREAM_UNPLANNED_COMPLETE; /* we don't know lengths in advance */
    }

    /* ?? RC: we can't be aborted / fail ? */
    return STREAM_NONE;
}