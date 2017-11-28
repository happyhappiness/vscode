void
clientProcessRequest(ConnStateData *conn, HttpParser *hp, ClientSocketContext *context, const HttpRequestMethod& method, Http::ProtocolVersion http_ver)
{
    ClientHttpRequest *http = context->http;
    HttpRequest::Pointer request;
    bool notedUseOfBuffer = false;
    bool chunked = false;
    bool mustReplyToOptions = false;
    bool unsupportedTe = false;
    bool expectBody = false;

    // temporary hack to avoid splitting this huge function with sensitive code
    const bool isFtp = !hp;
    if (isFtp) {
        // In FTP, case, we already have the request parsed and checked, so we
        // only need to go through the final body/conn setup to doCallouts().
        assert(http->request);
        request = http->request;
        notedUseOfBuffer = true;
    } else {

        if (context->flags.parsed_ok == 0) {
            clientStreamNode *node = context->getClientReplyContext();
            debugs(33, 2, "clientProcessRequest: Invalid Request");
            conn->quitAfterError(NULL);
            // setLogUri should called before repContext->setReplyToError
            setLogUri(http, http->uri,  true);
            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
            assert (repContext);
            switch (hp->request_parse_status) {
            case Http::scHeaderTooLarge:
                repContext->setReplyToError(ERR_TOO_BIG, Http::scBadRequest, method, http->uri, conn->clientConnection->remote, NULL, conn->in.buf.c_str(), NULL);
                break;
            case Http::scMethodNotAllowed:
                repContext->setReplyToError(ERR_UNSUP_REQ, Http::scMethodNotAllowed, method, http->uri,
                                            conn->clientConnection->remote, NULL, conn->in.buf.c_str(), NULL);
                break;
            default:
                repContext->setReplyToError(ERR_INVALID_REQ, hp->request_parse_status, method, http->uri,
                                            conn->clientConnection->remote, NULL, conn->in.buf.c_str(), NULL);
            }
            assert(context->http->out.offset == 0);
            context->pullData();
            connNoteUseOfBuffer(conn, http->req_sz);
            return;
        }

        if ((request = HttpRequest::CreateFromUrlAndMethod(http->uri, method)) == NULL) {
            clientStreamNode *node = context->getClientReplyContext();
            debugs(33, 5, "Invalid URL: " << http->uri);
            conn->quitAfterError(request.getRaw());
            // setLogUri should called before repContext->setReplyToError
            setLogUri(http, http->uri,  true);
            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
            assert (repContext);
            repContext->setReplyToError(ERR_INVALID_URL, Http::scBadRequest, method, http->uri, conn->clientConnection->remote, NULL, NULL, NULL);
            assert(context->http->out.offset == 0);
            context->pullData();
            connNoteUseOfBuffer(conn, http->req_sz);
            return;
        }

        /* RFC 2616 section 10.5.6 : handle unsupported HTTP major versions cleanly. */
        /* We currently only support 0.9, 1.0, 1.1 properly */
        /* TODO: move HTTP-specific processing into servers/HttpServer and such */
        if ( (http_ver.major == 0 && http_ver.minor != 9) ||
                (http_ver.major > 1) ) {

            clientStreamNode *node = context->getClientReplyContext();
            debugs(33, 5, "Unsupported HTTP version discovered. :\n" << HttpParserHdrBuf(hp));
            conn->quitAfterError(request.getRaw());
            // setLogUri should called before repContext->setReplyToError
            setLogUri(http, http->uri,  true);
            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
            assert (repContext);
            repContext->setReplyToError(ERR_UNSUP_HTTPVERSION, Http::scHttpVersionNotSupported, method, http->uri,
                                        conn->clientConnection->remote, NULL, HttpParserHdrBuf(hp), NULL);
            assert(context->http->out.offset == 0);
            context->pullData();
            connNoteUseOfBuffer(conn, http->req_sz);
            clientProcessRequestFinished(conn, request);
            return;
        }

        /* compile headers */
        /* we should skip request line! */
        /* XXX should actually know the damned buffer size here */
        if (http_ver.major >= 1 && !request->parseHeader(HttpParserHdrBuf(hp), HttpParserHdrSz(hp))) {
            clientStreamNode *node = context->getClientReplyContext();
            debugs(33, 5, "Failed to parse request headers:\n" << HttpParserHdrBuf(hp));
            conn->quitAfterError(request.getRaw());
            // setLogUri should called before repContext->setReplyToError
            setLogUri(http, http->uri,  true);
            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
            assert (repContext);
            repContext->setReplyToError(ERR_INVALID_REQ, Http::scBadRequest, method, http->uri, conn->clientConnection->remote, NULL, NULL, NULL);
            assert(context->http->out.offset == 0);
            context->pullData();
            connNoteUseOfBuffer(conn, http->req_sz);
            clientProcessRequestFinished(conn, request);
            return;
        }

        // when absolute-URI is provided Host header should be ignored. However
        // some code still uses Host directly so normalize it.
        // For now preserve the case where Host is completely absent. That matters.
        if (request->header.has(HDR_HOST)) {
            const char *host = request->header.getStr(HDR_HOST);
            SBuf authority(request->GetHost());
            if (request->port != urlDefaultPort(request->url.getScheme()))
                authority.appendf(":%d", request->port);
            debugs(33, 5, "URL domain " << authority << " overrides header Host: " << host);
            // URL authority overrides Host header
            request->header.delById(HDR_HOST);
            request->header.putStr(HDR_HOST, authority.c_str());
        }
    }

    // Some blobs below are still HTTP-specific, but we would have to rewrite
    // this entire function to remove them from the FTP code path. Connection
    // setup and body_pipe preparation blobs are needed for FTP.

    request->clientConnectionManager = conn;

    request->flags.accelerated = http->flags.accel;
    request->flags.sslBumped=conn->switchedToHttps();
    request->flags.ignoreCc = conn->port->ignore_cc;
    // TODO: decouple http->flags.accel from request->flags.sslBumped
    request->flags.noDirect = (request->flags.accelerated && !request->flags.sslBumped) ?
                              !conn->port->allow_direct : 0;
#if USE_AUTH
    if (request->flags.sslBumped) {
        if (conn->getAuth() != NULL)
            request->auth_user_request = conn->getAuth();
    }
#endif

    /** \par
     * If transparent or interception mode is working clone the transparent and interception flags
     * from the port settings to the request.
     */
    if (http->clientConnection != NULL) {
        request->flags.intercepted = ((http->clientConnection->flags & COMM_INTERCEPTION) != 0);
        request->flags.interceptTproxy = ((http->clientConnection->flags & COMM_TRANSPARENT) != 0 ) ;
        static const bool proxyProtocolPort = (conn->port != NULL) ? conn->port->flags.proxySurrogate : false;
        if (request->flags.interceptTproxy && !proxyProtocolPort) {
            if (Config.accessList.spoof_client_ip) {
                ACLFilledChecklist *checklist = clientAclChecklistCreate(Config.accessList.spoof_client_ip, http);
                request->flags.spoofClientIp = (checklist->fastCheck() == ACCESS_ALLOWED);
                delete checklist;
            } else
                request->flags.spoofClientIp = true;
        } else
            request->flags.spoofClientIp = false;
    }

    if (internalCheck(request->urlpath.termedBuf())) {
        if (internalHostnameIs(request->GetHost()) && request->port == getMyPort()) {
            debugs(33, 2, "internal URL found: " << request->url.getScheme() << "://" << request->GetHost() <<
                   ':' << request->port);
            http->flags.internal = true;
        } else if (Config.onoff.global_internal_static && internalStaticCheck(request->urlpath.termedBuf())) {
            debugs(33, 2, "internal URL found: " << request->url.getScheme() << "://" << request->GetHost() <<
                   ':' << request->port << " (global_internal_static on)");
            request->url.setScheme(AnyP::PROTO_HTTP);
            request->SetHost(internalHostname());
            request->port = getMyPort();
            http->flags.internal = true;
        } else
            debugs(33, 2, "internal URL found: " << request->url.getScheme() << "://" << request->GetHost() <<
                   ':' << request->port << " (not this proxy)");
    }

    if (http->flags.internal)
        request->login[0] = '\0';

    request->flags.internal = http->flags.internal;
    setLogUri (http, urlCanonicalClean(request.getRaw()));
    request->client_addr = conn->clientConnection->remote; // XXX: remove request->client_addr member.
#if FOLLOW_X_FORWARDED_FOR
    // indirect client gets stored here because it is an HTTP header result (from X-Forwarded-For:)
    // not details about the TCP connection itself
    request->indirect_client_addr = conn->clientConnection->remote;
#endif /* FOLLOW_X_FORWARDED_FOR */
    request->my_addr = conn->clientConnection->local;
    request->myportname = conn->port->name;
    request->http_ver = http_ver;
    request->hdr_sz = http->req_sz;

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

    mustReplyToOptions = (method == Http::METHOD_OPTIONS) &&
                         (request->header.getInt64(HDR_MAX_FORWARDS) == 0);
    if (!urlCheckRequest(request.getRaw()) || mustReplyToOptions || unsupportedTe) {
        clientStreamNode *node = context->getClientReplyContext();
        conn->quitAfterError(request.getRaw());
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_UNSUP_REQ, Http::scNotImplemented, request->method, NULL,
                                    conn->clientConnection->remote, request.getRaw(), NULL, NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        connNoteUseOfBuffer(conn, http->req_sz);
        clientProcessRequestFinished(conn, request);
        return;
    }

    if (!chunked && !clientIsContentLengthValid(request.getRaw())) {
        clientStreamNode *node = context->getClientReplyContext();
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        conn->quitAfterError(request.getRaw());
        repContext->setReplyToError(ERR_INVALID_REQ,
                                    Http::scLengthRequired, request->method, NULL,
                                    conn->clientConnection->remote, request.getRaw(), NULL, NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        connNoteUseOfBuffer(conn, http->req_sz);
        clientProcessRequestFinished(conn, request);
        return;
    }

    if (request->header.has(HDR_EXPECT)) {
        const String expect = request->header.getList(HDR_EXPECT);
        const bool supportedExpect = (expect.caseCmp("100-continue") == 0);
        if (!supportedExpect) {
            clientStreamNode *node = context->getClientReplyContext();
            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
            assert (repContext);
            conn->quitAfterError(request.getRaw());
            repContext->setReplyToError(ERR_INVALID_REQ, Http::scExpectationFailed, request->method, http->uri,
                                        conn->clientConnection->remote, request.getRaw(), NULL, NULL);
            assert(context->http->out.offset == 0);
            context->pullData();
            connNoteUseOfBuffer(conn, http->req_sz);
            clientProcessRequestFinished(conn, request);
            return;
        }
    }

    if (!isFtp) {
        http->request = request.getRaw();
        HTTPMSGLOCK(http->request);
    }

    clientSetKeepaliveFlag(http);
    // Let tunneling code be fully responsible for CONNECT requests
    if (http->request->method == Http::METHOD_CONNECT) {
        context->mayUseConnection(true);
        conn->flags.readMore = false;

        // consume header early so that tunnel gets just the body
        connNoteUseOfBuffer(conn, http->req_sz);
        notedUseOfBuffer = true;
    }

#if USE_OPENSSL
    if (conn->switchedToHttps() && conn->serveDelayedError(context)) {
        if (!notedUseOfBuffer)
            connNoteUseOfBuffer(conn, http->req_sz);
        clientProcessRequestFinished(conn, request);
        return;
    }
#endif

    /* Do we expect a request-body? */
    expectBody = chunked || request->content_length > 0;
    if (!context->mayUseConnection() && expectBody) {
        request->body_pipe = conn->expectRequestBody(
                                 chunked ? -1 : request->content_length);

        if (!isFtp) {
            // consume header early so that body pipe gets just the body
            connNoteUseOfBuffer(conn, http->req_sz);
            notedUseOfBuffer = true;
        }

        /* Is it too large? */
        if (!chunked && // if chunked, we will check as we accumulate
                clientIsRequestBodyTooLargeForPolicy(request->content_length)) {
            clientStreamNode *node = context->getClientReplyContext();
            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
            assert (repContext);
            conn->quitAfterError(request.getRaw());
            repContext->setReplyToError(ERR_TOO_BIG,
                                        Http::scPayloadTooLarge, Http::METHOD_NONE, NULL,
                                        conn->clientConnection->remote, http->request, NULL, NULL);
            assert(context->http->out.offset == 0);
            context->pullData();
            clientProcessRequestFinished(conn, request);
            return;
        }

        if (!isFtp) {
            // We may stop producing, comm_close, and/or call setReplyToError()
            // below, so quit on errors to avoid http->doCallouts()
            if (!conn->handleRequestBodyData()) {
                clientProcessRequestFinished(conn, request);
                return;
            }

            if (!request->body_pipe->productionEnded()) {
                debugs(33, 5, "need more request body");
                context->mayUseConnection(true);
                assert(conn->flags.readMore);
            }
        }
    }

    http->calloutContext = new ClientRequestContext(http);

    http->doCallouts();

    if (!notedUseOfBuffer)
        connNoteUseOfBuffer(conn, http->req_sz);

    clientProcessRequestFinished(conn, request);
}