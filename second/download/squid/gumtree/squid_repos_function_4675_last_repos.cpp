void
Http::One::Server::handleReply(HttpReply *rep, StoreIOBuffer receivedData)
{
    // the caller guarantees that we are dealing with the current context only
    Http::StreamPointer context = pipeline.front();
    Must(context != nullptr);
    const ClientHttpRequest *http = context->http;
    Must(http != NULL);

    // After sending Transfer-Encoding: chunked (at least), always send
    // the last-chunk if there was no error, ignoring responseFinishedOrFailed.
    const bool mustSendLastChunk = http->request->flags.chunkedReply &&
                                   !http->request->flags.streamError &&
                                   !EBIT_TEST(http->storeEntry()->flags, ENTRY_BAD_LENGTH) &&
                                   !context->startOfOutput();
    const bool responseFinishedOrFailed = !rep &&
                                          !receivedData.data &&
                                          !receivedData.length;
    if (responseFinishedOrFailed && !mustSendLastChunk) {
        context->writeComplete(0);
        return;
    }

    if (!context->startOfOutput()) {
        context->sendBody(receivedData);
        return;
    }

    assert(rep);
    http->al->reply = rep;
    HTTPMSGLOCK(http->al->reply);
    context->sendStartOfMessage(rep, receivedData);
}