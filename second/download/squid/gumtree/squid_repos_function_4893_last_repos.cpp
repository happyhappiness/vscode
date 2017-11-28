bool
Http::One::RequestParser::doParse(const SBuf &aBuf)
{
    buf_ = aBuf;
    debugs(74, DBG_DATA, "Parse buf={length=" << aBuf.length() << ", data='" << aBuf << "'}");

    // stage 1: locate the request-line
    if (parsingStage_ == HTTP_PARSE_NONE) {
        skipGarbageLines();

        // if we hit something before EOS treat it as a message
        if (!buf_.isEmpty())
            parsingStage_ = HTTP_PARSE_FIRST;
        else
            return false;
    }

    // stage 2: parse the request-line
    if (parsingStage_ == HTTP_PARSE_FIRST) {
        PROF_start(HttpParserParseReqLine);
        const int retcode = parseRequestFirstLine();

        // first-line (or a look-alike) found successfully.
        if (retcode > 0) {
            parsingStage_ = HTTP_PARSE_MIME;
        }

        debugs(74, 5, "request-line: retval " << retcode << ": line={" << aBuf.length() << ", data='" << aBuf << "'}");
        debugs(74, 5, "request-line: method: " << method_);
        debugs(74, 5, "request-line: url: " << uri_);
        debugs(74, 5, "request-line: proto: " << msgProtocol_);
        debugs(74, 5, "Parser: bytes processed=" << (aBuf.length()-buf_.length()));
        PROF_stop(HttpParserParseReqLine);

        // syntax errors already
        if (retcode < 0) {
            parsingStage_ = HTTP_PARSE_DONE;
            return false;
        }
    }

    // stage 3: locate the mime header block
    if (parsingStage_ == HTTP_PARSE_MIME) {
        // HTTP/1.x request-line is valid and parsing completed.
        if (!grabMimeBlock("Request", Config.maxRequestHeaderSize)) {
            if (parseStatusCode == Http::scHeaderTooLarge)
                parseStatusCode = Http::scRequestHeaderFieldsTooLarge;
            return false;
        }
    }

    return !needsMoreData();
}