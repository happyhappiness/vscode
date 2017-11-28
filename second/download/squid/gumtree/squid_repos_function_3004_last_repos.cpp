void
clientSocketRecipient(clientStreamNode * node, ClientHttpRequest * http,
                      HttpReply * rep, StoreIOBuffer receivedData)
{
    // dont tryt to deliver if client already ABORTED
    if (!http->getConn() || !cbdataReferenceValid(http->getConn()) || !Comm::IsConnOpen(http->getConn()->clientConnection))
        return;

    /* Test preconditions */
    assert(node != NULL);
    PROF_start(clientSocketRecipient);
    /* TODO: handle this rather than asserting
     * - it should only ever happen if we cause an abort and
     * the callback chain loops back to here, so we can simply return.
     * However, that itself shouldn't happen, so it stays as an assert for now.
     */
    assert(cbdataReferenceValid(node));
    assert(node->node.next == NULL);
    Http::StreamPointer context = dynamic_cast<Http::Stream *>(node->data.getRaw());
    assert(context != NULL);

    /* TODO: check offset is what we asked for */

    // TODO: enforces HTTP/1 MUST on pipeline order, but is irrelevant to HTTP/2
    if (context != http->getConn()->pipeline.front())
        context->deferRecipientForLater(node, rep, receivedData);
    else if (http->getConn()->cbControlMsgSent) // 1xx to the user is pending
        context->deferRecipientForLater(node, rep, receivedData);
    else
        http->getConn()->handleReply(rep, receivedData);

    PROF_stop(clientSocketRecipient);
}