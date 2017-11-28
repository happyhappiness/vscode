void clientReplyContext::setReplyToError(const HttpRequestMethod& method, ErrorState *errstate)
{
    if (errstate->httpStatus == HTTP_NOT_IMPLEMENTED && http->request)
        /* prevent confusion over whether we default to persistent or not */
        http->request->flags.proxyKeepalive = 0;

    http->al->http.code = errstate->httpStatus;

    if (http->request)
        http->request->ignoreRange("responding with a Squid-generated error");

    createStoreEntry(method, RequestFlags());
    assert(errstate->callback_data == NULL);
    errorAppendEntry(http->storeEntry(), errstate);
    /* Now the caller reads to get this */
}