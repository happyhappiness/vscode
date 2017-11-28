bool
HttpMsg::parse(MemBuf *buf, bool eof, Http::StatusCode *error)
{
    assert(error);
    *error = Http::scNone;

    // httpMsgParseStep() and debugging require 0-termination, unfortunately
    buf->terminate(); // does not affect content size

    // find the end of headers
    const size_t hdr_len = headersEnd(buf->content(), buf->contentSize());

    // sanity check the start line to see if this is in fact an HTTP message
    if (!sanityCheckStartLine(buf, hdr_len, error)) {
        // NP: sanityCheck sets *error and sends debug warnings on syntax errors.
        // if we have seen the connection close, this is an error too
        if (eof && *error == Http::scNone)
            *error = Http::scInvalidHeader;

        return false;
    }

    // TODO: move to httpReplyParseStep()
    if (hdr_len > Config.maxReplyHeaderSize || (hdr_len <= 0 && (size_t)buf->contentSize() > Config.maxReplyHeaderSize)) {
        debugs(58, DBG_IMPORTANT, "HttpMsg::parse: Too large reply header (" << hdr_len << " > " << Config.maxReplyHeaderSize);
        *error = Http::scHeaderTooLarge;
        return false;
    }

    if (hdr_len <= 0) {
        debugs(58, 3, "HttpMsg::parse: failed to find end of headers (eof: " << eof << ") in '" << buf->content() << "'");

        if (eof) // iff we have seen the end, this is an error
            *error = Http::scInvalidHeader;

        return false;
    }

    const int res = httpMsgParseStep(buf->content(), buf->contentSize(), eof);

    if (res < 0) { // error
        debugs(58, 3, "HttpMsg::parse: cannot parse isolated headers in '" << buf->content() << "'");
        *error = Http::scInvalidHeader;
        return false;
    }

    if (res == 0) {
        debugs(58, 2, "HttpMsg::parse: strange, need more data near '" << buf->content() << "'");
        *error = Http::scInvalidHeader;
        return false; // but this should not happen due to headersEnd() above
    }

    assert(res > 0);
    debugs(58, 9, "HttpMsg::parse success (" << hdr_len << " bytes) near '" << buf->content() << "'");

    if (hdr_sz != (int)hdr_len) {
        debugs(58, DBG_IMPORTANT, "internal HttpMsg::parse vs. headersEnd error: " <<
               hdr_sz << " != " << hdr_len);
        hdr_sz = (int)hdr_len; // because old http.cc code used hdr_len
    }

    return true;
}