bool
HttpReply::sanityCheckStartLine(MemBuf *buf, const size_t hdr_len, Http::StatusCode *error)
{
    // hack warning: using psize instead of size here due to type mismatches with MemBuf.

    // content is long enough to possibly hold a reply
    // 4 being magic size of a 3-digit number plus space delimiter
    if ( buf->contentSize() < (protoPrefix.psize() + 4) ) {
        if (hdr_len > 0) {
            debugs(58, 3, HERE << "Too small reply header (" << hdr_len << " bytes)");
            *error = Http::scInvalidHeader;
        }
        return false;
    }

    int pos;
    // catch missing or mismatched protocol identifier
    // allow special-case for ICY protocol (non-HTTP identifier) in response to faked HTTP request.
    if (strncmp(buf->content(), "ICY", 3) == 0) {
        protoPrefix = "ICY";
        pos = protoPrefix.psize();
    } else {

        if (protoPrefix.cmp(buf->content(), protoPrefix.size()) != 0) {
            debugs(58, 3, "HttpReply::sanityCheckStartLine: missing protocol prefix (" << protoPrefix << ") in '" << buf->content() << "'");
            *error = Http::scInvalidHeader;
            return false;
        }

        // catch missing or negative status value (negative '-' is not a digit)
        pos = protoPrefix.psize();

        // skip arbitrary number of digits and a dot in the verion portion
        while ( pos <= buf->contentSize() && (*(buf->content()+pos) == '.' || xisdigit(*(buf->content()+pos)) ) ) ++pos;

        // catch missing version info
        if (pos == protoPrefix.psize()) {
            debugs(58, 3, "HttpReply::sanityCheckStartLine: missing protocol version numbers (ie. " << protoPrefix << "/1.0) in '" << buf->content() << "'");
            *error = Http::scInvalidHeader;
            return false;
        }
    }

    // skip arbitrary number of spaces...
    while (pos <= buf->contentSize() && (char)*(buf->content()+pos) == ' ') ++pos;

    if (pos < buf->contentSize() && !xisdigit(*(buf->content()+pos))) {
        debugs(58, 3, "HttpReply::sanityCheckStartLine: missing or invalid status number in '" << buf->content() << "'");
        *error = Http::scInvalidHeader;
        return false;
    }

    return true;
}