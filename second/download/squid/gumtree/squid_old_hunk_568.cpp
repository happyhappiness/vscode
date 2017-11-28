HttpStateData::httpStateConnClosed(const CommCloseCbParams &params)
{
    debugs(11, 5, "httpStateFree: FD " << params.fd << ", httpState=" << params.data);
    mustStop("HttpStateData::httpStateConnClosed");
}

int
httpCachable(const HttpRequestMethod& method)
{
    /* GET and HEAD are cachable. Others are not. */

    // TODO: replase to HttpRequestMethod::isCachable() ?
    if (method != METHOD_GET && method != METHOD_HEAD)
        return 0;

    /* else cachable */
    return 1;
}

void
HttpStateData::httpTimeout(const CommTimeoutCbParams &params)
{
    debugs(11, 4, HERE << serverConnection << ": '" << entry->url() << "'" );

    if (entry->store_status == STORE_PENDING) {
        fwd->fail(new ErrorState(ERR_READ_TIMEOUT, HTTP_GATEWAY_TIMEOUT, fwd->request));
    }

    serverConnection->close();
}

static void
httpMaybeRemovePublic(StoreEntry * e, http_status status)
{
    int remove = 0;
    int forbidden = 0;
    StoreEntry *pe;

    if (!EBIT_TEST(e->flags, KEY_PRIVATE))
        return;

    switch (status) {

    case HTTP_OK:

    case HTTP_NON_AUTHORITATIVE_INFORMATION:

    case HTTP_MULTIPLE_CHOICES:

    case HTTP_MOVED_PERMANENTLY:

    case HTTP_MOVED_TEMPORARILY:

    case HTTP_GONE:

    case HTTP_NOT_FOUND:
        remove = 1;

        break;

    case HTTP_FORBIDDEN:

    case HTTP_METHOD_NOT_ALLOWED:
        forbidden = 1;

        break;

#if WORK_IN_PROGRESS

    case HTTP_UNAUTHORIZED:
        forbidden = 1;

        break;

#endif

