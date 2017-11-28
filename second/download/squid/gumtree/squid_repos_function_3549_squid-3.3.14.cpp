static void
clientProcessRequest(ConnStateData *conn, HttpParser *hp, ClientSocketContext *context, const HttpRequestMethod& method, HttpVersion http_ver)
{
    ClientHttpRequest *http = context->http;
    HttpRequest::Pointer request;
    bool notedUseOfBuffer = false;
    bool chunked = false;
    bool mustReplyToOptions = false;
    bool unsupportedTe = false;
    bool expectBody = false;

    /* We have an initial client stream in place should it be needed */
    /* setup our private context */
    context->registerWithConn();

    if (context->flags.parsed_ok == 0) {
        clientStreamNode *node = context->getClientReplyContext();
        debugs(33, 2, "clientProcessRequest: Invalid Request");
        conn->quitAfterError(NULL);
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri,  true);
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        switch (hp->request_parse_status) {
        case HTTP_HEADER_TOO_LARGE:
            repContext->setReplyToError(ERR_TOO_BIG, HTTP_BAD_REQUEST, method, http->uri, conn->clientConnection->remote, NULL, conn->in.buf, NULL);
            break;
        case HTTP_METHOD_NOT_ALLOWED:
            repContext->setReplyToError(ERR_UNSUP_REQ, HTTP_METHOD_NOT_ALLOWED, method, http->uri,
                                        conn->clientConnection->remote, NULL, conn->in.buf, NULL);
            break;
        default:
            repContext->setReplyToError(ERR_INVALID_REQ, hp->request_parse_status, method, http->uri,
                                        conn->clientConnection->remote, NULL, conn->in.buf, NULL);
        }
        assert(context->http->out.offset == 0);
        context->pullData();
        goto finish;
    }

    if ((request = HttpRequest::CreateFromUrlAndMethod(http->uri, method)) == NULL) {
        clientStreamNode *node = context->getClientReplyContext();
        debugs(33, 5, "Invalid URL: " << http->uri);
        conn->quitAfterError(request);
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri,  true);
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_INVALID_URL, HTTP_BAD_REQUEST, method, http->uri, conn->clientConnection->remote, NULL, NULL, NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        goto finish;
    }

    /* RFC 2616 section 10.5.6 : handle unsupported HTTP major versions cleanly. */
    /* We currently only support 0.9, 1.0, 1.1 properly */
    if ( (http_ver.major == 0 && http_ver.minor != 9) ||
            (http_ver.major > 1) ) {

        clientStreamNode *node = context->getClientReplyContext();
        debugs(33, 5, "Unsupported HTTP version discovered. :\n" << HttpParserHdrBuf(hp));
        conn->quitAfterError(request);
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri,  true);
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_UNSUP_HTTPVERSION, HTTP_HTTP_VERSION_NOT_SUPPORTED, method, http->uri,
                                    conn->clientConnection->remote, NULL, HttpParserHdrBuf(hp), NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        goto finish;
    }

    /* compile headers */
    /* we should skip request line! */
    /* XXX should actually know the damned buffer size here */
    if (http_ver.major >= 1 && !request->parseHeader(HttpParserHdrBuf(hp), HttpParserHdrSz(hp))) {
        clientStreamNode *node = context->getClientReplyContext();
        debugs(33, 5, "Failed to parse request headers:\n" << HttpParserHdrBuf(hp));
        conn->quitAfterError(request);
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri,  true);
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_INVALID_REQ, HTTP_BAD_REQUEST, method, http->uri, conn->clientConnection->remote, NULL, NULL, NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        goto finish;
    }

    request->clientConnectionManager = conn;

    request->flags.accelerated = http->flags.accel;
    request->flags.sslBumped=conn->switchedToHttps();
    request->flags.ignoreCc = conn->port->ignore_cc;
    // TODO: decouple http->flags.accel from request->flags.sslBumped
    request->flags.noDirect = (request->flags.accelerated && !request->flags.sslBumped) ?
                              !conn->port->allow_direct : 0;
#if USE_AUTH
    if (request->flags.sslBumped) {
        if (conn->auth_user_request != NULL)
            request->auth_user_request = conn->auth_user_request;
    }
#endif

    /** \par
     * If transparent or interception mode is working clone the transparent and interception flags
     * from the port settings to the request.
     */
    if (http->clientConnection != NULL) {
        request->flags.intercepted = ((http->clientConnection->flags & COMM_INTERCEPTION) != 0);
        request->flags.spoofClientIp = ((http->clientConnection->flags & COMM_TRANSPARENT) != 0 ) ;
    }

    if (internalCheck(request->urlpath.termedBuf())) {
        if (internalHostnameIs(request->GetHost()) &&
                request->port == getMyPort()) {
            http->flags.internal = 1;
        } else if (Config.onoff.global_internal_static && internalStaticCheck(request->urlpath.termedBuf())) {
            request->SetHost(internalHostname());
            request->port = getMyPort();
            http->flags.internal = 1;
        }
    }

    if (http->flags.internal) {
        request->protocol = AnyP::PROTO_HTTP;
        request->login[0] = '\0';
    }

    request->flags.internal = http->flags.internal;
    setLogUri (http, urlCanonicalClean(request));
    request->client_addr = conn->clientConnection->remote; // XXX: remove reuest->client_addr member.
#if FOLLOW_X_FORWARDED_FOR
    // indirect client gets stored here because it is an HTTP header result (from X-Forwarded-For:)
    // not a details about teh TCP connection itself
    request->indirect_client_addr = conn->clientConnection->remote;
#endif /* FOLLOW_X_FORWARDED_FOR */
    request->my_addr = conn->clientConnection->local;
    request->myportname = conn->port->name;
    request->http_ver = http_ver;

    // Link this HttpRequest to ConnStateData relatively early so the following complex handling can use it
    // TODO: this effectively obsoletes a lot of conn->FOO copying. That needs cleaning up later.
    request->clientConnectionManager = conn;

    if (request->header.chunked()) {
        chunked = true;
    } else if (request->header.has(HDR_TRANSFER_ENCODING)) {
        const String te = request->header.getList(HDR_TRANSFER_ENCODING);
        // HTTP/1.1 requires chunking to be the last encoding if there is one
        unsupportedTe = te.size() && te != "identity";
    } // else implied identity coding

    mustReplyToOptions = (method == METHOD_OPTIONS) &&
                         (request->header.getInt64(HDR_MAX_FORWARDS) == 0);
    if (!urlCheckRequest(request) || mustReplyToOptions || unsupportedTe) {
        clientStreamNode *node = context->getClientReplyContext();
        conn->quitAfterError(request);
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_UNSUP_REQ, HTTP_NOT_IMPLEMENTED, request->method, NULL,
                                    conn->clientConnection->remote, request, NULL, NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        goto finish;
    }

    if (!chunked && !clientIsContentLengthValid(request)) {
        clientStreamNode *node = context->getClientReplyContext();
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        conn->quitAfterError(request);
        repContext->setReplyToError(ERR_INVALID_REQ,
                                    HTTP_LENGTH_REQUIRED, request->method, NULL,
                                    conn->clientConnection->remote, request, NULL, NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        goto finish;
    }

    if (request->header.has(HDR_EXPECT)) {
        const String expect = request->header.getList(HDR_EXPECT);
        const bool supportedExpect = (expect.caseCmp("100-continue") == 0);
        if (!supportedExpect) {
            clientStreamNode *node = context->getClientReplyContext();
            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
            assert (repContext);
            conn->quitAfterError(request);
            repContext->setReplyToError(ERR_INVALID_REQ, HTTP_EXPECTATION_FAILED, request->method, http->uri,
                                        conn->clientConnection->remote, request, NULL, NULL);
            assert(context->http->out.offset == 0);
            context->pullData();
            goto finish;
        }
    }

    http->request = HTTPMSGLOCK(request);
    clientSetKeepaliveFlag(http);

    // Let tunneling code be fully responsible for CONNECT requests
    if (http->request->method == METHOD_CONNECT) {
        context->mayUseConnection(true);
        conn->flags.readMore = false;
    }

#if USE_SSL
    if (conn->switchedToHttps() && conn->serveDelayedError(context))
        goto finish;
#endif

    /* Do we expect a request-body? */
    expectBody = chunked || request->content_length > 0;
    if (!context->mayUseConnection() && expectBody) {
        request->body_pipe = conn->expectRequestBody(
                                 chunked ? -1 : request->content_length);

        // consume header early so that body pipe gets just the body
        connNoteUseOfBuffer(conn, http->req_sz);
        notedUseOfBuffer = true;

        /* Is it too large? */
        if (!chunked && // if chunked, we will check as we accumulate
                clientIsRequestBodyTooLargeForPolicy(request->content_length)) {
            clientStreamNode *node = context->getClientReplyContext();
            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
            assert (repContext);
            conn->quitAfterError(request);
            repContext->setReplyToError(ERR_TOO_BIG,
                                        HTTP_REQUEST_ENTITY_TOO_LARGE, METHOD_NONE, NULL,
                                        conn->clientConnection->remote, http->request, NULL, NULL);
            assert(context->http->out.offset == 0);
            context->pullData();
            goto finish;
        }

        // We may stop producing, comm_close, and/or call setReplyToError()
        // below, so quit on errors to avoid http->doCallouts()
        if (!conn->handleRequestBodyData())
            goto finish;

        if (!request->body_pipe->productionEnded()) {
            debugs(33, 5, HERE << "need more request body");
            context->mayUseConnection(true);
            assert(conn->flags.readMore);
        }
    }

    http->calloutContext = new ClientRequestContext(http);

    http->doCallouts();

finish:
    if (!notedUseOfBuffer)
        connNoteUseOfBuffer(conn, http->req_sz);

    /*
     * DPW 2007-05-18
     * Moved the TCP_RESET feature from clientReplyContext::sendMoreData
     * to here because calling comm_reset_close() causes http to
     * be freed and the above connNoteUseOfBuffer() would hit an
     * assertion, not to mention that we were accessing freed memory.
     */
    if (request && request->flags.resetTcp && Comm::IsConnOpen(conn->clientConnection)) {
        debugs(33, 3, HERE << "Sending TCP RST on " << conn->clientConnection);
        conn->flags.readMore = false;
        comm_reset_close(conn->clientConnection);
    }
}