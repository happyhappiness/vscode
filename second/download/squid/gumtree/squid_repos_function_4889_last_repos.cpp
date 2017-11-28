bool
Http::One::RequestParser::skipDelimiter(const size_t count, const char *where)
{
    if (count <= 0) {
        debugs(33, ErrorLevel(), "invalid request-line: missing delimiter " << where);
        parseStatusCode = Http::scBadRequest;
        return false;
    }

    // tolerant parser allows multiple whitespace characters between request-line fields
    if (count > 1 && !Config.onoff.relaxed_header_parser) {
        debugs(33, ErrorLevel(), "invalid request-line: too many delimiters " << where);
        parseStatusCode = Http::scBadRequest;
        return false;
    }

    return true;
}