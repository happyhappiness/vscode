void
clientReplyContext::sendStreamError(StoreIOBuffer const &result)
{
    /** call clientWriteComplete so the client socket gets closed
     *
     * We call into the stream, because we don't know that there is a
     * client socket!
     */
    debugs(88, 5, "clientReplyContext::sendStreamError: A stream error has occured, marking as complete and sending no data.");
    StoreIOBuffer localTempBuffer;
    flags.complete = 1;
    localTempBuffer.flags.error = result.flags.error;
    clientStreamCallback((clientStreamNode*)http->client_stream.head->data, http, NULL,
                         localTempBuffer);
}