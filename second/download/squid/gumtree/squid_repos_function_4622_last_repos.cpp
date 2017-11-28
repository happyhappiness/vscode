Http::Stream *
Ftp::Server::parseOneRequest()
{
    flags.readMore = false; // common for all but one case below

    // OWS <command> [ RWS <parameter> ] OWS LF

    // InlineSpaceChars are isspace(3) or RFC 959 Section 3.1.1.5.2, except
    // for the LF character that we must exclude here (but see FullWhiteSpace).
    static const char * const InlineSpaceChars = " \f\r\t\v";
    static const CharacterSet InlineSpace = CharacterSet("Ftp::Inline", InlineSpaceChars);
    static const CharacterSet FullWhiteSpace = (InlineSpace + CharacterSet::LF).rename("Ftp::FWS");
    static const CharacterSet CommandChars = FullWhiteSpace.complement("Ftp::Command");
    static const CharacterSet TailChars = CharacterSet::LF.complement("Ftp::Tail");

    // This set is used to ignore empty commands without allowing an attacker
    // to keep us endlessly busy by feeding us whitespace or empty commands.
    static const CharacterSet &LeadingSpace = FullWhiteSpace;

    SBuf cmd;
    SBuf params;

    Parser::Tokenizer tok(inBuf);

    (void)tok.skipAll(LeadingSpace); // leading OWS and empty commands
    const bool parsed = tok.prefix(cmd, CommandChars); // required command

    // note that the condition below will eat either RWS or trailing OWS
    if (parsed && tok.skipAll(InlineSpace) && tok.prefix(params, TailChars)) {
        // now params may include trailing OWS
        // TODO: Support right-trimming using CharacterSet in Tokenizer instead
        static const SBuf bufWhiteSpace(InlineSpaceChars);
        params.trim(bufWhiteSpace, false, true);
    }

    // Why limit command line and parameters size? Did not we just parse them?
    // XXX: Our good old String cannot handle very long strings.
    const SBuf::size_type tokenMax = min(
                                         static_cast<SBuf::size_type>(32*1024), // conservative
                                         static_cast<SBuf::size_type>(Config.maxRequestHeaderSize));
    if (cmd.length() > tokenMax || params.length() > tokenMax) {
        changeState(fssError, "huge req token");
        quitAfterError(NULL);
        return earlyError(EarlyErrorKind::HugeRequest);
    }

    // technically, we may skip multiple NLs below, but that is OK
    if (!parsed || !tok.skipAll(CharacterSet::LF)) { // did not find terminating LF yet
        // we need more data, but can we buffer more?
        if (inBuf.length() >= Config.maxRequestHeaderSize) {
            changeState(fssError, "huge req");
            quitAfterError(NULL);
            return earlyError(EarlyErrorKind::HugeRequest);
        } else {
            flags.readMore = true;
            debugs(33, 5, "Waiting for more, up to " <<
                   (Config.maxRequestHeaderSize - inBuf.length()));
            return NULL;
        }
    }

    Must(parsed && cmd.length());
    consumeInput(tok.parsedSize()); // TODO: Would delaying optimize copying?

    debugs(33, 2, ">>ftp " << cmd << (params.isEmpty() ? "" : " ") << params);

    cmd.toUpper(); // this should speed up and simplify future comparisons

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
    MasterXaction::Pointer mx = new MasterXaction(XactionInitiator::initClient);
    mx->tcpClient = clientConnection;
    HttpRequest *const request = HttpRequest::FromUrl(newUri, mx, method);
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
    ClientStreamData newClient = result;
    clientStreamInit(&http->client_stream, clientGetMoreData, clientReplyDetach,
                     clientReplyStatus, newServer, clientSocketRecipient,
                     clientSocketDetach, newClient, tempBuffer);

    result->flags.parsed_ok = 1;
    return result;
}