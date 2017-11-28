bool
Http::One::RequestParser::parseUriField(Http1::Tokenizer &tok)
{
    /* Arbitrary 64KB URI upper length limit.
     *
     * Not quite as arbitrary as it seems though. Old SquidString objects
     * cannot store strings larger than 64KB, so we must limit until they
     * have all been replaced with SBuf.
     *
     * Not that it matters but RFC 7230 section 3.1.1 requires (RECOMMENDED)
     * at least 8000 octets for the whole line, including method and version.
     */
    const size_t maxUriLength = static_cast<size_t>((64*1024)-1);

    SBuf uriFound;
    if (!tok.prefix(uriFound, RequestTargetCharacters())) {
        parseStatusCode = Http::scBadRequest;
        debugs(33, ErrorLevel(), "invalid request-line: missing or malformed URI");
        return false;
    }

    if (uriFound.length() > maxUriLength) {
        // RFC 7230 section 3.1.1 mandatory (MUST) 414 response
        parseStatusCode = Http::scUriTooLong;
        debugs(33, ErrorLevel(), "invalid request-line: " << uriFound.length() <<
               "-byte URI exceeds " << maxUriLength << "-byte limit");
        return false;
    }

    uri_ = uriFound;
    return true;
}