int
HttpHeader::has(http_hdr_type id) const
{
    assert_eid(id);
    assert(id != HDR_OTHER);
    debugs(55, 9, this << " lookup for " << id);
    return CBIT_TEST(mask, id);
}