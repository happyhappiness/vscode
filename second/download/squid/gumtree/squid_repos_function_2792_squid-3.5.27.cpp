bool
HttpHeader::skipUpdateHeader(const http_hdr_type id) const
{
    // RFC 7234, section 4.3.4: use fields other from Warning for update
    return id == HDR_WARNING;
}