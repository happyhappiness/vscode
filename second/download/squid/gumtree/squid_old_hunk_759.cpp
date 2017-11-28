            }
        }
    }

    return false;
}
#endif // USE_SSL

static void
clientProcessRequest(ConnStateData *conn, HttpParser *hp, ClientSocketContext *context, const HttpRequestMethod& method, Http::ProtocolVersion http_ver)
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
        case Http::scHeaderTooLarge:
            repContext->setReplyToError(ERR_TOO_BIG, Http::scBadRequest, method, http->uri, conn->clientConnection->remote, NULL, conn->in.buf, NULL);
            break;
        case Http::scMethodNotAllowed:
            repContext->setReplyToError(ERR_UNSUP_REQ, Http::scMethodNotAllowed, method, http->uri,
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
        conn->quitAfterError(request.getRaw());
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri,  true);
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_INVALID_URL, Http::scBadRequest, method, http->uri, conn->clientConnection->remote, NULL, NULL, NULL);
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
        conn->quitAfterError(request.getRaw());
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri,  true);
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_UNSUP_HTTPVERSION, Http::scHttpVersionNotSupported, method, http->uri,
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
        conn->quitAfterError(request.getRaw());
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri,  true);
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_INVALID_REQ, Http::scBadRequest, method, http->uri, conn->clientConnection->remote, NULL, NULL, NULL);
        assert(context->http->out.offset == 0);
        context->pullData();
        goto finish;
    }

    request->clientConnectionManager = conn;

    request->flags.accelerated = http->flags.accel;
    request->flags.sslBumped=conn->switchedToHttps();
    request->flags.ignoreCc = conn->port->ignore_cc;
    // TODO: decouple http->flags.accel from request->flags.sslBumped
