bool
HttpRequest::sanityCheckStartLine(const char *buf, const size_t hdr_len, Http::StatusCode *error)
{
    // content is long enough to possibly hold a reply
    // 2 being magic size of a 1-byte request method plus space delimiter
    if (hdr_len < 2) {
        // this is ony a real error if the headers apparently complete.
        if (hdr_len > 0) {
            debugs(58, 3, HERE << "Too large request header (" << hdr_len << " bytes)");
            *error = Http::scInvalidHeader;
        }
        return false;
    }

    /* See if the request buffer starts with a non-whitespace HTTP request 'method'. */
    HttpRequestMethod m;
    m.HttpRequestMethodXXX(buf);
    if (m == Http::METHOD_NONE) {
        debugs(73, 3, "HttpRequest::sanityCheckStartLine: did not find HTTP request method");
        *error = Http::scInvalidHeader;
        return false;
    }

    return true;
}