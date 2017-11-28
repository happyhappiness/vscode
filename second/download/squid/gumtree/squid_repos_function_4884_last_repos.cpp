bool
Http::One::RequestParser::parseMethodField(Http1::Tokenizer &tok)
{
    // method field is a sequence of TCHAR.
    // Limit to 32 characters to prevent overly long sequences of non-HTTP
    // being sucked in before mismatch is detected. 32 is itself annoyingly
    // big but there are methods registered by IANA that reach 17 bytes:
    //  http://www.iana.org/assignments/http-methods
    static const size_t maxMethodLength = 32; // TODO: make this configurable?

    SBuf methodFound;
    if (!tok.prefix(methodFound, CharacterSet::TCHAR, maxMethodLength)) {
        debugs(33, ErrorLevel(), "invalid request-line: missing or malformed method");
        parseStatusCode = Http::scBadRequest;
        return false;
    }
    method_ = HttpRequestMethod(methodFound);

    if (!skipDelimiter(tok.skipAll(DelimiterCharacters()), "after method"))
        return false;

    return true;
}