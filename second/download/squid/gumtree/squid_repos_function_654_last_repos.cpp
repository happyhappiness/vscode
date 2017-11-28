bool
HttpMsg::parse(const char *buf, const size_t sz, bool eof, Http::StatusCode *error)
{
    assert(error);
    *error = Http::scNone;

    // find the end of headers
    const size_t hdr_len = headersEnd(buf, sz);

    // sanity check the start line to see if this is in fact an HTTP message
    if (!sanityCheckStartLine(buf, hdr_len, error)) {
        // NP: sanityCheck sets *error and sends debug warnings on syntax errors.
        // if we have seen the connection close, this is an error too
        if (eof && *error == Http::scNone)
            *error = Http::scInvalidHeader;

        return false;
    }

    if (hdr_len > Config.maxReplyHeaderSize || (hdr_len <= 0 && sz > Config.maxReplyHeaderSize)) {
        debugs(58, DBG_IMPORTANT, "HttpMsg::parse: Too large reply header (" << hdr_len << " > " << Config.maxReplyHeaderSize);
        *error = Http::scHeaderTooLarge;
        return false;
    }

    if (hdr_len <= 0) {
        debugs(58, 3, "HttpMsg::parse: failed to find end of headers (eof: " << eof << ") in '" << buf << "'");

        if (eof) // iff we have seen the end, this is an error
            *error = Http::scInvalidHeader;

        return false;
    }

    const int res = httpMsgParseStep(buf, sz, eof);

    if (res < 0) { // error
        debugs(58, 3, "HttpMsg::parse: cannot parse isolated headers in '" << buf << "'");
        *error = Http::scInvalidHeader;
        return false;
    }

    if (res == 0) {
        debugs(58, 2, "HttpMsg::parse: strange, need more data near '" << buf << "'");
        *error = Http::scInvalidHeader;
        return false; // but this should not happen due to headersEnd() above
    }

    assert(res > 0);
    debugs(58, 9, "HttpMsg::parse success (" << hdr_len << " bytes) near '" << buf << "'");

    if (hdr_sz != (int)hdr_len) {
        debugs(58, DBG_IMPORTANT, "internal HttpMsg::parse vs. headersEnd error: " <<
               hdr_sz << " != " << hdr_len);
        hdr_sz = (int)hdr_len; // because old http.cc code used hdr_len
    }

    return true;
}