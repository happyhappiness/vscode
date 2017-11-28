static void
clientSocketRecipient(clientStreamNode * node, ClientHttpRequest * http,
                      HttpReply * rep, StoreIOBuffer receivedData)
{
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
    ClientSocketContext::Pointer context = dynamic_cast<ClientSocketContext *>(node->data.getRaw());
    assert(context != NULL);
    assert(connIsUsable(http->getConn()));

    /* TODO: check offset is what we asked for */

    if (context != http->getConn()->getCurrentContext()) {
        context->deferRecipientForLater(node, rep, receivedData);
        PROF_stop(clientSocketRecipient);
        return;
    }

    // After sending Transfer-Encoding: chunked (at least), always send
    // the last-chunk if there was no error, ignoring responseFinishedOrFailed.
    const bool mustSendLastChunk = http->request->flags.chunkedReply &&
                                   !http->request->flags.streamError && !context->startOfOutput();
    if (responseFinishedOrFailed(rep, receivedData) && !mustSendLastChunk) {
        context->writeComplete(context->clientConnection, NULL, 0, COMM_OK);
        PROF_stop(clientSocketRecipient);
        return;
    }

    if (!context->startOfOutput())
        context->sendBody(rep, receivedData);
    else {
        assert(rep);
        http->al->reply = HTTPMSGLOCK(rep);
        context->sendStartOfMessage(rep, receivedData);
    }

    PROF_stop(clientSocketRecipient);
}