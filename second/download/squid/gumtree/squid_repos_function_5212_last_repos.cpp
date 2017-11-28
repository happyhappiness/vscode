void
Client::handleRequestBodyProducerAborted()
{
    if (requestSender != NULL)
        debugs(9,3, HERE << "fyi: request body aborted while we were sending");

    fwd->dontRetry(true); // the problem is not with the server
    stopConsumingFrom(requestBodySource); // requestSender, if any, will notice

    // kids extend this
}