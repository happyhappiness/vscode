void
clientReplyContext::setReplyToReply(HttpReply *futureReply)
{
    Must(futureReply);
    http->al->http.code = futureReply->sline.status();

    HttpRequestMethod method;
    if (http->request) { // nil on responses to unparsable requests
        http->request->ignoreRange("responding with a Squid-generated reply");
        method = http->request->method;
    }

    createStoreEntry(method, RequestFlags());

    http->storeEntry()->storeErrorResponse(futureReply);
    /* Now the caller reads to get futureReply */
}