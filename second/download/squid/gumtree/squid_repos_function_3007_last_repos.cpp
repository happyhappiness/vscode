static void
ClientSocketContextPushDeferredIfNeeded(Http::StreamPointer deferredRequest, ConnStateData * conn)
{
    debugs(33, 2, HERE << conn->clientConnection << " Sending next");

    /** If the client stream is waiting on a socket write to occur, then */

    if (deferredRequest->flags.deferred) {
        /** NO data is allowed to have been sent. */
        assert(deferredRequest->http->out.size == 0);
        /** defer now. */
        clientSocketRecipient(deferredRequest->deferredparams.node,
                              deferredRequest->http,
                              deferredRequest->deferredparams.rep,
                              deferredRequest->deferredparams.queuedBuffer);
    }

    /** otherwise, the request is still active in a callbacksomewhere,
     * and we are done
     */
}