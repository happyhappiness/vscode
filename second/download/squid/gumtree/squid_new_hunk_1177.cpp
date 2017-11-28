
    // interception cases do not need USER to calculate the uri
    if (!transparent()) {
        if (!master->clientReadGreeting) {
            // the first command must be USER
            if (!pinning.pinned && cmd != cmdUser())
                return earlyError(EarlyErrorKind::MissingLogin);
        }

        // process USER request now because it sets FTP peer host name
        if (cmd == cmdUser()) {
            if (Http::Stream *errCtx = handleUserRequest(cmd, params))
                return errCtx;
        }
    }

    if (!Ftp::SupportedCommand(cmd))
        return earlyError(EarlyErrorKind::UnsupportedCommand);

    const HttpRequestMethod method =
        cmd == cmdAppe() || cmd == cmdStor() || cmd == cmdStou() ?
        Http::METHOD_PUT : Http::METHOD_GET;

    const SBuf *path = (params.length() && CommandHasPathParameter(cmd)) ?
                       &params : NULL;
    calcUri(path);
    char *newUri = xstrdup(uri.c_str());
    HttpRequest *const request = HttpRequest::CreateFromUrl(newUri, method);
    if (!request) {
        debugs(33, 5, "Invalid FTP URL: " << uri);
        uri.clear();
        safe_free(newUri);
        return earlyError(EarlyErrorKind::InvalidUri);
    }

    request->flags.ftpNative = true;
    request->http_ver = Http::ProtocolVersion(Ftp::ProtocolVersion().major, Ftp::ProtocolVersion().minor);

    // Our fake Request-URIs are not distinctive enough for caching to work
    request->flags.cachable = false; // XXX: reset later by maybeCacheable()
    request->flags.noCache = true;

    request->header.putStr(Http::HdrType::FTP_COMMAND, cmd.c_str());
    request->header.putStr(Http::HdrType::FTP_ARGUMENTS, params.c_str()); // may be ""
    if (method == Http::METHOD_PUT) {
        request->header.putStr(Http::HdrType::EXPECT, "100-continue");
        request->header.putStr(Http::HdrType::TRANSFER_ENCODING, "chunked");
    }

    ClientHttpRequest *const http = new ClientHttpRequest(this);
    http->request = request;
    HTTPMSGLOCK(http->request);
    http->req_sz = tok.parsedSize();
    http->uri = newUri;

    Http::Stream *const result =
        new Http::Stream(clientConnection, http);

    StoreIOBuffer tempBuffer;
    tempBuffer.data = result->reqbuf;
    tempBuffer.length = HTTP_REQBUF_SZ;

    ClientStreamData newServer = new clientReplyContext(http);
