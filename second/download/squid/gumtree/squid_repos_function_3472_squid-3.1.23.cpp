static ClientSocketContext *
parseHttpRequest(ConnStateData *conn, HttpParser *hp, HttpRequestMethod * method_p, HttpVersion *http_ver)
{
    char *req_hdr = NULL;
    char *end;
    size_t req_sz;
    ClientHttpRequest *http;
    ClientSocketContext *result;
    StoreIOBuffer tempBuffer;
    int r;

    /* pre-set these values to make aborting simpler */
    *method_p = METHOD_NONE;

    /* NP: don't be tempted to move this down or remove again.
     * It's the only DDoS protection old-String has against long URL */
    if ( hp->bufsiz <= 0) {
        debugs(33, 5, "Incomplete request, waiting for end of request line");
        return NULL;
    } else if ( (size_t)hp->bufsiz >= Config.maxRequestHeaderSize && headersEnd(hp->buf, Config.maxRequestHeaderSize) == 0) {
        debugs(33, 5, "parseHttpRequest: Too large request");
        return parseHttpRequestAbort(conn, "error:request-too-large");
    }

    /* Attempt to parse the first line; this'll define the method, url, version and header begin */
    r = HttpParserParseReqLine(hp);

    if (r == 0) {
        debugs(33, 5, "Incomplete request, waiting for end of request line");
        return NULL;
    }

    if (r == -1) {
        return parseHttpRequestAbort(conn, "error:invalid-request");
    }

    /* Request line is valid here .. */
    *http_ver = HttpVersion(hp->v_maj, hp->v_min);

    /* This call scans the entire request, not just the headers */
    if (hp->v_maj > 0) {
        if ((req_sz = headersEnd(hp->buf, hp->bufsiz)) == 0) {
            debugs(33, 5, "Incomplete request, waiting for end of headers");
            return NULL;
        }
    } else {
        debugs(33, 3, "parseHttpRequest: Missing HTTP identifier");
        req_sz = HttpParserReqSz(hp);
    }

    /* We know the whole request is in hp->buf now */

    assert(req_sz <= (size_t) hp->bufsiz);

    /* Will the following be true with HTTP/0.9 requests? probably not .. */
    /* So the rest of the code will need to deal with '0'-byte headers (ie, none, so don't try parsing em) */
    assert(req_sz > 0);

    hp->hdr_end = req_sz - 1;

    hp->hdr_start = hp->req_end + 1;

    /* Enforce max_request_size */
    if (req_sz >= Config.maxRequestHeaderSize) {
        debugs(33, 5, "parseHttpRequest: Too large request");
        return parseHttpRequestAbort(conn, "error:request-too-large");
    }

    /* Set method_p */
    *method_p = HttpRequestMethod(&hp->buf[hp->m_start], &hp->buf[hp->m_end]+1);

    /* deny CONNECT via accelerated ports */
    if (*method_p == METHOD_CONNECT && conn && conn->port && conn->port->accel) {
        debugs(33, DBG_IMPORTANT, "WARNING: CONNECT method received on " << conn->port->protocol << " Accelerator port " << conn->port->s.GetPort() );
        /* XXX need a way to say "this many character length string" */
        debugs(33, DBG_IMPORTANT, "WARNING: for request: " << hp->buf);
        /* XXX need some way to set 405 status on the error reply */
        return parseHttpRequestAbort(conn, "error:method-not-allowed");
    }

    if (*method_p == METHOD_NONE) {
        /* XXX need a way to say "this many character length string" */
        debugs(33, 1, "clientParseRequestMethod: Unsupported method in request '" << hp->buf << "'");

        /* XXX where's the method set for this error? */
        return parseHttpRequestAbort(conn, "error:unsupported-request-method");
    }

    /*
     * Process headers after request line
     * TODO: Use httpRequestParse here.
     */
    /* XXX this code should be modified to take a const char * later! */
    req_hdr = (char *) hp->buf + hp->req_end + 1;

    debugs(33, 3, "parseHttpRequest: req_hdr = {" << req_hdr << "}");

    end = (char *) hp->buf + hp->hdr_end;

    debugs(33, 3, "parseHttpRequest: end = {" << end << "}");

    /*
     * Check that the headers don't have double-CR.
     * NP: strnstr is required so we don't search any possible binary body blobs.
     */
    if ( squid_strnstr(req_hdr, "\r\r\n", req_sz) ) {
        debugs(33, 1, "WARNING: suspicious HTTP request contains double CR");
        return parseHttpRequestAbort(conn, "error:double-CR");
    }

    debugs(33, 3, "parseHttpRequest: prefix_sz = " <<
           (int) HttpParserRequestLen(hp) << ", req_line_sz = " <<
           HttpParserReqSz(hp));

    // Temporary hack: We might receive a chunked body from a broken HTTP/1.1
    // client that sends chunked requests to HTTP/1.0 Squid. If the request
    // might have a chunked body, parse the headers early to look for the
    // "Transfer-Encoding: chunked" header. If we find it, wait until the
    // entire body is available so that we can set the content length and
    // forward the request without chunks. The primary reason for this is
    // to avoid forwarding a chunked request because the server side lacks
    // logic to determine when it is valid to do so.
    // FUTURE_CODE_TO_SUPPORT_CHUNKED_REQUESTS below will replace this hack.
    if (hp->v_min == 1 && hp->v_maj == 1 && // broken client, may send chunks
            Config.maxChunkedRequestBodySize > 0 && // configured to dechunk
            (*method_p == METHOD_PUT || *method_p == METHOD_POST)) {

        // check only once per request because isChunkedRequest is expensive
        if (conn->in.dechunkingState == ConnStateData::chunkUnknown) {
            if (isChunkedRequest(hp))
                conn->startDechunkingRequest(hp);
            else
                conn->in.dechunkingState = ConnStateData::chunkNone;
        }

        if (conn->in.dechunkingState == ConnStateData::chunkParsing) {
            if (conn->parseRequestChunks(hp)) // parses newly read chunks
                return NULL; // wait for more data
            debugs(33, 5, HERE << "Got complete chunked request or err.");
            assert(conn->in.dechunkingState != ConnStateData::chunkParsing);
        }
    }

    /* Ok, all headers are received */
    http = new ClientHttpRequest(conn);

    http->req_sz = HttpParserRequestLen(hp);
    result = ClientSocketContextNew(http);
    tempBuffer.data = result->reqbuf;
    tempBuffer.length = HTTP_REQBUF_SZ;

    ClientStreamData newServer = new clientReplyContext(http);
    ClientStreamData newClient = result;
    clientStreamInit(&http->client_stream, clientGetMoreData, clientReplyDetach,
                     clientReplyStatus, newServer, clientSocketRecipient,
                     clientSocketDetach, newClient, tempBuffer);

    debugs(33, 5, "parseHttpRequest: Request Header is\n" <<(hp->buf) + hp->hdr_start);

    /* set url */
    /*
     * XXX this should eventually not use a malloc'ed buffer; the transformation code
     * below needs to be modified to not expect a mutable nul-terminated string.
     */
    char *url = (char *)xmalloc(hp->u_end - hp->u_start + 16);

    memcpy(url, hp->buf + hp->u_start, hp->u_end - hp->u_start + 1);

    url[hp->u_end - hp->u_start + 1] = '\0';

#if THIS_VIOLATES_HTTP_SPECS_ON_URL_TRANSFORMATION

    if ((t = strchr(url, '#')))	/* remove HTML anchors */
        *t = '\0';

#endif

    debugs(33,5, HERE << "repare absolute URL from " << (conn->transparent()?"intercept":(conn->port->accel ? "accel":"")));
    /* Rewrite the URL in transparent or accelerator mode */
    /* NP: there are several cases to traverse here:
     *  - standard mode (forward proxy)
     *  - transparent mode (TPROXY)
     *  - transparent mode with failures
     *  - intercept mode (NAT)
     *  - intercept mode with failures
     *  - accelerator mode (reverse proxy)
     *  - internal URL
     *  - mixed combos of the above with internal URL
     */
    if (conn->transparent()) {
        /* intercept or transparent mode, properly working with no failures */
        http->flags.intercepted = conn->port->intercepted;
        http->flags.spoof_client_ip = conn->port->spoof_client_ip;
        prepareTransparentURL(conn, http, url, req_hdr);

    } else if (conn->port->intercepted || conn->port->spoof_client_ip) {
        /* transparent or intercept mode with failures */
        prepareTransparentURL(conn, http, url, req_hdr);

    } else if (conn->port->accel || conn->switchedToHttps()) {
        /* accelerator mode */
        prepareAcceleratedURL(conn, http, url, req_hdr);

    } else if (internalCheck(url)) {
        /* internal URL mode */
        /* prepend our name & port */
        http->uri = xstrdup(internalLocalUri(NULL, url));
        http->flags.accel = 1;
    }

    if (!http->uri) {
        /* No special rewrites have been applied above, use the
         * requested url. may be rewritten later, so make extra room */
        int url_sz = strlen(url) + Config.appendDomainLen + 5;
        http->uri = (char *)xcalloc(url_sz, 1);
        strcpy(http->uri, url);
    }

    debugs(33, 5, "parseHttpRequest: Complete request received");
    result->flags.parsed_ok = 1;
    xfree(url);
    return result;
}