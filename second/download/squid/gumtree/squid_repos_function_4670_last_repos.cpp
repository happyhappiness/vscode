bool
Http::One::Server::buildHttpRequest(Http::StreamPointer &context)
{
    HttpRequest::Pointer request;
    ClientHttpRequest *http = context->http;
    if (context->flags.parsed_ok == 0) {
        debugs(33, 2, "Invalid Request");
        // determine which error page templates to use for specific parsing errors
        err_type errPage = ERR_INVALID_REQ;
        switch (parser_->parseStatusCode) {
        case Http::scRequestHeaderFieldsTooLarge:
        // fall through to next case
        case Http::scUriTooLong:
            errPage = ERR_TOO_BIG;
            break;
        case Http::scMethodNotAllowed:
            errPage = ERR_UNSUP_REQ;
            break;
        case Http::scHttpVersionNotSupported:
            errPage = ERR_UNSUP_HTTPVERSION;
            break;
        default:
            if (parser_->method() == METHOD_NONE || parser_->requestUri().length() == 0)
                // no method or url parsed, probably is wrong protocol
                errPage = ERR_PROTOCOL_UNKNOWN;
            // else use default ERR_INVALID_REQ set above.
            break;
        }
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri, true);
        const char * requestErrorBytes = inBuf.c_str();
        if (!clientTunnelOnError(this, context, request, parser_->method(), errPage)) {
            setReplyError(context, request, parser_->method(), errPage, parser_->parseStatusCode, requestErrorBytes);
            // HttpRequest object not build yet, there is no reason to call
            // clientProcessRequestFinished method
        }

        return false;
    }

    MasterXaction::Pointer mx = new MasterXaction(XactionInitiator::initClient);
    mx->tcpClient = clientConnection;
    if ((request = HttpRequest::FromUrl(http->uri, mx, parser_->method())) == NULL) {
        debugs(33, 5, "Invalid URL: " << http->uri);
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri, true);

        const char * requestErrorBytes = inBuf.c_str();
        if (!clientTunnelOnError(this, context, request, parser_->method(), ERR_INVALID_URL)) {
            setReplyError(context, request, parser_->method(), ERR_INVALID_URL, Http::scBadRequest, requestErrorBytes);
            // HttpRequest object not build yet, there is no reason to call
            // clientProcessRequestFinished method
        }
        return false;
    }

    /* RFC 2616 section 10.5.6 : handle unsupported HTTP major versions cleanly. */
    /* We currently only support 0.9, 1.0, 1.1 properly */
    /* TODO: move HTTP-specific processing into servers/HttpServer and such */
    if ( (parser_->messageProtocol().major == 0 && parser_->messageProtocol().minor != 9) ||
            (parser_->messageProtocol().major > 1) ) {

        debugs(33, 5, "Unsupported HTTP version discovered. :\n" << parser_->messageProtocol());
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri,  true);

        const char * requestErrorBytes = NULL; //HttpParserHdrBuf(parser_);
        if (!clientTunnelOnError(this, context, request, parser_->method(), ERR_UNSUP_HTTPVERSION)) {
            setReplyError(context, request, parser_->method(), ERR_UNSUP_HTTPVERSION, Http::scHttpVersionNotSupported, requestErrorBytes);
            clientProcessRequestFinished(this, request);
        }
        return false;
    }

    /* compile headers */
    if (parser_->messageProtocol().major >= 1 && !request->parseHeader(*parser_.getRaw())) {
        debugs(33, 5, "Failed to parse request headers:\n" << parser_->mimeHeader());
        // setLogUri should called before repContext->setReplyToError
        setLogUri(http, http->uri, true);
        const char * requestErrorBytes = NULL; //HttpParserHdrBuf(parser_);
        if (!clientTunnelOnError(this, context, request, parser_->method(), ERR_INVALID_REQ)) {
            setReplyError(context, request, parser_->method(), ERR_INVALID_REQ, Http::scBadRequest, requestErrorBytes);
            clientProcessRequestFinished(this, request);
        }
        return false;
    }

    // when absolute-URI is provided Host header should be ignored. However
    // some code still uses Host directly so normalize it using the previously
    // sanitized URL authority value.
    // For now preserve the case where Host is completely absent. That matters.
    if (const auto x = request->header.delById(Http::HOST)) {
        debugs(33, 5, "normalize " << x << " Host header using " << request->url.authority());
        SBuf tmp(request->url.authority());
        request->header.putStr(Http::HOST, tmp.c_str());
    }

    http->request = request.getRaw();
    HTTPMSGLOCK(http->request);

    return true;
}