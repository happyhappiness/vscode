bool
Http::One::RequestParser::skipTrailingCrs(Http1::Tokenizer &tok)
{
    if (Config.onoff.relaxed_header_parser) {
        (void)tok.skipAllTrailing(CharacterSet::CR); // optional; multiple OK
    } else {
        if (!tok.skipOneTrailing(CharacterSet::CR)) {
            debugs(33, ErrorLevel(), "invalid request-line: missing CR before LF");
            parseStatusCode = Http::scBadRequest;
            return false;
        }
    }
    return true;
}