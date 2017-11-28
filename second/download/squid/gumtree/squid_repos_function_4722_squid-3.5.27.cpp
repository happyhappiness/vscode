bool
ACLHTTPHeaderData::empty() const
{
    return (hdrId == HDR_BAD_HDR && hdrName.size()==0) || regex_rule->empty();
}