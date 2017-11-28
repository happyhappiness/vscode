int
Http::One::RequestParser::parseRequestFirstLine()
{
    debugs(74, 5, "parsing possible request: buf.length=" << buf_.length());
    debugs(74, DBG_DATA, buf_);

    SBuf line;

    // Earlier, skipGarbageLines() took care of any leading LFs (if allowed).
    // Now, the request line has to end at the first LF.
    static const CharacterSet lineChars = CharacterSet::LF.complement("notLF");
    ::Parser::Tokenizer lineTok(buf_);
    if (!lineTok.prefix(line, lineChars) || !lineTok.skip('\n')) {
        if (buf_.length() >= Config.maxRequestHeaderSize) {
            /* who should we blame for our failure to parse this line? */

            Http1::Tokenizer methodTok(buf_);
            if (!parseMethodField(methodTok))
                return -1; // blame a bad method (or its delimiter)

            // assume it is the URI
            debugs(74, ErrorLevel(), "invalid request-line: URI exceeds " <<
                   Config.maxRequestHeaderSize << "-byte limit");
            parseStatusCode = Http::scUriTooLong;
            return -1;
        }
        debugs(74, 5, "Parser needs more data");
        return 0;
    }

    Http1::Tokenizer tok(line);

    if (!parseMethodField(tok))
        return -1;

    /* now parse backwards, to leave just the URI */
    if (!skipTrailingCrs(tok))
        return -1;

    if (!parseHttpVersionField(tok))
        return -1;

    if (!http0() && !skipDelimiter(tok.skipAllTrailing(DelimiterCharacters()), "before protocol version"))
        return -1;

    /* parsed everything before and after the URI */

    if (!parseUriField(tok))
        return -1;

    if (!tok.atEnd()) {
        debugs(33, ErrorLevel(), "invalid request-line: garbage after URI");
        parseStatusCode = Http::scBadRequest;
        return -1;
    }

    parseStatusCode = Http::scOkay;
    buf_ = lineTok.remaining(); // incremental parse checkpoint
    return 1;
}