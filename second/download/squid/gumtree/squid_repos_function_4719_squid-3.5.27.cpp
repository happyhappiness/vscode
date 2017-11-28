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

    SBuf cvalue(value);
    return regex_rule->match(cvalue.c_str());
}