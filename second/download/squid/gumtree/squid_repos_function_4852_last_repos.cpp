void
Http::Stream::deferRecipientForLater(clientStreamNode *node, HttpReply *rep, StoreIOBuffer receivedData)
{
    debugs(33, 2, "Deferring request " << http->uri);
    assert(flags.deferred == 0);
    flags.deferred = 1;
    deferredparams.node = node;
    deferredparams.rep = rep;
    deferredparams.queuedBuffer = receivedData;
}