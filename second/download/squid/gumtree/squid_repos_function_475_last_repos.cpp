bool
HttpReply::sanityCheckStartLine(const char *buf, const size_t hdr_len, Http::StatusCode *error)
{
    // hack warning: using psize instead of size here due to type mismatches with MemBuf.

    // content is long enough to possibly hold a reply
    // 4 being magic size of a 3-digit number plus space delimiter
    if (hdr_len < (size_t)(protoPrefix.psize() + 4)) {
        if (hdr_len > 0) {
            debugs(58, 3, "Too small reply header (" << hdr_len << " bytes)");
            *error = Http::scInvalidHeader;
        }
        return false;
    }

    int pos;
    // catch missing or mismatched protocol identifier
    // allow special-case for ICY protocol (non-HTTP identifier) in response to faked HTTP request.
    if (strncmp(buf, "ICY", 3) == 0) {
        protoPrefix = "ICY";
        pos = protoPrefix.psize();
    } else {

        if (protoPrefix.cmp(buf, protoPrefix.size()) != 0) {
            debugs(58, 3, "missing protocol prefix (" << protoPrefix << ") in '" << buf << "'");
            *error = Http::scInvalidHeader;
            return false;
        }

        // catch missing or negative status value (negative '-' is not a digit)
        pos = protoPrefix.psize();

        // skip arbitrary number of digits and a dot in the verion portion
        while ((size_t)pos <= hdr_len && (*(buf+pos) == '.' || xisdigit(*(buf+pos)) ) ) ++pos;

        // catch missing version info
        if (pos == protoPrefix.psize()) {
            debugs(58, 3, "missing protocol version numbers (ie. " << protoPrefix << "/1.0) in '" << buf << "'");
            *error = Http::scInvalidHeader;
            return false;
        }
    }

    // skip arbitrary number of spaces...
    while ((size_t)pos <= hdr_len && (char)*(buf+pos) == ' ') ++pos;

    if ((size_t)pos < hdr_len && !xisdigit(*(buf+pos))) {
        debugs(58, 3, "missing or invalid status number in '" << buf << "'");
        *error = Http::scInvalidHeader;
        return false;
    }

    return true;
}