bool
ACLHTTPHeaderData::match(HttpHeader* hdr)
{
    if (hdr == NULL)
        return false;

    debugs(28, 3, "aclHeaderData::match: checking '" << hdrName << "'");

    String value;
    if (hdrId != Http::HdrType::BAD_HDR) {
        if (!hdr->has(hdrId))
            return false;
        value = hdr->getStrOrList(hdrId);
    } else {
        if (!hdr->hasNamed(hdrName, &value))
            return false;
    }

    auto cvalue = StringToSBuf(value);
    return regex_rule->match(cvalue.c_str());
}