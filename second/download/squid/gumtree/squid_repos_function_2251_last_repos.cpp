bool
HttpHeader::skipUpdateHeader(const Http::HdrType id) const
{
    // RFC 7234, section 4.3.4: use fields other from Warning for update
    return id == Http::HdrType::WARNING;
}