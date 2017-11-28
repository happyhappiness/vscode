bool
HttpRequest::sanityCheckStartLine(MemBuf *buf, const size_t hdr_len, http_status *error)
{
    // content is long enough to possibly hold a reply
    // 2 being magic size of a 1-byte request method plus space delimiter
    if ( buf->contentSize() < 2 ) {
        // this is ony a real error if the headers apparently complete.
        if (hdr_len > 0) {
            debugs(58, 3, HERE << "Too large request header (" << hdr_len << " bytes)");
            *error = HTTP_INVALID_HEADER;
        }
        return false;
    }

    /* See if the request buffer starts with a known HTTP request method. */
    if (HttpRequestMethod(buf->content(),NULL) == METHOD_NONE) {
        debugs(73, 3, "HttpRequest::sanityCheckStartLine: did not find HTTP request method");
        *error = HTTP_INVALID_HEADER;
        return false;
    }

    return true;
}