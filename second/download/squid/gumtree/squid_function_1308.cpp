Http::Stream *
parseHttpRequest(ConnStateData *csd, const Http1::RequestParserPointer &hp)
{
    /* Attempt to parse the first line; this will define where the method, url, version and header begin */
    {
        const bool parsedOk = hp->parse(csd->inBuf);

        // sync the buffers after parsing.
        csd->inBuf = hp->remaining();

        if (hp->needsMoreData()) {
            debugs(33, 5, "Incomplete request, waiting for end of request line");
            return NULL;
        }

        if (csd->mayTunnelUnsupportedProto()) {
            csd->preservedClientData = hp->parsed();
            csd->preservedClientData.append(csd->inBuf);
        }

        if (!parsedOk) {
            const bool tooBig =
                hp->parseStatusCode == Http::scRequestHeaderFieldsTooLarge ||
                hp->parseStatusCode == Http::scUriTooLong;
            auto result = csd->abortRequestParsing(
                              tooBig ? "error:request-too-large" : "error:invalid-request");
            // assume that remaining leftovers belong to this bad request
            if (!csd->inBuf.isEmpty())
                csd->consumeInput(csd->inBuf.length());
            return result;
        }
    }

    /* We know the whole request is in parser now */
    debugs(11, 2, "HTTP Client " << csd->clientConnection);
    debugs(11, 2, "HTTP Client REQUEST:\n---------\n" <<
           hp->method() << " " << hp->requestUri() << " " << hp->messageProtocol() << "\n" <<
           hp->mimeHeader() <<
           "\n----------");

    /* deny CONNECT via accelerated ports */
    if (hp->method() == Http::METHOD_CONNECT && csd->port != NULL && csd->port->flags.accelSurrogate) {
        debugs(33, DBG_IMPORTANT, "WARNING: CONNECT method received on " << csd->transferProtocol << " Accelerator port " << csd->port->s.port());
        debugs(33, DBG_IMPORTANT, "WARNING: for request: " << hp->method() << " " << hp->requestUri() << " " << hp->messageProtocol());
        hp->parseStatusCode = Http::scMethodNotAllowed;
        return csd->abortRequestParsing("error:method-not-allowed");
    }

    /* RFC 7540 section 11.6 registers the method PRI as HTTP/2 specific
     * Deny "PRI" method if used in HTTP/1.x or 0.9 versions.
     * If seen it signals a broken client or proxy has corrupted the traffic.
     */
    if (hp->method() == Http::METHOD_PRI && hp->messageProtocol() < Http::ProtocolVersion(2,0)) {
        debugs(33, DBG_IMPORTANT, "WARNING: PRI method received on " << csd->transferProtocol << " port " << csd->port->s.port());
        debugs(33, DBG_IMPORTANT, "WARNING: for request: " << hp->method() << " " << hp->requestUri() << " " << hp->messageProtocol());
        hp->parseStatusCode = Http::scMethodNotAllowed;
        return csd->abortRequestParsing("error:method-not-allowed");
    }

    if (hp->method() == Http::METHOD_NONE) {
        debugs(33, DBG_IMPORTANT, "WARNING: Unsupported method: " << hp->method() << " " << hp->requestUri() << " " << hp->messageProtocol());
        hp->parseStatusCode = Http::scMethodNotAllowed;
        return csd->abortRequestParsing("error:unsupported-request-method");
    }

    // Process headers after request line
    debugs(33, 3, "complete request received. " <<
           "prefix_sz = " << hp->messageHeaderSize() <<
           ", request-line-size=" << hp->firstLineSize() <<
           ", mime-header-size=" << hp->headerBlockSize() <<
           ", mime header block:\n" << hp->mimeHeader() << "\n----------");

    /* Ok, all headers are received */
    ClientHttpRequest *http = new ClientHttpRequest(csd);

    http->req_sz = hp->messageHeaderSize();
    Http::Stream *result = new Http::Stream(csd->clientConnection, http);

    StoreIOBuffer tempBuffer;
    tempBuffer.data = result->reqbuf;
    tempBuffer.length = HTTP_REQBUF_SZ;

    ClientStreamData newServer = new clientReplyContext(http);
    ClientStreamData newClient = result;
    clientStreamInit(&http->client_stream, clientGetMoreData, clientReplyDetach,
                     clientReplyStatus, newServer, clientSocketRecipient,
                     clientSocketDetach, newClient, tempBuffer);

    /* set url */
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
     *  - internal relative-URL
     *  - mixed combos of the above with internal URL
     *  - remote interception with PROXY protocol
     *  - remote reverse-proxy with PROXY protocol
     */
    if (csd->transparent()) {
        /* intercept or transparent mode, properly working with no failures */
        prepareTransparentURL(csd, http, hp);

    } else if (internalCheck(hp->requestUri())) { // NP: only matches relative-URI
        /* internal URL mode */
        /* prepend our name & port */
        http->uri = xstrdup(internalLocalUri(NULL, hp->requestUri()));
        // We just re-wrote the URL. Must replace the Host: header.
        //  But have not parsed there yet!! flag for local-only handling.
        http->flags.internal = true;

    } else if (csd->port->flags.accelSurrogate || csd->switchedToHttps()) {
        /* accelerator mode */
        prepareAcceleratedURL(csd, http, hp);
    }

    if (!http->uri) {
        /* No special rewrites have been applied above, use the
         * requested url. may be rewritten later, so make extra room */
        int url_sz = hp->requestUri().length() + Config.appendDomainLen + 5;
        http->uri = (char *)xcalloc(url_sz, 1);
        SBufToCstring(http->uri, hp->requestUri());
    }

    result->flags.parsed_ok = 1;
    return result;
}