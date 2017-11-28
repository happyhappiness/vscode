int
clientBeginRequest(const HttpRequestMethod& method, char const *url, CSCB * streamcallback,
                   CSD * streamdetach, ClientStreamData streamdata, HttpHeader const *header,
                   char *tailbuf, size_t taillen)
{
    size_t url_sz;
    ClientHttpRequest *http = new ClientHttpRequest(NULL);
    HttpRequest *request;
    StoreIOBuffer tempBuffer;
    if (http->al != NULL)
        http->al->cache.start_time = current_time;
    /* this is only used to adjust the connection offset in client_side.c */
    http->req_sz = 0;
    tempBuffer.length = taillen;
    tempBuffer.data = tailbuf;
    /* client stream setup */
    clientStreamInit(&http->client_stream, clientGetMoreData, clientReplyDetach,
                     clientReplyStatus, new clientReplyContext(http), streamcallback,
                     streamdetach, streamdata, tempBuffer);
    /* make it visible in the 'current acctive requests list' */
    /* Set flags */
    /* internal requests only makes sense in an
     * accelerator today. TODO: accept flags ? */
    http->flags.accel = true;
    /* allow size for url rewriting */
    url_sz = strlen(url) + Config.appendDomainLen + 5;
    http->uri = (char *)xcalloc(url_sz, 1);
    strcpy(http->uri, url);

    if ((request = HttpRequest::CreateFromUrlAndMethod(http->uri, method)) == NULL) {
        debugs(85, 5, "Invalid URL: " << http->uri);
        return -1;
    }

    /*
     * now update the headers in request with our supplied headers. urlParse
     * should return a blank header set, but we use Update to be sure of
     * correctness.
     */
    if (header)
        request->header.update(header);

    http->log_uri = xstrdup(urlCanonicalClean(request));

    /* http struct now ready */

    /*
     * build new header list *? TODO
     */
    request->flags.accelerated = http->flags.accel;

    request->flags.internalClient = true;

    /* this is an internally created
     * request, not subject to acceleration
     * target overrides */
    /*
     * FIXME? Do we want to detect and handle internal requests of internal
     * objects ?
     */

    /* Internally created requests cannot have bodies today */
    request->content_length = 0;

    request->client_addr.setNoAddr();

#if FOLLOW_X_FORWARDED_FOR
    request->indirect_client_addr.setNoAddr();
#endif /* FOLLOW_X_FORWARDED_FOR */

    request->my_addr.setNoAddr();   /* undefined for internal requests */

    request->my_addr.port(0);

    /* Our version is HTTP/1.1 */
    request->http_ver = Http::ProtocolVersion(1,1);

    http->request = request;
    HTTPMSGLOCK(http->request);

    /* optional - skip the access check ? */
    http->calloutContext = new ClientRequestContext(http);

    http->calloutContext->http_access_done = false;

    http->calloutContext->redirect_done = true;

    http->calloutContext->no_cache_done = true;

    http->doCallouts();

    return 0;
}