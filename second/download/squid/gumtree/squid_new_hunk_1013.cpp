                host = thost;
            } else if (!t) {
                snprintf(thost, sizeof(thost), "%s:%d",host, vport);
                host = thost;
            }
        } // else nothing to alter port-wise.
        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen + strlen(host);
        http->uri = (char *)xcalloc(url_sz, 1);
        const SBuf &scheme = AnyP::UriScheme(conn->transferProtocol.protocol).image();
        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s" SQUIDSBUFPH, SQUIDSBUFPRINT(scheme), host, SQUIDSBUFPRINT(url));
        debugs(33, 5, "ACCEL VHOST REWRITE: " << http->uri);
    } else if (conn->port->defaultsite /* && !vhost */) {
        debugs(33, 5, "ACCEL DEFAULTSITE REWRITE: defaultsite=" << conn->port->defaultsite << " + vport=" << vport);
        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen +
                           strlen(conn->port->defaultsite);
        http->uri = (char *)xcalloc(url_sz, 1);
        char vportStr[32];
        vportStr[0] = '\0';
        if (vport > 0) {
            snprintf(vportStr, sizeof(vportStr),":%d",vport);
        }
        const SBuf &scheme = AnyP::UriScheme(conn->transferProtocol.protocol).image();
        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s%s" SQUIDSBUFPH,
                 SQUIDSBUFPRINT(scheme), conn->port->defaultsite, vportStr, SQUIDSBUFPRINT(url));
        debugs(33, 5, "ACCEL DEFAULTSITE REWRITE: " << http->uri);
    } else if (vport > 0 /* && (!vhost || no Host:) */) {
        debugs(33, 5, "ACCEL VPORT REWRITE: *_port IP + vport=" << vport);
        /* Put the local socket IP address as the hostname, with whatever vport we found  */
        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen;
        http->uri = (char *)xcalloc(url_sz, 1);
        http->getConn()->clientConnection->local.toHostStr(ipbuf,MAX_IPSTRLEN);
        const SBuf &scheme = AnyP::UriScheme(conn->transferProtocol.protocol).image();
        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s:%d" SQUIDSBUFPH,
                 SQUIDSBUFPRINT(scheme), ipbuf, vport, SQUIDSBUFPRINT(url));
        debugs(33, 5, "ACCEL VPORT REWRITE: " << http->uri);
    }
}

static void
prepareTransparentURL(ConnStateData * conn, ClientHttpRequest *http, const Http1::RequestParserPointer &hp)
{
    // TODO Must() on URI !empty when the parser supports throw. For now avoid assert().
    if (!hp->requestUri().isEmpty() && hp->requestUri()[0] != '/')
        return; /* already in good shape */

    /* BUG: Squid cannot deal with '*' URLs (RFC2616 5.1.2) */

    if (const char *host = hp->getHeaderField("Host")) {
        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen +
                           strlen(host);
        http->uri = (char *)xcalloc(url_sz, 1);
        const SBuf &scheme = AnyP::UriScheme(conn->transferProtocol.protocol).image();
        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s" SQUIDSBUFPH,
                 SQUIDSBUFPRINT(scheme), host, SQUIDSBUFPRINT(hp->requestUri()));
        debugs(33, 5, "TRANSPARENT HOST REWRITE: " << http->uri);
    } else {
        /* Put the local socket IP address as the hostname.  */
        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen;
        http->uri = (char *)xcalloc(url_sz, 1);
        static char ipbuf[MAX_IPSTRLEN];
        http->getConn()->clientConnection->local.toHostStr(ipbuf,MAX_IPSTRLEN);
        const SBuf &scheme = AnyP::UriScheme(http->getConn()->transferProtocol.protocol).image();
        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s:%d" SQUIDSBUFPH,
                 SQUIDSBUFPRINT(scheme),
                 ipbuf, http->getConn()->clientConnection->local.port(), SQUIDSBUFPRINT(hp->requestUri()));
        debugs(33, 5, "TRANSPARENT REWRITE: " << http->uri);
    }
}

/** Parse an HTTP request
 *
 *  \note Sets result->flags.parsed_ok to 0 if failed to parse the request,
 *          to 1 if the request was correctly parsed.
 *  \param[in] csd a ConnStateData. The caller must make sure it is not null
 *  \param[in] hp an Http1::RequestParser
 *  \param[out] mehtod_p will be set as a side-effect of the parsing.
 *          Pointed-to value will be set to Http::METHOD_NONE in case of
 *          parsing failure
 *  \param[out] http_ver will be set as a side-effect of the parsing
 *  \return NULL on incomplete requests,
 *          a Http::Stream on success or failure.
 */
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

bool
ConnStateData::connFinishedWithConn(int size)
{
    if (size == 0) {
        if (pipeline.empty() && inBuf.isEmpty()) {
            /* no current or pending requests */
            debugs(33, 4, HERE << clientConnection << " closed");
            return true;
        } else if (!Config.onoff.half_closed_clients) {
            /* admin doesn't want to support half-closed client sockets */
            debugs(33, 3, HERE << clientConnection << " aborted (half_closed_clients disabled)");
            pipeline.terminateAll(0);
            return true;
        }
    }

    return false;
}

void
ConnStateData::consumeInput(const size_t byteCount)
{
    assert(byteCount > 0 && byteCount <= inBuf.length());
    inBuf.consume(byteCount);
    debugs(33, 5, "inBuf has " << inBuf.length() << " unused bytes");
}

void
ConnStateData::clientAfterReadingRequests()
{
    // Were we expecting to read more request body from half-closed connection?
