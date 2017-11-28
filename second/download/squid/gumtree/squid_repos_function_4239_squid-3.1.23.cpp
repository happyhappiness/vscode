bool
ACLHTTPHeaderData::match(HttpHeader* hdr)
{
    if (hdr == NULL)
        return false;

    debugs(28, 3, "aclHeaderData::match: checking '" << hdrName << "'");

    String value = hdrId != HDR_BAD_HDR ? hdr->getStrOrList(hdrId) : hdr->getByName(hdrName.termedBuf());

    return regex_rule->match(value.termedBuf());
}