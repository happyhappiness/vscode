bool
Http::One::ResponseParser::parse(const SBuf &aBuf)
{
    buf_ = aBuf;
    debugs(74, DBG_DATA, "Parse buf={length=" << aBuf.length() << ", data='" << aBuf << "'}");

    // stage 1: locate the status-line
    if (parsingStage_ == HTTP_PARSE_NONE) {
        // RFC 7230 explicitly states whether garbage whitespace is to be handled
        // at each point of the message framing boundaries.
        // It omits mentioning garbage prior to HTTP Responses.
        // Therefore, if we receive anything at all treat it as Response message.
        if (!buf_.isEmpty())
            parsingStage_ = HTTP_PARSE_FIRST;
        else
            return false;
    }

    // stage 2: parse the status-line
    if (parsingStage_ == HTTP_PARSE_FIRST) {
        PROF_start(HttpParserParseReplyLine);

        const int retcode = parseResponseFirstLine();

        // first-line (or a look-alike) found successfully.
        if (retcode > 0 && parsingStage_ == HTTP_PARSE_FIRST)
            parsingStage_ = HTTP_PARSE_MIME;
        debugs(74, 5, "status-line: retval " << retcode);
        debugs(74, 5, "status-line: proto " << msgProtocol_);
        debugs(74, 5, "status-line: status-code " << statusCode_);
        debugs(74, 5, "status-line: reason-phrase " << reasonPhrase_);
        debugs(74, 5, "Parser: bytes processed=" << (aBuf.length()-buf_.length()));
        PROF_stop(HttpParserParseReplyLine);

        // syntax errors already
        if (retcode < 0) {
            parsingStage_ = HTTP_PARSE_DONE;
            parseStatusCode = Http::scInvalidHeader;
            return false;
        }
    }

    // stage 3: locate the mime header block
    if (parsingStage_ == HTTP_PARSE_MIME) {
        if (!grabMimeBlock("Response", Config.maxReplyHeaderSize))
            return false;
    }

    return !needsMoreData();
}