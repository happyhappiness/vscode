bool
ACLHTTPHeaderData::empty() const
{
    return (hdrId == Http::HdrType::BAD_HDR && hdrName.isEmpty()) || regex_rule->empty();
}