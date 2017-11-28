bool
Http::One::RequestParser::parseHttpVersionField(Http1::Tokenizer &tok)
{
    static const SBuf http1p0("HTTP/1.0");
    static const SBuf http1p1("HTTP/1.1");
    const auto savedTok = tok;

    // Optimization: Expect (and quickly parse) HTTP/1.1 or HTTP/1.0 in
    // the vast majority of cases.
    if (tok.skipSuffix(http1p1)) {
        msgProtocol_ = Http::ProtocolVersion(1, 1);
        return true;
    } else if (tok.skipSuffix(http1p0)) {
        msgProtocol_ = Http::ProtocolVersion(1, 0);
        return true;
    } else {
        // RFC 7230 section 2.6:
        // HTTP-version  = HTTP-name "/" DIGIT "." DIGIT
        static const CharacterSet period("Decimal point", ".");
        static const SBuf proto("HTTP/");
        SBuf majorDigit;
        SBuf minorDigit;
        if (tok.suffix(minorDigit, CharacterSet::DIGIT) &&
                tok.skipOneTrailing(period) &&
                tok.suffix(majorDigit, CharacterSet::DIGIT) &&
                tok.skipSuffix(proto)) {
            const bool multiDigits = majorDigit.length() > 1 || minorDigit.length() > 1;
            // use '0.0' for unsupported multiple digit version numbers
            const unsigned int major = multiDigits ? 0 : (*majorDigit.rawContent() - '0');
            const unsigned int minor = multiDigits ? 0 : (*minorDigit.rawContent() - '0');
            msgProtocol_ = Http::ProtocolVersion(major, minor);
            return true;
        }
    }

    // A GET request might use HTTP/0.9 syntax
    if (method_ == Http::METHOD_GET) {
        // RFC 1945 - no HTTP version field at all
        tok = savedTok; // in case the URI ends with a digit
        // report this assumption as an error if configured to triage parsing
        debugs(33, ErrorLevel(), "assuming HTTP/0.9 request-line");
        msgProtocol_ = Http::ProtocolVersion(0,9);
        return true;
    }

    debugs(33, ErrorLevel(), "invalid request-line: not HTTP");
    parseStatusCode = Http::scBadRequest;
    return false;
}