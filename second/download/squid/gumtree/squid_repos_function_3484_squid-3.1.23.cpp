static void
clientProcessRequest(ConnStateData *conn, HttpParser *hp, ClientSocketContext *context, const HttpRequestMethod& method, HttpVersion http_ver)
{
    ClientHttpRequest *http = context->http;
    HttpRequest *request = NULL;
    bool notedUseOfBuffer = false;
    bool tePresent = false;
    bool deChunked = false;
    bool mustReplyToOptions = false;
    bool unsupportedTe = false;

    /* We have an initial client stream in place should it be needed */
    /* setup our private context */
    context->registerWithConn();

    if (context->flags.parsed_ok == 0) {
        clientStreamNode *node = context->getClientReplyContext();
        debugs(33, 2, "clientProcessRequest: Invalid Request");
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri,  true);
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_INVALID_REQ, HTTP_BAD_REQUEST, method, NULL, conn->peer, NULL, conn->in.buf, NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        conn->flags.readMoreRequests = false;
        goto finish;
    }

    if ((request = HttpRequest::CreateFromUrlAndMethod(http->uri, method)) == NULL) {
        clientStreamNode *node = context->getClientReplyContext();
        debugs(33, 5, "Invalid URL: " << http->uri);
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri,  true);
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_INVALID_URL, HTTP_BAD_REQUEST, method, http->uri, conn->peer, NULL, NULL, NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        conn->flags.readMoreRequests = false;
        goto finish;
    }

    /* RFC 2616 section 10.5.6 : handle unsupported HTTP versions cleanly. */
    /* We currently only accept 0.9, 1.0, 1.1 */
    if ( (http_ver.major == 0 && http_ver.minor != 9) ||
            (http_ver.major == 1 && http_ver.minor > 1 ) ||
            (http_ver.major > 1) ) {

        clientStreamNode *node = context->getClientReplyContext();
        debugs(33, 5, "Unsupported HTTP version discovered. :\n" << HttpParserHdrBuf(hp));
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri,  true);
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_UNSUP_HTTPVERSION, HTTP_HTTP_VERSION_NOT_SUPPORTED, method, http->uri, conn->peer, NULL, HttpParserHdrBuf(hp), NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        conn->flags.readMoreRequests = false;
        goto finish;
    }

    /* compile headers */
    /* we should skip request line! */
    /* XXX should actually know the damned buffer size here */
    if (http_ver.major >= 1 && !request->parseHeader(HttpParserHdrBuf(hp), HttpParserHdrSz(hp))) {
        clientStreamNode *node = context->getClientReplyContext();
        debugs(33, 5, "Failed to parse request headers:\n" << HttpParserHdrBuf(hp));
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri,  true);
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_INVALID_REQ, HTTP_BAD_REQUEST, method, http->uri, conn->peer, NULL, NULL, NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        conn->flags.readMoreRequests = false;
        goto finish;
    }

    request->flags.accelerated = http->flags.accel;
    request->flags.sslBumped = conn->switchedToHttps();
    request->flags.ignore_cc = conn->port->ignore_cc;
    request->flags.no_direct = request->flags.accelerated ? !conn->port->allow_direct : 0;

    /** \par
     * If transparent or interception mode is working clone the transparent and interception flags
     * from the port settings to the request.
     */
    if (IpInterceptor.InterceptActive()) {
        request->flags.intercepted = http->flags.intercepted;
    }
    if (IpInterceptor.TransparentActive()) {
        request->flags.spoof_client_ip = conn->port->spoof_client_ip;
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
        request->protocol = PROTO_HTTP;
        request->login[0] = '\0';
    }

    request->flags.internal = http->flags.internal;
    setLogUri (http, urlCanonicalClean(request));
    request->client_addr = conn->peer;
#if FOLLOW_X_FORWARDED_FOR
    request->indirect_client_addr = conn->peer;
#endif /* FOLLOW_X_FORWARDED_FOR */
    request->my_addr = conn->me;
    request->myportname = conn->port->name;
    request->http_ver = http_ver;

    tePresent = request->header.has(HDR_TRANSFER_ENCODING);
    deChunked = conn->in.dechunkingState == ConnStateData::chunkReady;
    if (deChunked) {
        assert(tePresent);
        request->setContentLength(conn->in.dechunked.contentSize());
        request->header.delById(HDR_TRANSFER_ENCODING);
        conn->finishDechunkingRequest(hp);
    } else
        conn->cleanDechunkingRequest();

    mustReplyToOptions = (method == METHOD_OPTIONS) &&
                         (request->header.getInt64(HDR_MAX_FORWARDS) == 0);
    unsupportedTe = tePresent && !deChunked;
    if (!urlCheckRequest(request) || mustReplyToOptions || unsupportedTe) {
        clientStreamNode *node = context->getClientReplyContext();
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_UNSUP_REQ,
                                    HTTP_NOT_IMPLEMENTED, request->method, NULL,
                                    conn->peer, request, NULL, NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        conn->flags.readMoreRequests = false;
        goto finish;
    }


    if (!clientIsContentLengthValid(request)) {
        clientStreamNode *node = context->getClientReplyContext();
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_INVALID_REQ,
                                    HTTP_LENGTH_REQUIRED, request->method, NULL,
                                    conn->peer, request, NULL, NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        conn->flags.readMoreRequests = false;
        goto finish;
    }

    if (request->header.has(HDR_EXPECT)) {
        int ignore = 0;
#if HTTP_VIOLATIONS
        if (Config.onoff.ignore_expect_100) {
            String expect = request->header.getList(HDR_EXPECT);
            if (expect.caseCmp("100-continue") == 0)
                ignore = 1;
            expect.clean();
        }
#endif
        if (!ignore) {
            clientStreamNode *node = context->getClientReplyContext();
            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
            assert (repContext);
            repContext->setReplyToError(ERR_INVALID_REQ, HTTP_EXPECTATION_FAILED, request->method, http->uri, conn->peer, request, NULL, NULL);
            assert(context->http->out.offset == 0);
            context->pullData();
            goto finish;
        }
    }

    http->request = HTTPMSGLOCK(request);
    clientSetKeepaliveFlag(http);

    /* If this is a CONNECT, don't schedule a read - ssl.c will handle it */
    if (http->request->method == METHOD_CONNECT)
        context->mayUseConnection(true);

    /* Do we expect a request-body? */
    if (!context->mayUseConnection() && request->content_length > 0) {
        request->body_pipe = conn->expectRequestBody(request->content_length);

        // consume header early so that body pipe gets just the body
        connNoteUseOfBuffer(conn, http->req_sz);
        notedUseOfBuffer = true;

        conn->handleRequestBodyData(); // may comm_close and stop producing

        /* Is it too large? */

        if (!clientIsRequestBodyValid(request->content_length) ||
                clientIsRequestBodyTooLargeForPolicy(request->content_length)) {
            clientStreamNode *node = context->getClientReplyContext();
            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
            assert (repContext);
            repContext->setReplyToError(ERR_TOO_BIG,
                                        HTTP_REQUEST_ENTITY_TOO_LARGE, METHOD_NONE, NULL,
                                        conn->peer, http->request, NULL, NULL);
            assert(context->http->out.offset == 0);
            context->pullData();
            goto finish;
        }

        if (!request->body_pipe->productionEnded())
            conn->readSomeData();

        context->mayUseConnection(!request->body_pipe->productionEnded());
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
    if (http->request->flags.resetTCP() && conn->fd > -1) {
        debugs(33, 3, HERE << "Sending TCP RST on FD " << conn->fd);
        conn->flags.readMoreRequests = false;
        comm_reset_close(conn->fd);
        return;
    }
}