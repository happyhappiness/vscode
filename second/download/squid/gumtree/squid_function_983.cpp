ClientSocketContext *
parseHttpRequest(ConnStateData *csd, HttpParser *hp, HttpRequestMethod * method_p, Http::ProtocolVersion *http_ver)
{
    char *req_hdr = NULL;
    char *end;
    size_t req_sz;
    ClientHttpRequest *http;
    ClientSocketContext *result;
    StoreIOBuffer tempBuffer;
    int r;

    /* pre-set these values to make aborting simpler */
    *method_p = Http::METHOD_NONE;

    /* NP: don't be tempted to move this down or remove again.
     * It's the only DDoS protection old-String has against long URL */
    if ( hp->bufsiz <= 0) {
        debugs(33, 5, "Incomplete request, waiting for end of request line");
        return NULL;
    } else if ( (size_t)hp->bufsiz >= Config.maxRequestHeaderSize && headersEnd(hp->buf, Config.maxRequestHeaderSize) == 0) {
        debugs(33, 5, "parseHttpRequest: Too large request");
        hp->request_parse_status = Http::scHeaderTooLarge;
        return csd->abortRequestParsing("error:request-too-large");
    }

    /* Attempt to parse the first line; this'll define the method, url, version and header begin */
    r = HttpParserParseReqLine(hp);

    if (r == 0) {
        debugs(33, 5, "Incomplete request, waiting for end of request line");
        return NULL;
    }

    if (r == -1) {
        return csd->abortRequestParsing("error:invalid-request");
    }

    /* Request line is valid here .. */
    *http_ver = Http::ProtocolVersion(hp->req.v_maj, hp->req.v_min);

    /* This call scans the entire request, not just the headers */
    if (hp->req.v_maj > 0) {
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

    hp->hdr_start = hp->req.end + 1;

    /* Enforce max_request_size */
    if (req_sz >= Config.maxRequestHeaderSize) {
        debugs(33, 5, "parseHttpRequest: Too large request");
        hp->request_parse_status = Http::scHeaderTooLarge;
        return csd->abortRequestParsing("error:request-too-large");
    }

    /* Set method_p */
    *method_p = HttpRequestMethod(&hp->buf[hp->req.m_start], &hp->buf[hp->req.m_end]+1);

    /* deny CONNECT via accelerated ports */
    if (*method_p == Http::METHOD_CONNECT && csd->port != NULL && csd->port->flags.accelSurrogate) {
        debugs(33, DBG_IMPORTANT, "WARNING: CONNECT method received on " << csd->port->transport.protocol << " Accelerator port " << csd->port->s.port());
        /* XXX need a way to say "this many character length string" */
        debugs(33, DBG_IMPORTANT, "WARNING: for request: " << hp->buf);
        hp->request_parse_status = Http::scMethodNotAllowed;
        return csd->abortRequestParsing("error:method-not-allowed");
    }

    /* RFC 7540 section 11.6 registers the method PRI as HTTP/2 specific
     * Deny "PRI" method if used in HTTP/1.x or 0.9 versions.
     * If seen it signals a broken client or proxy has corrupted the traffic.
     */
    if (*method_p == Http::METHOD_PRI && *http_ver < Http::ProtocolVersion(2,0)) {
        debugs(33, DBG_IMPORTANT, "WARNING: PRI method received on " << csd->port->transport.protocol << "port " << csd->port->s.port());
        debugs(33, DBG_IMPORTANT, "WARNING: for request: " << hp->buf);
        hp->request_parse_status = Http::scMethodNotAllowed;
        return csd->abortRequestParsing("error:method-not-allowed");
    }

    if (*method_p == Http::METHOD_NONE) {
        /* XXX need a way to say "this many character length string" */
        debugs(33, DBG_IMPORTANT, "clientParseRequestMethod: Unsupported method in request '" << hp->buf << "'");
        hp->request_parse_status = Http::scMethodNotAllowed;
        return csd->abortRequestParsing("error:unsupported-request-method");
    }

    /*
     * Process headers after request line
     * TODO: Use httpRequestParse here.
     */
    /* XXX this code should be modified to take a const char * later! */
    req_hdr = (char *) hp->buf + hp->req.end + 1;

    debugs(33, 3, "parseHttpRequest: req_hdr = {" << req_hdr << "}");

    end = (char *) hp->buf + hp->hdr_end;

    debugs(33, 3, "parseHttpRequest: end = {" << end << "}");

    debugs(33, 3, "parseHttpRequest: prefix_sz = " <<
           (int) HttpParserRequestLen(hp) << ", req_line_sz = " <<
           HttpParserReqSz(hp));

    /* Ok, all headers are received */
    http = new ClientHttpRequest(csd);

    http->req_sz = HttpParserRequestLen(hp);
    result = new ClientSocketContext(csd->clientConnection, http);
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
    char *url = (char *)xmalloc(hp->req.u_end - hp->req.u_start + 16);

    memcpy(url, hp->buf + hp->req.u_start, hp->req.u_end - hp->req.u_start + 1);

    url[hp->req.u_end - hp->req.u_start + 1] = '\0';

#if THIS_VIOLATES_HTTP_SPECS_ON_URL_TRANSFORMATION

    if ((t = strchr(url, '#'))) /* remove HTML anchors */
        *t = '\0';

#endif

    debugs(33,5, "Prepare absolute URL from " <<
           (csd->transparent()?"intercept":(csd->port->flags.accelSurrogate ? "accel":"")));
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
     *  - remote interception with PROXY protocol
     *  - remote reverse-proxy with PROXY protocol
     */
    if (csd->transparent()) {
        /* intercept or transparent mode, properly working with no failures */
        prepareTransparentURL(csd, http, url, req_hdr);

    } else if (internalCheck(url)) {
        /* internal URL mode */
        /* prepend our name & port */
        http->uri = xstrdup(internalLocalUri(NULL, url));
        // We just re-wrote the URL. Must replace the Host: header.
        //  But have not parsed there yet!! flag for local-only handling.
        http->flags.internal = true;

    } else if (csd->port->flags.accelSurrogate || csd->switchedToHttps()) {
        /* accelerator mode */
        prepareAcceleratedURL(csd, http, url, req_hdr);
    }

    if (!http->uri) {
        /* No special rewrites have been applied above, use the
         * requested url. may be rewritten later, so make extra room */
        int url_sz = strlen(url) + Config.appendDomainLen + 5;
        http->uri = (char *)xcalloc(url_sz, 1);
        strcpy(http->uri, url);
    }

    debugs(33, 5, "parseHttpRequest: Complete request received");

    // XXX: crop this dump at the end of headers. No need for extras
    debugs(11, 2, "HTTP Client " << csd->clientConnection);
    debugs(11, 2, "HTTP Client REQUEST:\n---------\n" << (hp->buf) + hp->req.m_start << "\n----------");

    result->flags.parsed_ok = 1;
    xfree(url);
    return result;
}