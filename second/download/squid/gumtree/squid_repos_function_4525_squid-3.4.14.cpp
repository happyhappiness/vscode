bool
ACLHTTPHeaderData::match(HttpHeader* hdr)
{
    if (hdr == NULL)
        return false;

    debugs(28, 3, "aclHeaderData::match: checking '" << hdrName << "'");

    String value;
    if (hdrId != HDR_BAD_HDR) {
        if (!hdr->has(hdrId))
            return false;
        value = hdr->getStrOrList(hdrId);
    } else {
        if (!hdr->getByNameIfPresent(hdrName.termedBuf(), value))
            return false;
    }

    // By now, we know the header is present, but:
    // HttpHeader::get*() return an undefined String for empty header values;
    // String::termedBuf() returns NULL for undefined Strings; and
    // ACLRegexData::match() always fails on NULL strings.
    // This makes it possible to detect an empty header value using regex:
    const char *cvalue = value.defined() ? value.termedBuf() : "";
    return regex_rule->match(cvalue);
}