bool
ACLHTTPHeaderData::empty() const
{
    return (hdrId == HDR_BAD_HDR && hdrName.undefined()) || regex_rule->empty();
}